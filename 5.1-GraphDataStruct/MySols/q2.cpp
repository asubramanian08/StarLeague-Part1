#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> *conns;
bool *marked;
bool *type;
bool dfs(int node, bool makeType)
{
    if (marked[node])
        return type[node] == makeType;
    marked[node] = true;
    type[node] = makeType;
    for (int next : conns[node])
        if (!dfs(next, !type[node]))
            return false;
    return true;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("paintbarns.in", "r", stdin);
    freopen("paintbarns.out", "w", stdout);
#endif
    int numBarns, numConns;
    cin >> numBarns >> numConns;
    conns = new vector<int>[numBarns];
    int b1, b2;
    for (int i = 0; i < numConns; i++)
    {
        cin >> b1 >> b2;
        b1--, b2--;
        conns[b1].push_back(b2);
        conns[b2].push_back(b1);
    }

    //find the DFS, mark and answer
    marked = new bool[numBarns];
    fill(marked, marked + numBarns, false);
    type = new bool[numBarns];
    bool ans = true;
    for (int i = 0; i < numBarns; i++)
        if (marked[i] == false)
            ans &= dfs(i, true); //mark is arbitrary

    //print and delete
    cout << (ans ? "YES" : "NO") << endl;
    delete[] conns;
    delete[] marked;
    delete[] type;
    return 0;
}