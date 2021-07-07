#include <iostream>
#include <vector>
using namespace std;

#define MAX_BARNS 500
int adjMatrix[MAX_BARNS][MAX_BARNS];
#define BIG_NUM 1000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("hosfire.in", "r", stdin);
    freopen("hosfire.out", "w", stdout);
#endif
    int numBarns, numConns;
    cin >> numBarns >> numConns;
    for (int i = 0; i < numBarns; i++)
        for (int j = 0; j < numBarns; j++)
            adjMatrix[i][j] = i != j ? BIG_NUM : 0;
    int b1, b2, wt;
    for (int i = 0; i < numConns; i++)
    {
        cin >> b1 >> b2 >> wt;
        b1--, b2--;
        adjMatrix[b1][b2] = min(adjMatrix[b1][b2], wt);
        adjMatrix[b2][b1] = min(adjMatrix[b2][b1], wt);
    }

    //do the floyd warshall
    for (int i = 0; i < numBarns; i++)
        for (int j = 0; j < numBarns; j++)
            for (int k = 0; k < numBarns; k++)
                if (adjMatrix[j][k] > adjMatrix[j][i] + adjMatrix[i][k])
                    adjMatrix[j][k] = adjMatrix[j][i] + adjMatrix[i][k];

    //find the hospital and firestation
    int maxBarns = 0, minHosp = BIG_NUM, minFire = BIG_NUM;
    vector<int> hospital, firestation;
    int currBarns, currHosp, currFire;
    for (int i = 0; i < numBarns; i++)
    {
        currBarns = currHosp = currFire = 0;
        for (int j = 0; j < numBarns; j++)
            if (adjMatrix[i][j] != BIG_NUM)
            {
                currBarns++;
                currHosp += adjMatrix[i][j];
                currFire = max(currFire, adjMatrix[i][j]);
            }
        if (currBarns < maxBarns)
            continue;
        if (currBarns > maxBarns || currHosp < minHosp)
        {
            hospital.clear();
            minHosp = currHosp;
        }
        if (currHosp == minHosp)
            hospital.push_back(i + 1);
        if (currBarns > maxBarns || currFire < minFire)
        {
            firestation.clear();
            minFire = currFire;
        }
        if (currFire == minFire)
            firestation.push_back(i + 1);
        maxBarns = max(maxBarns, currBarns);
    }

    //print
    for (auto barn : hospital)
        cout << barn << ' ';
    cout << endl;
    for (auto barn : firestation)
        cout << barn << ' ';
    cout << endl;
    return 0;
}