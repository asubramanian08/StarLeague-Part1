#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

vector<int> *graph;
int numNodes;
#define BIG_NUM 1000000000
int *BFS(int source)
{
    int *dists = new int[numNodes];
    fill(dists, dists + numNodes, BIG_NUM);
    queue<int> bfs;
    bfs.push(source);
    dists[source] = 0;
    int node;
    while (!bfs.empty())
    {
        node = bfs.front();
        bfs.pop();
        for (int next : graph[node])
            if (dists[next] > dists[node] + 1)
            {
                dists[next] = dists[node] + 1;
                bfs.push(next);
            }
    }
    return dists;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("piggyback.in", "r", stdin);
    freopen("piggyback.out", "w", stdout);
#endif
    int bCost, eCost, jCost, numConns;
    cin >> bCost >> eCost >> jCost >> numNodes >> numConns;
    graph = new vector<int>[numNodes];
    int nd1, nd2;
    for (int i = 0; i < numConns; i++)
    {
        cin >> nd1 >> nd2;
        nd1--, nd2--;
        graph[nd1].push_back(nd2);
        graph[nd2].push_back(nd1);
    }

    //find the distences with BFS
    int *bessie = BFS(0);
    int *elsie = BFS(1);
    int *joined = BFS(numNodes - 1);

    //print and delete
    int minDist = BIG_NUM;
    for (int i = 0; i < numNodes; i++)
        minDist = min(minDist, bCost * bessie[i] + eCost * elsie[i] + jCost * joined[i]);
    cout << minDist << endl;
    delete[] graph;
    delete[] bessie;
    delete[] elsie;
    delete[] joined;
    return 0;
}