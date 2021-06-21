#include <iostream>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;
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
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    pii *cows = new pii[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;

    //make an array of all connections and sort
    pii *pairs = new pii[numCows * numCows];
    for (int i = 0; i < numCows; i++)
        for (int j = 0; j < numCows; j++)
            pairs[i * numCows + j] = make_pair(i, j);
    auto sqrDist = [&cows](int c1, int c2)
    { return (cows[c1].first - cows[c2].first) * (cows[c1].first - cows[c2].first) +
             (cows[c1].second - cows[c2].second) * (cows[c1].second - cows[c2].second); };
    sort(pairs, pairs + numCows * numCows, [&sqrDist](pii p1, pii p2)
         { return sqrDist(p1.first, p1.second) < sqrDist(p2.first, p2.second); });

    //run though the pairs
    DSU dsu(numCows);
    int radius = 0;
    for (int i = numCows; dsu.compSize(0) != numCows; i++)
    {
        radius = sqrDist(pairs[i].first, pairs[i].second);
        dsu.connect(pairs[i].first, pairs[i].second);
    }

    //print and delete
    cout << radius << endl;
    delete[] cows;
    delete[] pairs;
    return 0;
}