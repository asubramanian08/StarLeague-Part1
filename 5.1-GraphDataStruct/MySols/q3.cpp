#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int tree = 0, back = 0, ahead = 0, cross = 0;
vector<int> *conns;
set<int> ansestors;
multiset<int> looking;
bool *vis;

void dfs(int node)
{
    vis[node] = true;
    ansestors.insert(node);
    ahead += looking.count(node);
    cross -= looking.count(node);
    looking.erase(node);

    vector<int> children;
    vector<int> myLook;
    for (int next : conns[node])
        if (!vis[next])
        {
            children.push_back(next);
            tree++;
        }
        else if (ansestors.find(next) != ansestors.end())
            back++;
        else
        {
            myLook.push_back(next);
            looking.insert(next);
            cross++;
        }

    for (int next : children) //go to children
        if (!vis[next])
            dfs(next);
        else
            tree--, ahead++;
    for (int look : myLook) //erase my looks
        if (looking.find(look) != looking.end())
            looking.erase(looking.lower_bound(look));
    ansestors.erase(node);
}

int main(void)
{
    //read
#ifndef HOME
    freopen("dfsedges.in", "r", stdin);
    freopen("dfsedges.out", "w", stdout);
#endif
    int numNodes, numConns;
    cin >> numNodes >> numConns;
    conns = new vector<int>[numNodes];
    int nd1, nd2;
    for (int i = 0; i < numConns; i++)
    {
        cin >> nd1 >> nd2;
        nd1--, nd2--;
        conns[nd1].push_back(nd2);
    }

    //run the dfs
    for (int i = 0; i < numNodes; i++)
        sort(conns[i].begin(), conns[i].end());
    vis = new bool[numNodes];
    fill(vis, vis + numNodes, false);
    for (int i = 0; i < numNodes; i++)
        if (!vis[i])
            dfs(i);

    //print and delete
    cout << tree << endl
         << back << endl
         << ahead << endl
         << cross << endl;
    delete[] conns;
    delete[] vis;
    return 0;
}