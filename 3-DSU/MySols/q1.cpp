#include <iostream>
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
    int numConns(int idx);
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
int DSU::numConns(int idx) { return sz[root(idx)]; }
DSU::~DSU()
{
    delete[] id;
    delete[] sz;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);
#endif
    int numEle, numConns;
    cin >> numEle >> numConns;
    pair<int, int> *edges = new pair<int, int>[numConns];
    for (int i = 0; i < numConns; i++)
        cin >> edges[i].first >> edges[i].second;

    //process
    DSU graph(numEle + 1);
    bool is_cycle = false;
    sort(edges, edges + numConns);
    for (int i = 0; i < numConns; i++)
    {
        if (i != numConns - 1 && edges[i] == edges[i + 1])
            continue;
        is_cycle |= graph.is_connected(edges[i].first, edges[i].second);
        graph.connect(edges[i].first, edges[i].second);
    }

    //print and delete
    delete[] edges;
    cout << (is_cycle ? "YES" : "NO") << endl;
    return 0;
}