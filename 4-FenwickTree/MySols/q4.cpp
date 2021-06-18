#include <iostream>
#include <algorithm>
using namespace std;

#define NA -1
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
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    int *pos = new int[numCows];
    fill(pos, pos + numCows, NA);
    int cow, ans = 0, currOpen = 0;
    BIT bit(numCows);
    for (int i = 0; i < numCows * 2; i++)
    {
        cin >> cow;
        cow--;
        if (pos[cow] == NA) //opening
        {
            pos[cow] = currOpen;
            currOpen++;
            bit.updt(pos[cow], 1);
        }
        else //closing
        {
            ans += bit.query(currOpen - 1) - bit.query((pos[cow]));
            bit.updt(pos[cow], -1);
        }
    }
    cout << ans << endl;
    delete[] pos;
    return 0;
}