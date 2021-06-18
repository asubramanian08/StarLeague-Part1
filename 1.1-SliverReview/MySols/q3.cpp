#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
using namespace std;

struct cow
{
    int x, y, radius;
};
cow *cows;
vector<int> *conns;
bool *vis;

int dist(int c1, int c2) { return pow(cows[c1].x - cows[c2].x, 2) + pow(cows[c1].y - cows[c2].y, 2); }
int DFS(int pos)
{
    if (vis[pos])
        return 0;
    vis[pos] = true;
    int visCount = 1;
    for (int next : conns[pos])
        visCount += DFS(next);
    return visCount;
}
int main(void)
{
    //read
#ifndef HOME
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    cows = new cow[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].x >> cows[i].y >> cows[i].radius;

    //find the connections
    conns = new vector<int>[numCows];
    for (int i = 0; i < numCows; i++)
        for (int j = 0; j < numCows; j++)
            if (dist(i, j) <= pow(cows[i].radius, 2))
                conns[i].push_back(j);

    //do a DFS and find the max cast
    vis = new bool[numCows];
    int maxCast = 0;
    for (int i = 0; i < numCows; i++)
    {
        fill(vis, vis + numCows, 0);
        maxCast = max(maxCast, DFS(i));
    }

    //print and delete
    cout << maxCast << endl;
    delete[] cows;
    delete[] conns;
    delete[] vis;
    return 0;
}