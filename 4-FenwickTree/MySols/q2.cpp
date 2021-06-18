#include <iostream>
#include <algorithm>
using namespace std;

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
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    int *heights = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> heights[i];

    //change the heights -> now it looks for the number of cows shorter
    pair<int, int> *changer = new pair<int, int>[numCows];
    for (int i = 0; i < numCows; i++)
        changer[i].first = heights[i], changer[i].second = i;
    sort(changer, changer + numCows);
    for (int i = 0; i < numCows; i++)
        heights[changer[i].second] = (numCows - 1) - i;

    //fill in the left -> forward
    BIT leftFind(numCows);
    int *left = new int[numCows];
    for (int i = 0; i < numCows; i++)
    {
        left[i] = leftFind.query(heights[i]);
        leftFind.updt(heights[i], 1);
    }

    //fill in the left -> backward
    BIT rightFind(numCows);
    int *right = new int[numCows];
    for (int i = numCows - 1; i >= 0; i--)
    {
        right[i] = rightFind.query(heights[i]);
        rightFind.updt(heights[i], 1);
    }

    //calc, print and delete
    int unbalCount = 0;
    for (int i = 0; i < numCows; i++)
        unbalCount += left[i] > right[i] * 2 ||
                      right[i] > left[i] * 2;
    cout << unbalCount << endl;
    delete[] heights;
    delete[] changer;
    delete[] left;
    delete[] right;
    return 0;
}