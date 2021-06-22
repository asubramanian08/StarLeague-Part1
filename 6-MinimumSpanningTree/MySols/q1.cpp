#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

#define MAX_FARMS 100
int adjMatrix[MAX_FARMS][MAX_FARMS];
#define BIG_NUM 1000000000
#define NA -1
using pii = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);
#endif
    int numFarms;
    cin >> numFarms;
    for (int i = 0; i < numFarms; i++)
        for (int j = 0; j < numFarms; j++)
            cin >> adjMatrix[i][j];

    //get the cost
    int *costTo = new int[numFarms];
    fill(costTo, costTo + numFarms, BIG_NUM);
    costTo[0] = 0;
    bool *vis = new bool[numFarms];
    fill(vis, vis + numFarms, false);
    int node;
    for (int run = 0; run < numFarms; run++)
    {
        node = NA;
        for (int i = 0; i < numFarms; i++)
            if (!vis[i] && (node == NA || costTo[i] < costTo[node]))
                node = i;
        vis[node] = true;
        for (int i = 0; i < numFarms; i++)
            if (!vis[i])
                costTo[i] = min(costTo[i], adjMatrix[node][i]);
    }

    //print and delete
    cout << accumulate(costTo, costTo + numFarms, 0) << endl;
    delete[] costTo;
    delete[] vis;
    return 0;
}