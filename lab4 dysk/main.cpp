#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <windows.h>

using namespace std;
const int INF = INT_MAX;

struct Edge {
    int to;
    int weight;
};

void addEdge(vector<vector<Edge>>& graph, int u, int v, int weight) {
    graph[u].push_back({ v, weight });
    graph[v].push_back({ u, weight });
}

int primMST(const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<int> minWeight(n, INF);
    vector<int> parent(n, -1);  
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    int start = 0; 
    minWeight[start] = 0;
    pq.push({ 0, start });
    int totalWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        totalWeight += weight;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;
            if (!visited[v] && w < minWeight[v]) {
                minWeight[v] = w;
                parent[v] = u;  
                pq.push({ w, v });
            }
        }
    }
   
    cout << "Ребра мінімального кістякового дерева:" << endl;
    for (int i = 1; i < n; i++) { 
        if (parent[i] != -1) {
            char u = 'A' + parent[i];
            char v = 'A' + i;
            cout << u << " - " << v << " з вагою " << minWeight[i] << endl;
        }
    }
    cout << "Загальна вага мінімального кістякового дерева: " << totalWeight << endl;

    return totalWeight;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n = 5; 
    vector<vector<Edge>> graph(n);

    
    addEdge(graph, 0, 1, 1);  
    addEdge(graph, 1, 2, 8);  
    addEdge(graph, 0, 2, 5);  
    addEdge(graph, 1, 4, 10); 
    addEdge(graph, 4, 3, 6);  
    addEdge(graph, 4, 0, 4);  
    addEdge(graph, 4, 2, 3);  
    addEdge(graph, 1, 3, 7); 
    addEdge(graph, 3, 2, 2); 

    primMST(graph);

    return 0;
}