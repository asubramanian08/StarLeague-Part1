#include <iostream>
#include <list>
using namespace std;

#define BIG_NUM 1000000000
struct level
{
    int height, width, index;
    level(int h, int w, int i) : height(h), width(w), index(i) {}
};

int main(void)
{
    //read
#ifndef HOME
    freopen("alake.in", "r", stdin);
    freopen("alake.out", "w", stdout);
#endif
    int numLevels;
    cin >> numLevels;
    list<level> levels;
    int w, h;
    for (int i = 0; i < numLevels; i++)
    {
        cin >> w >> h;
        levels.push_front(level(h, w, i));
    }

    //find the min + levels stuff
    auto min = levels.begin();
    for (auto l = levels.begin(); l != levels.end(); l++)
        if (min->height > l->height)
            min = l;
    levels.push_back(level(BIG_NUM, 0, -1));
    levels.push_front(level(BIG_NUM, 0, -1));

    long long *cost = new long long[numLevels];
    auto curr = min;
    long long soFar = 0, h1, h2;
    while (levels.size() > 3)
    {
        h1 = (++curr)->height;
        curr--;
        h2 = (--curr)->height;
        curr++;
        if (h1 < curr->height || h2 < curr->height)
        {
            h1 < curr->height ? curr++ : curr--;
            continue;
        }
        cost[curr->index] = soFar + curr->width;
        auto next = curr;
        h1 < h2 ? next++ : next--;
        next->width += curr->width;
        soFar += curr->width * (long long)(next->height - curr->height);
        levels.erase(curr);
        curr = next;
    }
    cost[curr->index] = soFar + curr->width;

    //print and delete
    for (int i = 0; i < numLevels; i++)
        cout << cost[i] << endl;
    delete[] cost;
    return 0;
}