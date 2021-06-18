#include <iostream>
#include <string>
using namespace std;

using test = pair<int, int>;

//from geeksforgeeks
int countSetBits(int n)
{
    unsigned int count = 0;
    while (n)
    {
        count += n & 1;
        n >>= 1;
    }
    return count;
}
int readBin()
{
    string strRep;
    cin >> strRep;
    int val = 0;
    for (char ch : strRep)
        val = (val << 1) | (ch - '0');
    return val;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("troughgame.in", "r", stdin);
    freopen("troughgame.out", "w", stdout);
#endif
    int numTroughs, numTests;
    cin >> numTroughs >> numTests;
    test *tests = new test[numTests];
    for (int i = 0; i < numTests; i++)
    {
        tests[i].first = readBin();
        cin >> tests[i].second;
    }

    //check all combinations
    int combinations = 1 << numTroughs;
    int sol = 0;
    bool has_sol = false, is_sol;
    for (int posAns = 0; posAns < combinations; posAns++)
    {
        is_sol = true;
        for (int i = 0; i < numTests && is_sol; i++)
            is_sol = countSetBits(posAns & tests[i].first) == tests[i].second;
        if (!is_sol)
            continue;
        if (has_sol)
        {
            cout << "NOT UNIQUE" << endl;
            return 0;
        }
        sol = posAns;
        has_sol = true;
    }

    //print and delete
    if (!has_sol)
        cout << "IMPOSSIBLE";
    else
        for (int i = numTroughs - 1; i >= 0; i--)
            cout << bool(sol & 1 << i);
    cout << endl;
    delete[] tests;
    return 0;
}