#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{
//read
#ifndef HOME
    freopen("mnotes.in", "r", stdin);
    freopen("mnotes.out", "w", stdout);
#endif
    int numNotes, numQueries;
    cin >> numNotes >> numQueries;
    long long *noteStart = new long long[numNotes];
    long long currTime = 0;
    int noteLen;
    for (int i = 0; i < numNotes; i++)
    {
        noteStart[i] = currTime;
        cin >> noteLen;
        currTime += noteLen;
    }

    //answer the queries
    long long beatNum;
    for (int i = 0; i < numQueries; i++)
    {
        cin >> beatNum;
        auto pos = upper_bound(noteStart, noteStart + numNotes, beatNum);
        cout << pos - noteStart << endl;
    }
    return 0;
}