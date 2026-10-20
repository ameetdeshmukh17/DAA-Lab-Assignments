#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;

void dijkstra(int graph[MAX][MAX], int n, int source,
              int dist[], int parent[]) {

    bool visited[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < n - 1; count++) {

        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] &&
                (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1 || dist[u] == INT_MAX)
            break;

        visited[u] = true;

        for (int v = 0; v < n; v++) {

            if (!visited[v] &&
                graph[u][v] != 0 &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

void printPath(int parent[], int source, int destination) {

    int path[MAX];
    int count = 0;
    int current = destination;

    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    if (path[count - 1] != source) {
        cout << "No path exists.\n";
        return;
    }

    cout << "Shortest Path: ";

    for (int i = count - 1; i >= 0; i--) {

        cout << path[i];

        if (i != 0)
            cout << " -> ";
    }

    cout << endl;
}

int main() {

    int n, m;

    cout << "===== Dijkstra's Shortest Path Algorithm =====\n\n";

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    int graph[MAX][MAX] = {0};

    cout << "\nEnter each edge in the format:\n";
    cout << "Source Vertex  Destination Vertex  Weight\n";
    cout << "Example: 0 1 4\n\n";

    for (int i = 0; i < m; i++) {

        int u, v, w;

        cout << "Enter edge " << i + 1 << ": ";
        cin >> u >> v >> w;

        graph[u][v] = w;
        graph[v][u] = w;
    }

    int source, destination;

    cout << "\nEnter source vertex: ";
    cin >> source;

    cout << "Enter destination vertex: ";
    cin >> destination;

    int dist[MAX];
    int parent[MAX];

    dijkstra(graph, n, source, dist, parent);

    cout << "\n========== Result ==========\n";

    if (dist[destination] == INT_MAX) {
        cout << "No path exists.\n";
    }
    else {
        cout << "Shortest Distance: "
             << dist[destination] << endl;

        printPath(parent, source, destination);
    }

    return 0;
}
