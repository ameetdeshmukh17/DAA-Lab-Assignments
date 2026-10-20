#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in) {
        cerr << "Cannot open input.txt\n";
        return 1;
    }

    int courses, students;
    in >> courses >> students;

    vector<set<int>> graph(courses + 1);

    for (int s = 0; s < students; ++s) {
        int count;
        in >> count;

        vector<int> enrolled(count);
        for (int i = 0; i < count; ++i)
            in >> enrolled[i];

        for (int i = 0; i < count; ++i) {
            for (int j = i + 1; j < count; ++j) {
                int a = enrolled[i], b = enrolled[j];

                if (a >= 1 && a <= courses &&
                    b >= 1 && b <= courses && a != b) {
                    graph[a].insert(b);
                    graph[b].insert(a);
                }
            }
        }
    }

    vector<int> order(courses);
    iota(order.begin(), order.end(), 1);

    sort(order.begin(), order.end(), [&](int a, int b) {
        if (graph[a].size() != graph[b].size())
            return graph[a].size() > graph[b].size();
        return a < b;
    });

    vector<int> color(courses + 1, 0);
    int maxColor = 0;

    for (int course : order) {
        set<int> used;

        for (int neighbor : graph[course]) {
            if (color[neighbor])
                used.insert(color[neighbor]);
        }

        int c = 1;
        while (used.count(c))
            ++c;

        color[course] = c;
        maxColor = max(maxColor, c);
    }

    out << "Minimum exam slots found by Welsh-Powell greedy coloring: "
        << maxColor << "\n";

    for (int c = 1; c <= maxColor; ++c) {
        out << "Slot " << c << ": ";
        bool first = true;

        for (int course = 1; course <= courses; ++course) {
            if (color[course] == c) {
                if (!first)
                    out << ", ";

                out << "Course " << course;
                first = false;
            }
        }

        out << "\n";
    }

    out << "Conflict check: ";
    bool valid = true;

    for (int u = 1; u <= courses; ++u) {
        for (int v : graph[u]) {
            if (color[u] == color[v])
                valid = false;
        }
    }

    out << (valid
        ? "PASS - no overlapping exams share a slot."
        : "FAIL - a conflict exists.") << "\n";

    return 0;
}
