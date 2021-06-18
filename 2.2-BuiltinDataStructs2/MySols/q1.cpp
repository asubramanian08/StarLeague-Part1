#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

struct entry
{
    int day, id, change;
    bool operator<(const entry &lg) const { return day < lg.day; }
};

int main(void)
{
    //read
#ifndef HOME
    freopen("measurement.in", "r", stdin);
    freopen("measurement.out", "w", stdout);
#endif
    int numEntries, defaultMilk;
    cin >> numEntries >> defaultMilk;
    entry *entries = new entry[numEntries];
    char is_pos;
    for (int i = 0; i < numEntries; i++)
    {
        cin >> entries[i].day >> entries[i].id >> is_pos >> entries[i].change;
        entries[i].change *= is_pos == '+' ? 1 : -1;
    }

    //prep -> sort + map + set
    sort(entries, entries + numEntries);
    map<int, int> production;
    for (int i = 0; i < numEntries; i++)
        production[entries[i].id] = defaultMilk;
    multiset<int, greater<int>> highestMilk;
    //one extra for everyone else
    for (int i = 0; i <= production.size(); i++)
        highestMilk.insert(defaultMilk);

    //run the simulation
    int changeCount = 0;
    bool sole_start, start;
    auto is_s = [&production, &entries, &highestMilk](int i)
    { return production[entries[i].id] == *highestMilk.begin(); };
    auto is_ss = [&production, &entries, &highestMilk, &is_s](int i)
    {
        if (!is_s(i))
            return false;
        if (highestMilk.size() == 1)
            return true;
        auto temp = highestMilk.begin();
        temp++;
        return *temp != *highestMilk.begin();
    };
    for (int i = 0; i < numEntries; i++)
    {
        sole_start = is_ss(i);
        start = is_s(i);
        highestMilk.erase(highestMilk.lower_bound(production[entries[i].id]));
        production[entries[i].id] += entries[i].change;
        highestMilk.insert(production[entries[i].id]);
        if (sole_start != is_ss(i) || start != is_s(i))
            changeCount++;
    }

    //print and delete
    cout << changeCount << endl;
    delete[] entries;
    return 0;
}