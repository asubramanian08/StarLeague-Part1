#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define NODE_SIZE 26
string inorder, preorder;
vector<char> postorder;
int in_idx[NODE_SIZE], pre_idx[NODE_SIZE];

void DFS(int node, int inStart, int inEnd)
{
    if (inStart != in_idx[node])
        DFS(preorder[pre_idx[node] + 1], inStart, in_idx[node] - 1);
    if (inEnd != in_idx[node])
        DFS(preorder[pre_idx[node] + (in_idx[node] - inStart) + 1], in_idx[node] + 1, inEnd);
    postorder.push_back(node + 'A');
}

int main(void)
{
    //read
#ifndef HOME
    freopen("heritage.in", "r", stdin);
    freopen("heritage.out", "w", stdout);
#endif
    cin >> inorder >> preorder;

    //find the indexes
    for (int i = 0; i < inorder.size(); i++)
    {
        inorder[i] -= 'A';
        preorder[i] -= 'A';
        in_idx[inorder[i]] = i;
        pre_idx[preorder[i]] = i;
    }

    //print
    DFS(preorder[0], 0, inorder.size() - 1); //do the dfs
    for (auto ch : postorder)
        cout << ch;
    return 0;
}