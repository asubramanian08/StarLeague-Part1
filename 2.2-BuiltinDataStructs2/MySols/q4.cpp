//most of the code copied from lesson 2.1 q3
#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("submatrix2.in", "r", stdin);
    freopen("submatrix2.out", "w", stdout);
#endif
    int rows, cols;
    cin >> rows >> cols;
    char **matrix = new char *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new char[cols + 2];
        matrix[i][0] = 0; //dummy 1
        for (int j = 1; j <= cols; j++)
            cin >> matrix[i][j];
        matrix[i][cols + 1] = 0; //dummy 2
    }

    //prep: vars and calcs
    cols += 2; //for the dummies -> trick histogram
    int *start = new int[cols];
    int *end = new int[cols];
    int *row = new int[cols];
    int maxRect = 0;
    stack<int> histogram;

    //do histogram for each column
    for (int alpha = 0; alpha < 26; alpha++)
    {
        fill(row, row + cols, 0);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++) //set row
                row[j] = matrix[i][j] - 'a' == alpha ? row[j] + 1 : 0;
            for (int j = 0; j < cols; j++) //find end
            {
                while (!histogram.empty() && row[histogram.top()] > row[j])
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
                while (!histogram.empty() && row[histogram.top()] > row[j])
                {
                    start[histogram.top()] = j;
                    histogram.pop();
                }
                histogram.push(j);
            }
            while (!histogram.empty())
                histogram.pop();
            for (int j = 0; j < cols; j++) //calc the max
                maxRect = max(maxRect, row[j] * (end[j] - start[j] - 1));
        }
    }

    //print and delete
    cout << maxRect << endl;
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] start;
    delete[] end;
    delete[] row;
    return 0;
}