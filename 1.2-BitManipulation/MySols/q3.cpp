#include <iostream>
#include <set>
using namespace std;

using pii = pair<int, int>;

inline int lowestBit(int n) { return n & -n; }
int highestBit(int n)
{
    while (n != lowestBit(n))
        n -= lowestBit(n);
    return n;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("cowxor2.in", "r", stdin);
    freopen("cowxor2.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    int *id = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> id[i];

    //make the prefixSum
    int *xor_ps = new int[numCows];
    int total = 0;
    for (int i = 0; i < numCows; i++)
        xor_ps[i] = total ^= id[i];

    //find the maximmum length
    int maxVal = 0, bestSearch;
    for (int i = 0; i < numCows; i++)
        maxVal = max(maxVal, id[i]);
    bestSearch = (highestBit(maxVal) << 1) - 1;

    //run through the best for each cow
    set<pii, greater<pii>> s;
    int bestVal = 0, start, end, best;
    set<pii, greater<pii>>::iterator iter;
    for (int i = 0; i < numCows; i++)
    {
        best = ~xor_ps[i] & bestSearch;
        while ((iter = s.lower_bound(pii(best, i)))->first > 0 &&
               best > 0 &&
               highestBit(iter->first) != highestBit(best))
            best -= highestBit(best);
        //reuse the best value
        best = iter->first == 0 || best == 0 ? xor_ps[i] : xor_ps[i] ^ iter->first;
        if (bestVal < best)
        {
            bestVal = best;
            start = iter->second + 2;
            end = i + 1;
        }
        s.insert(pii(xor_ps[i], i));
    }

    //print and delete
    cout << bestVal << ' ' << start << ' ' << end << endl;
    delete[] id;
    delete[] xor_ps;
    return 0;
}