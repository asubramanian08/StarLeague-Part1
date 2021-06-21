#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

using pii = pair<int, int>;
#define MOD 1000000007
#define TRACK_LEN 200100
class BIT
{
private:
    int *bTree;
    int elements;

public:
    BIT(int elem);
    BIT(int elem, int *initialize, int numInit);
    ~BIT() { delete[] bTree; }
    int query(int node);
    void updt(int node, int cng);
};
BIT::BIT(int elem)
{
    elements = elem;
    bTree = new int[elem + 1];
    for (int i = 1; i <= elem; i++)
        bTree[i] = 0;
}
BIT::BIT(int elem, int *initialize, int numInit)
{
    elements = elem;
    bTree = new int[elem + 1];
    for (int i = 1; i <= elem; i++)
        bTree[i] = 0;
    for (int i = 0; i < numInit; i++)
        updt(i, initialize[i]);
}
int BIT::query(int node)
{
    if (node == -1)
        return 0;
    int sum = 0;
    for (int i = node + 1; i > 0; i -= (i & -i))
        sum += bTree[i];
    return sum;
}
void BIT::updt(int node, int cng)
{
    for (int i = node + 1; i <= elements; i += (i & -i))
        bTree[i] += cng;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("relayrace.in", "r", stdin);
    freopen("relayrace.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    pii *cows = new pii[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;

    //do it
    BIT bit(TRACK_LEN);
    int *eventPoints = new int[numCows * 2];
    for (int i = 0; i < numCows * 2; i++)
        eventPoints[i] = i;
    sort(eventPoints, eventPoints + numCows * 2, [cows, numCows](int i1, int i2)
         {
             int pos1 = i1 < numCows ? cows[i1].first : cows[i1 - numCows].second;
             int pos2 = i2 < numCows ? cows[i2].first : cows[i2 - numCows].second;
             if (pos1 == pos2)
             {
                 if (i1 < numCows && i2 < numCows)
                     return cows[i1].second > cows[i2].second;
                 else
                     return i1 >= numCows;
             }
             return pos1 < pos2;
         });
    int ans = 0;
    for (int i = 0; i < numCows * 2; i++)
        if (eventPoints[i] < numCows)
        {
            bit.updt(cows[eventPoints[i]].second, 1);
            ans += bit.query(cows[eventPoints[i]].second - 1);
            ans %= MOD;
        }
        else
            bit.updt(cows[eventPoints[i] - numCows].second, -1);

    //print and delete
    cout << ans << endl;
    delete[] cows;
    delete[] eventPoints;
    return 0;
}