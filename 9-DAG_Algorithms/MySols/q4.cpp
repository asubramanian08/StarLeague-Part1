#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("dizzy.in", "r", stdin);
    freopen("dizzy.out", "w", stdout);
#endif
    int numNodes, numConns, junk; //junk = num2D_conns
    cin >> numNodes >> numConns >> junk;
    vector<int> *graph = new vector<int>[numNodes];
    int *inDeg = new int[numNodes];
    fill(inDeg, inDeg + numNodes, 0);
    int n1, n2;
    for (int i = 0; i < numConns; i++)
    {
        cin >> n1 >> n2;
        n1--, n2--;
        graph[n1].push_back(n2);
        inDeg[n2]++;
    }

    //run topological
    queue<int> q;
    for (int i = 0; i < numNodes; i++)
        if (inDeg[i] == 0)
            q.push(i);
    int ans;
    for (ans = numNodes; !q.empty(); q.pop(), ans--)
        for (auto next : graph[q.front()])
            if (--inDeg[next] == 0)
                q.push(next);

    //print and delete
    cout << (ans == 0 ? "Yes" : "No") << endl;
    delete[] graph;
    delete[] inDeg;
    return 0;
}