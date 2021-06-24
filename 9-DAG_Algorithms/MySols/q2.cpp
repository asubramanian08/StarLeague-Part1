#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_COWS 1000
bool adjMatrix[MAX_COWS][MAX_COWS] = {false};

int main(void)
{
    //read
#ifndef HOME
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);
#endif
    int numCows, numConn;
    cin >> numCows >> numConn;
    int c1, c2;
    for (int i = 0; i < numConn; i++)
    {
        cin >> c1 >> c2;
        c1--, c2--;
        adjMatrix[c1][c2] = true;
    }

    //do the transitive closer
    for (int i = 0; i < numCows; i++)
        for (int j = 0; j < numCows; j++)
            if (adjMatrix[j][i])
                for (int k = 0; k < numCows; k++)
                    adjMatrix[j][k] |= adjMatrix[i][k];

    //find the number of nodes affected
    int *affected = new int[numCows];
    fill(affected, affected + numCows, 1);
    for (int i = 0; i < numCows; i++)
        for (int j = 0; j < numCows; j++)
            if (adjMatrix[i][j])
            {
                affected[i]++;
                affected[j]++;
            }

    //print and delete
    int ans = 0;
    for (int i = 0; i < numCows; i++)
        ans += affected[i] == numCows;
    cout << ans << endl;
    delete[] affected;
    return 0;
}