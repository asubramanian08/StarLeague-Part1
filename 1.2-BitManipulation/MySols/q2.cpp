#include <iostream>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("rockers2.in", "r", stdin);
    freopen("rockers2.out", "w", stdout);
#endif
    int numSongs, time, numDisks;
    cin >> numSongs >> time >> numDisks;
    int *songLen = new int[numSongs];
    for (int i = 0; i < numSongs; i++)
        cin >> songLen[i];

    //though every combinations
    int maxSongs = 0, songCount, currTime, pos;
    for (int songSet = 0; songSet < 1 << numSongs; songSet++)
    {
        songCount = 0, pos = 0;
        for (int disk = 0; disk < numDisks; disk++)
            for (currTime = 0; pos < numSongs; pos++)
                if (songSet & (1 << pos))
                {
                    currTime += songLen[pos];
                    if (currTime > time)
                        break;
                    songCount++;
                }
        maxSongs = max(maxSongs, songCount);
    }

    //print and delete
    cout << maxSongs << endl;
    delete[] songLen;
    return 0;
}