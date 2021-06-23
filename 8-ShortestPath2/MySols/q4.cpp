#include <iostream>
using namespace std;

#define MAX_PAST 500
int adjMatrix[MAX_PAST][MAX_PAST];
#define BIG_NUM 1000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("bestspot.in", "r", stdin);
    freopen("bestspot.out", "w", stdout);
#endif
    int numPast, numFav, numConn;
    cin >> numPast >> numFav >> numConn;
    int *favorite = new int[numFav];
    for (int i = 0; i < numFav; i++)
        cin >> favorite[i];
    for (int i = 0; i < numPast; i++)
        for (int j = 0; j < numPast; j++)
            adjMatrix[i][j] = i != j ? BIG_NUM : 0;

    int nd1, nd2, wt;
    for (int i = 0; i < numConn; i++)
    {
        cin >> nd1 >> nd2 >> wt;
        nd1--, nd2--;
        adjMatrix[nd1][nd2] = wt;
        adjMatrix[nd2][nd1] = wt;
    }

    //do floyd warshall
    for (int i = 0; i < numPast; i++)
        for (int j = 0; j < numPast; j++)
            for (int k = 0; k < numPast; k++)
                if (adjMatrix[j][k] > adjMatrix[j][i] + adjMatrix[i][k])
                    adjMatrix[j][k] = adjMatrix[j][i] + adjMatrix[i][k];

    //find the best place
    int bestPlace = -1, bestDist = BIG_NUM, currDist;
    for (int i = 0; i < numPast; i++)
    {
        currDist = 0;
        for (int j = 0; j < numFav; j++)
            currDist += adjMatrix[i][favorite[j] - 1];
        if (currDist < bestDist)
        {
            bestDist = currDist;
            bestPlace = i;
        }
    }

    //print and delete
    cout << bestPlace + 1 << endl;
    delete[] favorite;
    return 0;
}