#include <iostream>
#include <algorithm>
using namespace std;

#define xMult 2019201913
#define yMult 2019201949
#define MOD 2019201997
int calcDist(int x, int y)
{
    long long X = min(x, y), Y = max(x, y);
    return (X * xMult + Y * yMult) % MOD;
}
#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
#endif
    int numCows, numGroups;
    cin >> numCows >> numGroups;

    //form the distences
    int *dists = new int[numCows];
    fill(dists, dists + numCows, MOD);
    bool *vis = new bool[numCows];
    fill(vis, vis + numCows, false);
    int currNode;
    for (int run = 0; run < numCows; run++)
    {
        currNode = NA;
        for (int i = 0; i < numCows; i++)
            if (!vis[i] && (currNode == NA || dists[i] < dists[currNode]))
                currNode = i;
        vis[currNode] = true;
        for (int i = 0; i < numCows; i++)
            if (!vis[i])
                dists[i] = min(dists[i], calcDist(i + 1, currNode + 1));
    }

    //print and delete
    sort(dists, dists + numCows, greater<int>());
    cout << dists[numGroups - 1] << endl;
    delete[] dists;
    delete[] vis;
    return 0;
}