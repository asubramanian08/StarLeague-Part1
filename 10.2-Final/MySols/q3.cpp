#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MOD 1000000007
#define NA -1
vector<int> *graph;
bool *vis;
int repeatCt;
int DFS(int node, int par)
{
    if (vis[node])
    {
        repeatCt++;
        return 0;
    }
    vis[node] = true;
    int sum = 1;
    for (auto next : graph[node])
        if (next != par)
            sum += DFS(next, node);
        else
            par = NA;
    return sum;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("alliance.in", "r", stdin);
    freopen("alliance.out", "w", stdout);
#endif
    int numFarms, numTrails;
    cin >> numFarms >> numTrails;
    graph = new vector<int>[numFarms];
    int f1, f2;
    for (int i = 0; i < numTrails; i++)
    {
        cin >> f1 >> f2;
        f1--, f2--;
        graph[f1].push_back(f2);
        graph[f2].push_back(f1);
    }

    long long ans = 1, ret;
    vis = new bool[numFarms];
    fill(vis, vis + numFarms, false);
    for (int i = 0; i < numFarms; i++)
        if (!vis[i])
        {
            repeatCt = 0;
            ret = DFS(i, NA);
            if (repeatCt > 2)
                ans = 0;
            if (repeatCt != 0)
                ans *= 2;
            else
                ans *= ret;
            ans %= MOD;
        }

    //print and delete
    cout << ans << endl;
    delete[] graph;
    delete[] vis;
    return 0;
}