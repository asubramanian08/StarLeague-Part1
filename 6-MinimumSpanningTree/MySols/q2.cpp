//a lot copied from starleague part 1 lesson 6 q1
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

#define MAX_FARMS 300
int adjMatrix[MAX_FARMS][MAX_FARMS];
#define BIG_NUM 1000000000
#define NA -1
using pii = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
#endif
    int numFarms;
    cin >> numFarms;
    int *costTo = new int[numFarms];
    for (int i = 0; i < numFarms; i++)
        cin >> costTo[i];
    for (int i = 0; i < numFarms; i++)
        for (int j = 0; j < numFarms; j++)
            cin >> adjMatrix[i][j];

    //get the cost
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

/*

#include <iostream>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;

#define MAX_FARMS 300
int adjMatrix[MAX_FARMS][MAX_FARMS];
#define NA -1
using pii = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    FILE* junk;
    junk = freopen("water.in", "r", stdin);
    junk = freopen("water.out", "w", stdout);
#endif
    int numFarms;
    cin >> numFarms;
    int *wellCost = new int[numFarms];
    for (int i = 0; i < numFarms; i++)
        cin >> wellCost[i];
    for (int i = 0; i < numFarms; i++)
        for (int j = 0; j < numFarms; j++)
            cin >> adjMatrix[i][j];

    //prepare + add wells
    int *costTo = new int[numFarms];
    fill(costTo, costTo + numFarms, NA);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < numFarms; i++)
        pq.push({wellCost[i], i});

    //run though
    int node, wt;
    while (!pq.empty())
    {
        node = pq.top().second;
        wt = pq.top().first;
        pq.pop();
        if (costTo[node] != NA)
            continue;
        costTo[node] = wt;
        for (int i = 0; i < numFarms; i++)
            if (costTo[i] == NA)
                pq.push({adjMatrix[node][i], i});
    }

    //print and delete
    cout << accumulate(costTo, costTo + numFarms, 0) << endl;
    delete[] costTo;
    return 0;
}*/