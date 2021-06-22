#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

using pll = pair<long long, long long>;
#define x first
#define y second
using pdi = pair<double, int>;
double dist(pll p1, pll p2) { return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)); }

int main(void)
{
    //read
#ifndef HOME
    freopen("pwrfail.in", "r", stdin);
    freopen("pwrfail.out", "w", stdout);
#endif
    int numNodes, numWire;
    double maxLen;
    cin >> numNodes >> numWire >> maxLen;
    pll *points = new pll[numNodes];
    for (int i = 0; i < numNodes; i++)
        cin >> points[i].first >> points[i].second;
    int w1, w2;
    vector<int> *wires = new vector<int>[numNodes];
    for (int i = 0; i < numWire; i++)
    {
        cin >> w1 >> w2;
        w1--, w2--;
        wires[w1].push_back(w2);
        wires[w2].push_back(w1);
    }

    //do the dijkstra
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    bool *vis = new bool[numNodes];
    fill(vis, vis + numNodes, false);
    pq.push({0, numNodes - 1});
    double cost, currDist;
    int node;
    while (!vis[0] && !pq.empty())
    {
        node = pq.top().second;
        cost = pq.top().first;
        pq.pop();
        if (vis[node])
            continue;
        vis[node] = true;
        for (int wire : wires[node])
            if (!vis[wire])
                pq.push({cost, wire});
        for (int i = 0; i < numNodes; i++)
            if (!vis[i] && (currDist = dist(points[node], points[i])) <= maxLen)
                pq.push({cost + currDist, i});
    }

    //print and delete
    cout << (int)(vis[0] ? cost * 1000 : -1) << endl;
    delete[] points;
    delete[] wires;
    delete[] vis;
    return 0;
}