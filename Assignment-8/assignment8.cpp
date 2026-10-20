#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL << 60);

struct State {
    ll bound, cost;
    vector<int> path;
    vector<bool> visited;
    int current;
    bool operator>(const State& other) const { return bound > other.bound; }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    if (!in) { cerr << "Cannot open input.txt\n"; return 1; }
    int n; in >> n;
    vector<vector<ll>> cost(n, vector<ll>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            in >> cost[i][j];
            if (i != j && cost[i][j] < 0) { out << "Negative costs are not supported.\n"; return 0; }
        }
    if (n <= 0) { out << "Invalid number of cities.\n"; return 0; }
    if (n == 1) { out << "Optimal route: 1 -> 1\nMinimum cost: 0\n"; return 0; }
    vector<ll> minOut(n, INF);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j) minOut[i] = min(minOut[i], cost[i][j]);
    for (int i = 0; i < n; ++i) if (minOut[i] == INF) {
        out << "No Hamiltonian cycle exists.\n"; return 0;
    }
    auto lowerBound = [&](ll currentCost, int current, const vector<bool>& visited) {
        ll bound = currentCost + minOut[current];
        for (int i = 0; i < n; ++i) if (!visited[i]) bound += minOut[i];
        return bound;
    };
    priority_queue<State, vector<State>, greater<State>> pq;
    State start; start.cost = 0; start.path = {0}; start.visited.assign(n, false);
    start.visited[0] = true; start.current = 0;
    start.bound = lowerBound(0, 0, start.visited); pq.push(start);
    ll bestCost = INF; vector<int> bestPath;
    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        if (s.bound >= bestCost) continue;
        if ((int)s.path.size() == n) {
            if (cost[s.current][0] < INF) {
                ll total = s.cost + cost[s.current][0];
                if (total < bestCost) { bestCost = total; bestPath = s.path; bestPath.push_back(0); }
            }
            continue;
        }
        for (int next = 1; next < n; ++next) if (!s.visited[next]) {
            State child; child.cost = s.cost + cost[s.current][next];
            child.path = s.path; child.path.push_back(next);
            child.visited = s.visited; child.visited[next] = true; child.current = next;
            child.bound = lowerBound(child.cost, child.current, child.visited);
            if (child.bound < bestCost) pq.push(move(child));
        }
    }
    if (bestPath.empty()) { out << "No Hamiltonian cycle exists.\n"; return 0; }
    out << "Optimal route: ";
    for (int i = 0; i < (int)bestPath.size(); ++i) {
        if (i) out << " -> "; out << bestPath[i] + 1;
    }
    out << "\nMinimum cost: " << bestCost << "\n";
    return 0;
}
