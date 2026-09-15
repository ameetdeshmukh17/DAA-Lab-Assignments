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

        // Find unvisited vertex with minimum distance
        for (int i = 0; i < n; i++) {
            if (!visited[i] &&
                (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1 || dist[u] == INT_MAX)
            break;

        visited[u] = true;

        // Relax adjacent vertices
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

void printPath(int parent[], int source, int destination,
               ofstream &fout) {

    int path[MAX];
    int count = 0;
    int current = destination;

    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    // No path exists
    if (path[count - 1] != source) {
        fout << "No path exists.\n";
        return;
    }

    fout << "Shortest Path: ";

    for (int i = count - 1; i >= 0; i--) {

        fout << path[i];

        if (i != 0)
            fout << " -> ";
    }

    fout << endl;
}

int main() {

    ifstream fin("inputd.txt");
    ofstream fout("output.txt");

    if (!fin) {
        cerr << "Error opening inputd.txt\n";
        return 1;
    }

    int n, m;

    fin >> n >> m;

    int graph[MAX][MAX] = {0};

    // Read m edges
    for (int i = 0; i < m; i++) {

        int u, v, w;

        fin >> u >> v >> w;

        graph[u][v] = w;
        graph[v][u] = w;
    }

    int source, destination;

    fin >> source >> destination;

    int dist[MAX];
    int parent[MAX];

    dijkstra(graph, n, source, dist, parent);

    if (dist[destination] == INT_MAX) {
        fout << "No path exists.\n";
    }
    else {
        fout << "Shortest Distance: "
             << dist[destination] << endl;

        printPath(parent, source, destination, fout);
    }

    fin.close();
    fout.close();

    return 0;
}