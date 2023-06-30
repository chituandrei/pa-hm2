#include <bits/stdc++.h>

using namespace std;

int timp = 0;

void recursive_dfs(vector<int>adj[], int source, vector<bool>&viz,
                vector <int> &pre, vector<int >&post, vector<int>&ret) {
    pre[source] = timp;
    viz[source] = true;
    ret.push_back(source);
    for (int j = 0; j < adj[source].size(); j++) {
        if (!viz[adj[source][j]])
            recursive_dfs(adj, adj[source][j], viz, pre, post, ret);
    }
    post[source] = timp;
    timp++;
}

int main() {
    ifstream f("magazin.in");
    ofstream g("magazin.out");

    int n, q, parent;

    f >> n >> q;

    vector<int>adj[n+1];
    vector<int>dp(n+1, 0);
    vector<int>apr(n+1, 0);
    vector<bool>viz(n+1, 0);
    vector<int>ret;
    vector<int>pre(n+1, 0);
    vector<int>post(n+1, 0);

    for (int i = 2; i <= n; i++) {
        f >> parent;
        adj[parent].push_back(i);
    }

    recursive_dfs(adj, 1, viz, pre, post, ret);

    for (int i = 1; i<= n; i++)
        dp[i] = post[i] - pre[i];

    for (int i = 0; i < ret.size(); i++)
        apr[ret[i]] = i+1;

    for (int i = 0; i < q; i++) {
        int start, step;
        f >> start >> step;
        if (apr[start] + step - 1 >= ret.size()) {
            g << -1<<"\n";
        } else if (step > dp[start]) {
            g<< -1<<"\n";
        } else {
            g<<ret[apr[start] + step -1]<<"\n";
        }
    }
}
