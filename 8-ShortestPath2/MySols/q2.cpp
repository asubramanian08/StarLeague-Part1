#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int numFarms, numConns, source;
using pii = pair<int, int>;
#define BIG_NUM 1000000000
int *dijkstra(vector<pii> *graph)
{
    int *cost = new int[numFarms];
    fill(cost, cost + numFarms, BIG_NUM);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, source});
    int nd, wt;
    while (!pq.empty())
    {
        nd = pq.top().second;
        wt = pq.top().first;
        pq.pop();
        if (cost[nd] != BIG_NUM)
            continue;
        cost[nd] = wt;
        for (auto next : graph[nd])
            if (cost[next.second] == BIG_NUM)
                pq.push({wt + next.first, next.second});
    }
    return cost;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("sparty.in", "r", stdin);
    freopen("sparty.out", "w", stdout);
#endif
    cin >> numFarms >> numConns >> source;
    source--;
    vector<pii> *fromGraph = new vector<pii>[numFarms];
    vector<pii> *toGraph = new vector<pii>[numFarms];
    int u, v, wt;
    for (int i = 0; i < numConns; i++)
    {
        cin >> u >> v >> wt;
        u--, v--;
        fromGraph[u].push_back({wt, v});
        toGraph[v].push_back({wt, u});
    }

    //find the costs, max time
    int *fromCost = dijkstra(fromGraph);
    int *toCost = dijkstra(toGraph);
    int maxTime = 0;
    for (int i = 0; i < numFarms; i++)
        maxTime = max(maxTime, fromCost[i] + toCost[i]);

    //print and delete
    cout << maxTime << endl;
    delete[] fromGraph;
    delete[] toGraph;
    delete[] fromCost;
    delete[] toCost;
    return 0;
}