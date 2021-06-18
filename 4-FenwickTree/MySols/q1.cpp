#include <iostream>
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
//main numbers + BIT init
#ifndef HOME
    freopen("swalking.in", "r", stdin);
    freopen("swalking.out", "w", stdout);
#endif
    int numCows, numStalls, numLines, minCows;
    cin >> numCows >> numStalls >> numLines >> minCows;
    BIT stalls(numStalls + 1);

    //the init positions
    int *pos = new int[numCows];
    for (int i = 0; i < numCows; i++)
    {
        cin >> pos[i];
        stalls.updt(pos[i], 1);
    }

    //updt + process
    int oper, num1, num2, dist;
    for (int i = 0; i < numLines; i++)
    {
        cin >> oper >> num1 >> num2;
        if (oper == 0)
        {
            num1--;
            stalls.updt(pos[num1], -1);
            pos[num1] = num2;
            stalls.updt(num2, 1);
        }
        else if ((dist = stalls.query(num2) - stalls.query(num1 - 1)) > minCows)
            cout << dist << '\n';
    }

    return 0;
}