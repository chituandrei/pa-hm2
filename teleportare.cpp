#include <bits/stdc++.h>


using namespace std;

const int INF = (1<<30);
vector<int>distances(10000+5);
vector<pair<int, int>>adj[10000+5];
int n;

struct compara {
    bool operator()(int x, int y) {
        return distances[x] > distances[y];
    }
};

void dijkstra(int source) {
    vector<bool>viz(n+1, false);
    priority_queue<int, vector<int>, compara> Coada;
    for (int i = 0; i < distances.size(); i++)
        distances[i] = INF;

    distances[source] = 0;
    Coada.push(source);
    viz[source] = true;

    while (!Coada.empty()) {
        int curr = Coada.top();
        Coada.pop();
        viz[curr] = false;

        for (int i = 0; i < adj[curr].size(); i++) {
            int vecin = adj[curr][i].first;
            int cost = adj[curr][i].second;
            if (distances[curr] + cost < distances[vecin]) {
                distances[vecin] = distances[curr] + cost;
                if (viz[vecin] == false) {
                    Coada.push(vecin);
                    viz[vecin] = true;
                }
            }
        }
    }
}
int main() {
    ifstream f("teleportare.in");
    ofstream g("teleportare.out");

    int m, k;
    f >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int x, y, cost;

        f >> x >> y >> cost;
        adj[x].push_back(make_pair(y, cost));
        adj[y].push_back(make_pair(x, cost));
    }

    for (int i = 0; i < k; i++) {
        int x, y, cost;

        f >> x >> y >> cost;
        adj[x].push_back(make_pair(y, 1));
        adj[y].push_back(make_pair(x, 1));
    }

    dijkstra(1);

    if (distances[n] != INF) {
        g << distances[n];
    } else {
        g << -1;
    }

    f.close();
    g.close();
}
