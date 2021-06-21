#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

#define NA -1
using pib = pair<int, bool>;

int main(void)
{
    //read
#ifndef HOME
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);
#endif
    int paintLen;
    cin >> paintLen;
    int *start = new int[paintLen];
    fill(start, start + paintLen, NA);
    int *end = new int[paintLen];
    int paint;
    stack<int> colors;
    bool *vis = new bool[paintLen + 1];
    fill(vis, vis + paintLen + 1, false);
    for (int i = 0; i < paintLen; i++)
    {
        cin >> paint;
        //ensureing valid
        if (!vis[paint])
            colors.push(paint);
        vis[paint] = true;
        while (!colors.empty() && colors.top() != paint)
            colors.pop();
        if (colors.empty() && paint != 0) //not valid
        {
            cout << -1 << endl;
            return 0;
        }

        //round counting prep
        if (paint == 0)
            continue;
        paint--;
        if (start[paint] == NA)
            start[paint] = i;
        end[paint] = i + 1;
    }

    //make the event points
    pib *events = new pib[paintLen * 2];
    int onCount = 0;
    for (int i = 0; i < paintLen; i++)
        if (start[i] != NA)
        {
            events[onCount * 2] = make_pair(start[i], true);
            events[onCount * 2 + 1] = make_pair(end[i], false);
            onCount++;
        }
    sort(events, events + onCount * 2);

    //run though
    int maxOn = 0, currOn = 0;
    for (int i = 0; i < onCount * 2; i++)
    {
        events[i].second ? currOn++ : currOn--;
        maxOn = max(maxOn, currOn);
    }

    //print and delete
    cout << maxOn << endl;
    delete[] start;
    delete[] end;
    delete[] events;
    return 0;
}