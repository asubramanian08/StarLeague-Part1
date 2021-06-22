#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_FLOW 1005
#define MULT 1000000
struct pipe
{
    int conn, cost, flow;
    pipe(int conn, int cost, int flow) : conn(conn), cost(cost), flow(flow) {}
    pipe() = default;
};
using pii = pair<int, int>;
int numNodes, flow;
vector<pipe> *graph;
bool *vis;
int dijkstra()
{
    fill(vis, vis + numNodes, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, numNodes - 1});
    int node, cost;
    while (!vis[0] && !pq.empty())
    {
        node = pq.top().second;
        cost = pq.top().first;
        pq.pop();
        if (vis[node])
            continue;
        vis[node] = true;
        for (const pipe &next : graph[node])
            if (!vis[next.conn] && next.flow >= flow)
                pq.push({next.cost + cost, next.conn});
    }
    return vis[0] ? cost : -1;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);
#endif
    int numConns;
    cin >> numNodes >> numConns;
    graph = new vector<pipe>[numNodes];
    int n1, n2, c, f;
    for (int i = 0; i < numConns; i++)
    {
        cin >> n1 >> n2 >> c >> f;
        n1--, n2--;
        graph[n1].push_back(pipe(n2, c, f));
        graph[n2].push_back(pipe(n1, c, f));
    }

    //loop though flow and find max ratio
    double maxRatio = 0;
    vis = new bool[numNodes];
    for (flow = 1; flow < MAX_FLOW; flow++)
        maxRatio = max(maxRatio, (double)flow / (double)dijkstra());

    //print and delete
    cout << (long long)(maxRatio * MULT) << endl;
    delete[] graph;
    return 0;
}