#include <iostream>
#include <queue>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("milking.in", "r", stdin);
    freopen("milking.out", "w", stdout);
#endif
    int numCows, numMachines;
    cin >> numCows >> numMachines;
    queue<int> cowLine;
    vector<int> *cowList = new vector<int>[numMachines];
    char action;
    int index;
    while (cin >> action >> index)
    {
        if (action == 'C')
            cowLine.push(index);
        else
        {
            cowList[index - 1].push_back(cowLine.front());
            cowLine.pop();
        }
    }

    //print and delete
    for (int i = 0; i < numMachines; i++)
    {
        cout << i + 1 << ' ';
        for (int cow : cowList[i])
            cout << cow << ' ';
        cout << endl;
    }
    delete[] cowList;
    return 0;
}