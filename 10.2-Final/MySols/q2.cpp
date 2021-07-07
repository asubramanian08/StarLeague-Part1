#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

using pii = pair<int, int>;
#define BIG_NUM 1000000000
#define NA -1
int dist(pii p1, pii p2)
{
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main(void)
{
    //read
#ifndef HOME
    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);
#endif
    int numBarns, minRoad;
    cin >> numBarns >> minRoad;
    pii *points = new pii[numBarns];
    for (int i = 0; i < numBarns; i++)
        cin >> points[i].first >> points[i].second;

    //do the MST
    int *costTo = new int[numBarns];
    fill(costTo, costTo + numBarns, BIG_NUM);
    costTo[0] = 0;
    bool *vis = new bool[numBarns];
    fill(vis, vis + numBarns, false);
    int node, currDist;
    for (int run = 0; run < numBarns; run++)
    {
        node = NA;
        for (int i = 0; i < numBarns; i++)
            if (!vis[i] && (node == NA || costTo[i] < costTo[node]))
                node = i;
        if (costTo[node] == BIG_NUM)
        {
            cout << -1 << endl;
            return 0;
        }
        vis[node] = true;
        for (int i = 0; i < numBarns; i++)
            if (!vis[i] && (currDist = dist(points[node], points[i])) >= minRoad)
                costTo[i] = min(costTo[i], currDist);
    }

    //print and delete
    int ans = 0;
    for (int i = 0; i < numBarns; i++)
        ans += costTo[i];
    cout << ans << endl;
    delete[] points;
    delete[] costTo;
    delete[] vis;
    return 0;
}