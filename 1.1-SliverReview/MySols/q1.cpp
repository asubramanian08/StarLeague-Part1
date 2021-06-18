#include <iostream>
using namespace std;

#define PIPE_LOC 52
int matrix[PIPE_LOC][PIPE_LOC] = {0};
#define NA -1

void mergePipes(int first, int second, int ref)
{
    int maxFlow = min(matrix[ref][first], matrix[ref][second]);
    matrix[first][second] += maxFlow;
    matrix[second][first] += maxFlow;
    matrix[ref][first] = matrix[ref][second] =
        matrix[first][ref] = matrix[second][ref] = 0;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("totalflow.in", "r", stdin);
    freopen("totalflow.out", "w", stdout);
#endif
    int numPipes;
    cin >> numPipes;
    char pos1, pos2;
    int flow;
    for (int i = 0; i < numPipes; i++)
    {
        cin >> pos1 >> pos2 >> flow;
        pos1 -= (pos1 >= 'a' ? ('a' - 26) : 'A');
        pos2 -= (pos2 >= 'a' ? ('a' - 26) : 'A');
        matrix[pos1][pos2] += flow;
        matrix[pos2][pos1] += flow;
    }

    //just keep applying rules
    bool change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < PIPE_LOC; i++)
        {
            if (i == 'A' - 'A' || i == 'Z' - 'A')
                continue;
            //find the values to determine if changeable or not
            //more efficient would be to have arrays and just confirm their values
            int first = NA, second = NA;
            bool third = false;
            for (int j = 0; j < PIPE_LOC && !third; j++)
                if (matrix[i][j] == 0)
                    continue;
                else if (first == NA)
                    first = j;
                else if (second == NA)
                    second = j;
                else
                    third = true;
            //do the actual rules
            if (third || first == NA)
                continue;
            change = true;
            if (second != NA)
                mergePipes(first, second, i);
            else
                matrix[i][first] = matrix[first][i] = 0;
        }
    }

    //print
    cout << matrix['A' - 'A']['Z' - 'A'] << endl;
    return 0;
}