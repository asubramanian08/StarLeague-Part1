#include <iostream>
using namespace std;

struct edge
{
    int u, v, wt;
};
#define BIG_NUM 1000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("jobhunt.in", "r", stdin);
    freopen("jobhunt.out", "w", stdout);
#endif
    int maxMoney, numPaths, numNodes, numFlights, source;
    cin >> maxMoney >> numPaths >> numNodes >> numFlights >> source;
    source--;
    edge *edges = new edge[numPaths + numFlights];
    for (int i = 0; i < numPaths; i++)
    {
        cin >> edges[i].u >> edges[i].v;
        edges[i].u--, edges[i].v--;
        edges[i].wt = 0;
    }
    for (int i = numPaths; i < numFlights + numPaths; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].wt;
        edges[i].u--, edges[i].v--;
    }

    //run the bellman ford
    int *dist = new int[numNodes];
    fill(dist, dist + numNodes, BIG_NUM);
    dist[source] = -maxMoney;
    for (int run = 1; run < numNodes; run++)
        for (int i = 0; i < numPaths + numFlights; i++)
            dist[edges[i].v] = min(dist[edges[i].v], dist[edges[i].u] + edges[i].wt - maxMoney);
    for (int i = 0; i < numPaths + numFlights; i++) //pos cycle check
        if (dist[edges[i].v] > dist[edges[i].u] + edges[i].wt - maxMoney)
        {
            cout << -1 << endl;
            return 0;
        }

    //print and delete
    int minCost = BIG_NUM;
    for (int i = 0; i < numNodes; i++)
        minCost = min(minCost, dist[i]);
    cout << -minCost << endl;
    delete[] edges;
    delete[] dist;
    return 0;
}