#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU
{
private:
    int *id;
    int *sz;

public:
    DSU(int n_ele);
    //find its first parent
    int root(int idx);
    bool is_connected(int n1, int n2);
    void connect(int n1, int n2);
    int compSize(int idx);
    ~DSU();
};
DSU::DSU(int n_ele)
{
    id = new int[n_ele];
    sz = new int[n_ele];
    for (int i = 0; i < n_ele; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
}
int DSU::root(int idx)
{
    while (idx != id[idx])
    {
        id[idx] = id[id[idx]];
        idx = id[idx];
    }
    return idx;
}
bool DSU::is_connected(int n1, int n2) { return root(n1) == root(n2); }
void DSU::connect(int n1, int n2)
{
    int i = root(n1), j = root(n2);
    if (i == j)
        return;
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }
}
int DSU::compSize(int idx) { return sz[root(idx)]; }
DSU::~DSU()
{
    delete[] id;
    delete[] sz;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
#endif
    int numCows, numConns;
    cin >> numCows >> numConns;
    vector<int> *conns = new vector<int>[numCows];
    int c1, c2;
    for (int i = 0; i < numConns; i++)
    {
        cin >> c1 >> c2;
        c1--, c2--;
        conns[c1].push_back(c2);
        conns[c2].push_back(c1);
    }
    int *order = new int[numCows];
    for (int i = 0; i < numCows; i++)
    {
        cin >> order[i];
        order[i]--;
    }

    //setup
    DSU dsu(numCows);
    bool *farmConn = new bool[numCows];
    bool *farmOpen = new bool[numCows];
    fill(farmOpen, farmOpen + numCows, false);

    //keep openning farms
    for (int i = numCows - 1; i >= 0; i--)
    {
        farmOpen[order[i]] = true;
        for (int next : conns[order[i]])
            if (farmOpen[next])
                dsu.connect(order[i], next);
        farmConn[i] = dsu.compSize(order[i]) == numCows - i;
    }

    //print and delete
    for (int i = 0; i < numCows; i++)
        cout << (farmConn[i] ? "YES" : "NO") << '\n';
    return 0;
}