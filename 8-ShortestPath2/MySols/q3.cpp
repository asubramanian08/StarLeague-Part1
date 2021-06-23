#include <iostream>
#include <string>
using namespace std;

#define char_size 26
bool converts[char_size][char_size] = {false};
bool is_unique[char_size];
int main(void)
{
    //read
#ifndef HOME
    freopen("decrypt.in", "r", stdin);
    freopen("decrypt.out", "w", stdout);
#endif
    int numTrans, numQueries;
    cin >> numTrans >> numQueries;
    char from, to;
    for (int i = 0; i < numTrans; i++)
    {
        cin >> from >> to;
        converts[from - 'a'][to - 'a'] = true;
    }

    //find all connectivity, modified floyd-warshall
    for (int i = 0; i < char_size; i++)
        for (int j = 0; j < char_size; j++)
            if (converts[j][i])
                for (int k = 0; k < char_size; k++)
                    converts[j][k] |= converts[i][k];
    for (int i = 0; i < char_size; i++)
    {
        is_unique[i] = true;
        for (int j = 0; j < char_size; j++)
            if (i != j)
                is_unique[i] &= !converts[i][j];
            else
                converts[i][j] = true;
    }

    //go though the queries and print
    string wd1, wd2;
    bool currUnique, currConvert;
    for (int i = 0; i < numQueries; i++)
    {
        cin >> wd1 >> wd2;
        currConvert = wd1.size() == wd2.size();
        currUnique = true;
        for (int i = 0; i < wd1.size() && currConvert; i++)
        {
            currConvert = converts[wd1[i] - 'a'][wd2[i] - 'a'];
            currUnique &= is_unique[wd1[i] - 'a'];
        }
        if (!currConvert)
            cout << "NO" << endl;
        else if (currUnique)
            cout << "UNIQUE" << endl;
        else
            cout << "NOT UNIQUE" << endl;
    }
    return 0;
}