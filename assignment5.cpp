#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long cost;
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in) {
        cerr << "Cannot open input.txt\n";
        return 1;
    }

    int n, m, stages;
    in >> n >> m >> stages;

    vector<int> stage(n + 1);

    for (int i = 1; i <= n; ++i) {
        in >> stage[i];
    }

    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long cost;
        in >> u >> v >> cost;

        if (u >= 1 && u <= n && v >= 1 && v <= n &&
            stage[v] > stage[u]) {
            graph[u].push_back({v, cost});
        }
    }

    int q;
    in >> q;

    const long long INF = LLONG_MAX / 4;

    while (q--) {
        int source, destination;
        in >> source >> destination;

        vector<long long> dp(n + 1, INF);
        vector<int> nextNode(n + 1, -1);

        if (destination >= 1 && destination <= n) {
            dp[destination] = 0;
        }

        for (int s = stages - 1; s >= 1; --s) {
            for (int u = 1; u <= n; ++u) {
                if (stage[u] == s) {
                    for (const auto &e : graph[u]) {
                        if (dp[e.to] != INF &&
                            e.cost + dp[e.to] < dp[u]) {
                            dp[u] = e.cost + dp[e.to];
                            nextNode[u] = e.to;
                        }
                    }
                }
            }
        }

        if (source < 1 || source > n ||
            destination < 1 || destination > n ||
            dp[source] == INF) {
            out << "No valid route from " << source
                << " to " << destination << ".\n";
            continue;
        }

        out << "Minimum cost from " << source
            << " to " << destination << ": "
            << dp[source] << "\nRoute: ";

        int cur = source;
        out << cur;

        int steps = 0;

        while (cur != destination &&
               nextNode[cur] != -1 && steps++ <= n) {
            cur = nextNode[cur];
            out << " -> " << cur;
        }

        out << "\n";
    }

    return 0;
}