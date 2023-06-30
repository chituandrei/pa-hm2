#include <bits/stdc++.h>

using namespace std;

void dfs(vector<int>adj[], int start, vector<bool>&viz, stack<int>&stack_k) {
    viz[start] = true;
    for (int i = 0; i < adj[start].size(); i++) {
        int vecin = adj[start][i];
        if (viz[vecin] == false)
            dfs(adj, vecin, viz, stack_k);
    }
    stack_k.push(start);
}
void dfs2(vector<int>adj[], int start, vector<bool>&viz, vector<int>&sol) {
    viz[start] = true;
    sol.push_back(start);
    for (int i = 0; i < adj[start].size(); i++) {
        int vecin = adj[start][i];
        if (viz[vecin] == false)
            dfs2(adj, vecin, viz, sol);
    }
}
int main() {
    ifstream f("ferate.in");
    ofstream g("ferate.out");

    int n, m, start, x, y, sol_afis = 0;

    f>>n>>m>>start;

    vector<int>adj[n+1];
    vector<int>adj_reverse[n+1];
    vector<bool>grad(n+1, 0);
    vector<int>comp_conexa(n+1, 0);

    for (int i = 0; i < m; i++) {
        f >> x >> y;
        adj[x].push_back(y);
        adj_reverse[y].push_back(x);
    }

    vector<bool>viz(n+1, 0);
    stack<int>stack_k;

    for (int i = 1; i <= n; i++)
        if (viz[i] == false)
            dfs(adj, i, viz, stack_k);

    viz.assign(viz.size(), false);

    while (!stack_k.empty()) {
        int nod = stack_k.top();
        stack_k.pop();
        if (viz[nod] == false) {
            vector<int>sol;
            dfs2(adj_reverse, nod, viz, sol);

            bool change = false;
            for (int i = 0; i < sol.size(); i++) {
                comp_conexa[sol[i]] = sol[0];
                if (sol[i] == start) {
                    change = 1;
                    break;
                }
            }

            if (change == 1) {
                for (int i = 0; i < sol.size(); i++)
                    comp_conexa[sol[i]] = start;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < adj[i].size(); j++) {
            int vecin = adj[i][j];
            if (comp_conexa[i] != comp_conexa[vecin])
                grad[comp_conexa[vecin]] = true;
        }

    for (int i = 1; i <= n; i++)
        if (grad[i] == false && i!= start && comp_conexa[i] == i)
            sol_afis++;

    g<<sol_afis;

    f.close();
    g.close();
}
