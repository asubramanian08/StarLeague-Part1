#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define NA -1

class DSU
{
private:
    vector<int> id, sz;

public:
    DSU(int n_ele = 0);
    //find its first parent
    int root(int idx);
    bool is_connected(int n1, int n2);
    void connect(int n1, int n2);
    void addEle(void);
    int compSize(int idx);
    int numEle(void);
};
DSU::DSU(int n_ele)
{
    id.resize(n_ele);
    sz.resize(n_ele);
    for (int i = 0; i < n_ele; i++)
        addEle();
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
void DSU::addEle(void)
{
    id.push_back(id.size());
    sz.push_back(1);
}
int DSU::compSize(int idx) { return sz[root(idx)]; }
int DSU::numEle(void) { return id.size(); }

int main(void)
{
    //read
    map<int, int> convert;
    vector<int> counterPart;
    vector<pair<int, int>> games;
    DSU teammates;
#ifndef HOME
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
#endif
    int numGames;
    cin >> numGames;
    int c1, c2;
    auto ensureAdded = [&convert, &counterPart, &teammates](int c)
    {
        if (convert.find(c) != convert.end())
            return;
        convert[c] = counterPart.size();
        teammates.addEle();
        counterPart.push_back(NA); //dummy
    };
    for (int i = 0; i < numGames; i++)
    {
        cin >> c1 >> c2;
        ensureAdded(c1);
        ensureAdded(c2);
        c1 = convert[c1];
        c2 = convert[c2];
        games.push_back(pair<int, int>(c1, c2));
        if (counterPart[c1] != NA)
            teammates.connect(counterPart[c1], c2);
        else
            counterPart[c1] = c2;
        if (counterPart[c2] != NA)
            teammates.connect(counterPart[c2], c1);
        else
            counterPart[c2] = c1;
    }

    //loop though games and find the maxTeam
    int maxTeam = 0, visEle = counterPart.size();
    teammates.addEle();
    for (auto game : games)
    {
        if (teammates.is_connected(game.first, visEle))
            continue;
        maxTeam += max(teammates.compSize(game.first), teammates.compSize(game.second));
        teammates.connect(game.first, visEle);
        teammates.connect(game.second, visEle);
    }

    //print
    cout << maxTeam << endl;
    return 0;
}