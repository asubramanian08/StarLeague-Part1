#include <iostream>
#include <vector>
using namespace std;

vector<int> *graph;
int *height;
#define BIG_NUM 1000000000
int findHeight(int node, int par)
{
    height[node] = BIG_NUM;
    for (auto next : graph[node])
        if (next != par)
            height[node] = min(height[node], findHeight(next, node));
    height[node] = height[node] == BIG_NUM ? 0 : height[node] + 1;
    return height[node];
}
int DFS(int node, int depth, int par)
{
    if (height[node] <= depth)
        return 1;
    int ans = 0;
    for (auto next : graph[node])
        if (next != par)
            ans += DFS(next, depth + 1, node);
    return ans;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);
#endif
    int numBarns, source;
    cin >> numBarns >> source;
    source--;
    graph = new vector<int>[numBarns];
    int b1, b2;
    for (int i = 1; i < numBarns; i++)
    {
        cin >> b1 >> b2;
        b1--, b2--;
        graph[b1].push_back(b2);
        graph[b2].push_back(b1);
    }

    //find the height then DFS
    height = new int[numBarns];
    findHeight(source, -1);
    int ans = DFS(source, 0, -1);
    ans += graph[source].size() == 1;

    //print and delete
    cout << ans << endl;
    delete[] graph;
    delete[] height;
    return 0;
}