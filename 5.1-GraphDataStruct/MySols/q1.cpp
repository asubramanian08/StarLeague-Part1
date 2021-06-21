#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define BIG_NUM 1000000000
#define NA -1
int *cap;
vector<int> *conns;
int p1, p2; //excluded ones
bool *vis;
int dfs(int node)
{
    if (vis[node])
        return 0;
    vis[node] = true;
    int ans = cap[node];
    int search = node == p1 ? p2 : (node == p2 ? p1 : NA);
    for (int next : conns[node])
        if (next != search)
            ans += dfs(next);
        else //only remove one conn
            search = NA;
    return ans;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("divide.in", "r", stdin);
    freopen("divide.out", "w", stdout);
#endif
    int numCows, numConns;
    cin >> numCows >> numConns;
    cap = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cap[i];
    int c1, c2;
    conns = new vector<int>[numConns];
    for (int i = 0; i < numConns; i++)
    {
        cin >> c1 >> c2;
        c1--, c2--;
        conns[c1].push_back(c2);
        conns[c2].push_back(c1);
    }

    //loop though the connections and remove
    int minDiff = BIG_NUM, first, second;
    vis = new bool[numCows];
    for (int i = 0; i < numCows; i++)
        for (int j : conns[i])
        {
            p1 = i, p2 = j;
            fill(vis, vis + numCows, false);
            first = dfs(i);
            if (vis[j])
                continue;
            second = dfs(j);
            minDiff = min(minDiff, abs(first - second));
        }

    //print and delete
    cout << minDiff << endl;
    delete[] cap;
    delete[] conns;
    delete[] vis;
    return 0;
}