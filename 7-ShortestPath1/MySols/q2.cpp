#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int numFarms;
using pii = pair<int, int>;
vector<pii> *graph;
pii *route;
bool *vis;
#define NA -1
#define BIG_NUM 1000000000
int dijkstra(void)
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});
    fill(route, route + numFarms, pii(BIG_NUM, NA));
    fill(vis, vis + numFarms, false);
    route[0] = pii(0, 0);
    int node, wt;
    while (!pq.empty())
    {
        node = pq.top().second;
        wt = pq.top().first;
        pq.pop();
        if (vis[node])
            continue;
        vis[node] = true;
        route[node].first = wt;
        for (auto next : graph[node])
            if (!vis[next.second] && route[next.second].first > wt + next.first)
            {
                route[next.second] = {wt + next.first, node};
                pq.push({wt + next.first, next.second});
            }
    }
    return route[numFarms - 1].first;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("rblock.in", "r", stdin);
    freopen("rblock.out", "w", stdout);
#endif
    int numConns;
    cin >> numFarms >> numConns;
    graph = new vector<pii>[numFarms];
    int f1, f2, wt;
    for (int i = 0; i < numConns; i++)
    {
        cin >> f1 >> f2 >> wt;
        f1--, f2--;
        graph[f1].push_back({wt, f2});
        graph[f2].push_back({wt, f1});
    }

    //get the orginal route
    route = new pii[numFarms];
    vis = new bool[numFarms];
    int orgDist = dijkstra();
    vector<int> travel;
    for (int pos = numFarms - 1; pos != 0; pos = route[pos].second)
        travel.push_back(pos);
    travel.push_back(0);

    //find the longest to double
    int pos1, pos2, maxDist = orgDist;
    for (int i = 1; i < travel.size(); i++)
    {
        for (int j = 0; j < graph[travel[i - 1]].size(); j++)
            if (graph[travel[i - 1]][j].second == travel[i])
            {
                pos1 = j;
                break;
            }
        for (int j = 0; j < graph[travel[i]].size(); j++)
            if (graph[travel[i]][j].second == travel[i - 1])
            {
                pos2 = j;
                break;
            }
        graph[travel[i - 1]][pos1].first *= 2;
        graph[travel[i]][pos2].first *= 2;
        maxDist = max(maxDist, dijkstra());
        graph[travel[i - 1]][pos1].first /= 2;
        graph[travel[i]][pos2].first /= 2;
    }

    //print and delete
    cout << maxDist - orgDist << endl;
    delete[] graph;
    delete[] route;
    delete[] vis;
    return 0;
}