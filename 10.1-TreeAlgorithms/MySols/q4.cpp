#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

using pii = pair<int, int>;
using piii = pair<pii, int>;
#define BIG_NUM 1000000000
#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);
#endif
    int numNodes, numConns, shortcutTime;
    cin >> numNodes >> numConns >> shortcutTime;
    int *cowsThrough = new int[numNodes];
    for (int i = 0; i < numNodes; i++)
        cin >> cowsThrough[i];
    vector<pii> *graph = new vector<pii>[numNodes];
    int n1, n2, wt;
    for (int i = 0; i < numConns; i++)
    {
        cin >> n1 >> n2 >> wt;
        n1--, n2--;
        graph[n1].push_back({wt, n2});
        graph[n2].push_back({wt, n1});
    }

    //dijkstra
    int *parent = new int[numNodes];
    int *cost = new int[numNodes];
    fill(cost, cost + numNodes, BIG_NUM);
    priority_queue<piii, vector<piii>, greater<piii>> pq;
    pq.push({{0, NA}, 0});
    int node, /*wt,*/ par;
    while (!pq.empty())
    {
        node = pq.top().second;
        wt = pq.top().first.first;
        par = pq.top().first.second;
        pq.pop();
        if (cost[node] != BIG_NUM)
            continue;
        cost[node] = wt;
        parent[node] = par;
        for (const pii &next : graph[node])
            pq.push({{wt + next.first, node}, next.second});
    }

    //calculate the cows though a node
    int *childCount = new int[numNodes];
    fill(childCount, childCount + numNodes, 0);
    for (int i = 1; i < numNodes; i++)
        childCount[parent[i]]++;
    queue<int> q;
    for (int i = 0; i < numNodes; i++)
        if (childCount[i] == 0)
            q.push(i);
    //int node;
    while (q.front() != 0)
    {
        node = q.front();
        q.pop();
        cowsThrough[parent[node]] += cowsThrough[node];
        if (--childCount[parent[node]] == 0)
            q.push(parent[node]);
    }

    //print and delete
    long long maxReduction = 0;
    for (int i = 0; i < numNodes; i++)
        maxReduction = max(maxReduction, (long long)(cost[i] - shortcutTime) * cowsThrough[i]);
    cout << maxReduction << endl;
    delete[] cowsThrough;
    delete[] graph;
    delete[] parent;
    delete[] cost;
    delete[] childCount;
    return 0;
}