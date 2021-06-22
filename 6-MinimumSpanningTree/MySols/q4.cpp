#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
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

int endX, endY, numCols, numRows;
int *cols, *rows;
int getPos(int col, int row) { return col * numRows + row; }

int main(void)
{
    //read
#ifndef HOME
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
#endif
    cin >> endX >> endY >> numCols >> numRows;
    cols = new int[numCols + 2];
    rows = new int[numRows + 2];
    for (int i = 0; i < numCols; i++)
        cin >> cols[i];
    for (int i = 0; i < numRows; i++)
        cin >> rows[i];

    //prep
    cols[numCols] = endX;
    rows[numRows] = endY;
    numCols++, numRows++;
    cols[numCols] = 0;
    rows[numRows] = 0;
    sort(cols, cols + numCols + 1);
    sort(rows, rows + numRows + 1);
    for (int i = 0; i < numCols; i++)
        cols[i] = cols[i + 1] - cols[i];
    for (int i = 0; i < numRows; i++)
        rows[i] = rows[i + 1] - rows[i];
    sort(cols, cols + numCols);
    sort(rows, rows + numRows);
    int graphSize = numRows * numCols;
    DSU dsu(graphSize);

    //find the ans
    long long ans = 0;
    int currCol = 0, currRow = 0;
    while (currCol < numCols || currRow < numRows)
        if (currRow == numRows || (currRow < numRows && cols[currCol] < rows[currRow]))
        {
            for (int i = 0; i < numRows - 1; i++)
                if (!dsu.is_connected(getPos(currCol, i), getPos(currCol, i + 1)))
                {
                    dsu.connect(getPos(currCol, i), getPos(currCol, i + 1));
                    ans += cols[currCol];
                }
            currCol++;
        }
        else
        {
            for (int i = 0; i < numCols - 1; i++)
                if (!dsu.is_connected(getPos(i, currRow), getPos(i + 1, currRow)))
                {
                    dsu.connect(getPos(i, currRow), getPos(i + 1, currRow));
                    ans += rows[currRow];
                }
            currRow++;
        }

    //print and delete
    cout << ans << endl;
    delete[] cols;
    delete[] rows;
    return 0;
}