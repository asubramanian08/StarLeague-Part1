#include <iostream>
#include <algorithm>
using namespace std;

using cow = pair<int, int>;
#define x second
#define y first
#define BIG_NUM 1'000'000'000

int main(void)
{
    //read
#ifndef HOME
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    cow *cowsByY = new cow[numCows];
    int *byX = new int[numCows];
    for (int i = 0; i < numCows; i++)
    {
        cin >> cowsByY[i].x >> cowsByY[i].y;
        byX[i] = cowsByY[i].x;
    }

    //prep for the sweep lines (sort)
    sort(cowsByY, cowsByY + numCows);
    sort(byX, byX + numCows);

    //do the sweep line
    int ur = numCows, ul = 0, lr = 0, ll = 0, minQuad = BIG_NUM;
    for (int i = 0; i < numCows; i++) //x sweep line
    {
        //move
        ur--;
        ul++;
        if (i != numCows - 1 && byX[i] == byX[i + 1])
            continue;                     //check
        for (int j = 0; j < numCows; j++) //y sweep line
        {
            //move
            if (cowsByY[j].x > byX[i])
            {
                ur--;
                lr++;
            }
            else
            {
                ul--;
                ll++;
            }
            if (j != numCows - 1 && cowsByY[j].y == cowsByY[j + 1].y)
                continue; //check
            minQuad = min(minQuad, max(max(ur, ul), max(lr, ll)));
        }
        ur += lr;
        lr = 0;
        ul += ll;
        ll = 0;
    }

    //print and delete
    cout << minQuad << endl;
    delete[] cowsByY;
    delete[] byX;
    return 0;
}