#include <bits/stdc++.h>

using namespace std;

ifstream f("supercomputer.in");
ofstream g("supercomputer.out");

int solve(int N, int M, vector<int>& thread, vector<int>adj[]
                                , vector<int>count, queue<int>q) {
    vector<int> result(N + 1, 0);
    int sol = 0;

    while (!q.empty()) {
        int task = q.front();
        q.pop();

        for (int i = 0; i < adj[task].size(); ++i)  {
            int dependent_task = adj[task][i];
            count[dependent_task]--;

            int costa = 0;
            if (thread[task] != thread[dependent_task])
                costa = 1;

            if (result[dependent_task] < result[task] + costa)
                result[dependent_task] = result[task] + costa;

            if (sol < result[dependent_task])
                sol = result[dependent_task];

            if (count[dependent_task] == 0)
                q.push(dependent_task);
        }
    }

    return sol;
}

int main() {
    int N, M;
    bool ok = false;

    f >> N >> M;

    vector<int> thread(N + 1);

    f>>thread[1];

    for (int i = 2; i <= N; i++) {
        f >> thread[i];
        if (thread[i] != thread[1])
            ok = true;
    }

    if (ok == false) {
        g<<0;
    } else {
        vector<int> count(N + 1, 0);

        queue<int>q;
        vector<int>adj[N+1];

        for (int i = 0; i < M; i++) {
        int x, y;
        f >> x >> y;
        adj[x].push_back(y);
        count[y] ++;
        }

        for (int i = 1; i <= N; i++) {
            if (count[i] == 0)
                q.push(i);
        }

        g << solve(N, M, thread, adj, count, q);
    }
}
