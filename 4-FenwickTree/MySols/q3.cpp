#include <iostream>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;
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
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    pii *cows = new pii[numCows];
    for (int i = 0; i < numCows; i++)
    {
        cin >> cows[i].first;
        cows[i].second = i;
    }

    //set up
    sort(cows, cows + numCows);
    BIT bit(numCows);

    //go though the hair and find the ans
    long long *inversions = new long long[numCows];
    fill(inversions, inversions + numCows, 0);
    for (int i = numCows - 1; i >= 0; i--)
    {
        inversions[cows[i].first] += bit.query(cows[i].second);
        bit.updt(cows[i].second, 1);
    }

    //print the inversions
    long long aggSum = 0;
    for (int i = 0; i < numCows; i++)
    {
        cout << aggSum << endl;
        aggSum += inversions[i];
    }
    return 0;
}