#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <numeric>
using namespace std;

bool *kit;
vector<int> *graph;
void DFS(int node, int par)
{
    for (int next : graph[node])
    {
        if (next == par)
            continue;

        DFS(next, node);
        if (!kit[next])
            kit[node] = true;
    }
}

int main(void)
{
    //read
#ifndef HOME
    freopen("kits.in", "r", stdin);
    freopen("kits.out", "w", stdout);
#endif
    int numNodes, givenKits;
    cin >> numNodes >> givenKits;
    kit = new bool[numNodes];
    fill(kit, kit + numNodes, false);
    int n1, n2;
    for (int i = 0; i < givenKits; i++)
    {
        cin >> n1;
        kit[n1 - 1] = true;
    }
    graph = new vector<int>[numNodes];
    for (int i = 1; i < numNodes; i++)
    {
        cin >> n1 >> n2;
        n1--, n2--;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    //do the DFS and get ans
    DFS(0, 0);

    //print and delete
    cout << accumulate(kit, kit + numNodes, 0) - givenKits << endl;
    delete[] kit;
    delete[] graph;
    return 0;
}