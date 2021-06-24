#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);
#endif
    int numCows, numConn;
    cin >> numCows >> numConn;
    int *milkTime = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> milkTime[i];
    vector<int> *graph = new vector<int>[numCows];
    int *inDeg = new int[numCows];
    fill(inDeg, inDeg + numCows, 0);
    int c1, c2;
    for (int i = 0; i < numConn; i++)
    {
        cin >> c1 >> c2;
        c1--, c2--;
        graph[c1].push_back(c2);
        inDeg[c2]++;
    }

    //though topological order, find end time
    int *endTime = new int[numCows];
    fill(endTime, endTime + numCows, 0);
    queue<int> q;
    for (int i = 0; i < numCows; i++)
        if (inDeg[i] == 0)
            q.push(i);
    int node;
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        endTime[node] += milkTime[node];
        for (auto next : graph[node])
        {
            endTime[next] = max(endTime[next], endTime[node]);
            if (--inDeg[next] == 0)
                q.push(next);
        }
    }

    //print and delete
    int lastTime = 0;
    for (int i = 0; i < numCows; i++)
        lastTime = max(lastTime, endTime[i]);
    cout << lastTime;
    delete[] milkTime;
    delete[] graph;
    delete[] inDeg;
    delete[] endTime;
    return 0;
}