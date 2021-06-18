#include <iostream>
#include <set>
using namespace std;

using bale = pair<int, long long>;
#define BIG_NUM 1000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);
#endif
    int numBales;
    long long minFlavor;
    cin >> numBales >> minFlavor;
    bale *bales = new bale[numBales];
    for (int i = 0; i < numBales; i++)
        cin >> bales[i].second >> bales[i].first;

    //go though the bales
    int end = 0, minSpice = BIG_NUM;
    long long currFlavor = 0;
    multiset<bale, greater<bale>> on;
    for (int start = 0; start < numBales; start++)
    {
        while (end < numBales && currFlavor < minFlavor)
        {
            on.insert(bales[end]);
            currFlavor += bales[end].second;
            end++;
        }
        if (currFlavor < minFlavor)
            break;
        minSpice = min(minSpice, on.begin()->first);
        on.erase(on.lower_bound(bales[start]));
        currFlavor -= bales[start].second;
    }

    //print and delete
    cout << minSpice << endl;
    delete[] bales;
    return 0;
}