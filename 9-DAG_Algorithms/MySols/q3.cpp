#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

using pii = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);
#endif
    int numNodes, maxDay, numConns;
    cin >> numNodes >> maxDay >> numConns;
    int *startTime = new int[numNodes];
    for (int i = 0; i < numNodes; i++)
        cin >> startTime[i];
    vector<pii> *graph = new vector<pii>[numNodes];
    int *inDeg = new int[numNodes];
    fill(inDeg, inDeg + numNodes, 0);
    int c1, c2, wt;
    for (int i = 0; i < numConns; i++)
    {
        cin >> c1 >> c2 >> wt;
        c1--, c2--;
        graph[c1].push_back({c2, wt});
        inDeg[c2]++;
    }

    //go though in topological order
    queue<int> q;
    for (int i = 0; i < numNodes; i++)
        if (inDeg[i] == 0)
            q.push(i);
    int node;
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        for (auto next : graph[node])
        {
            startTime[next.first] = max(startTime[next.first], startTime[node] + next.second);
            if (--inDeg[next.first] == 0)
                q.push(next.first);
        }
    }

    //print and delete
    for (int i = 0; i < numNodes; i++)
        cout << startTime[i] << endl;
    delete[] startTime;
    delete[] graph;
    delete[] inDeg;
    return 0;
}