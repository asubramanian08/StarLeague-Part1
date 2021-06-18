#include <iostream>
#include <stack>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("submatrix1.in", "r", stdin);
    freopen("submatrix1.out", "w", stdout);
#endif
    int rows, cols;
    cin >> rows >> cols;
    int **matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols + 2];
        matrix[i][0] = 0; //dummy 1
        for (int j = 1; j <= cols; j++)
            cin >> matrix[i][j];
        matrix[i][cols + 1] = 0; //dummy 2
    }

    //prep: vars and calcs
    cols += 2; //for the dummies -> trick histogram
    int *start = new int[cols];
    int *end = new int[cols];
    int maxRect = 0;
    stack<int> histogram;
    for (int i = 1; i < rows; i++)
        for (int j = 0; j < cols; j++) //change the matrix
            matrix[i][j] = matrix[i][j] ? matrix[i - 1][j] + 1 : 0;

    //do histogram for each column
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) //find end
        {
            while (!histogram.empty() && matrix[i][histogram.top()] > matrix[i][j])
            {
                end[histogram.top()] = j;
                histogram.pop();
            }
            histogram.push(j);
        }
        while (!histogram.empty())
            histogram.pop();
        for (int j = cols - 1; j >= 0; j--) //find start
        {
            while (!histogram.empty() && matrix[i][histogram.top()] > matrix[i][j])
            {
                start[histogram.top()] = j;
                histogram.pop();
            }
            histogram.push(j);
        }
        while (!histogram.empty())
            histogram.pop();
        for (int j = 0; j < cols; j++) //calc the max
            maxRect = max(maxRect, matrix[i][j] * (end[j] - start[j] - 1));
    }

    //print and delete
    cout << maxRect << endl;
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] start;
    delete[] end;
    return 0;
}