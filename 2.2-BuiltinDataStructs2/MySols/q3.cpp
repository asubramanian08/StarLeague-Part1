#include <iostream>
#include <queue>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("baying.in", "r", stdin);
    freopen("baying.out", "w", stdout);
#endif
    long long start, times,
        m1, a1, d1,
        m2, a2, d2;
    cin >> start >> times >>
        m1 >> a1 >> d1 >>
        m2 >> a2 >> d2;

    //run the priority queue
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    long long last;
    pq.push(start);
    for (long long i = 0; i < times; i++)
    {
        for (last = pq.top(); !pq.empty() && last == pq.top(); pq.pop())
            ;
        pq.push(m1 * last / d1 + a1);
        pq.push(m2 * last / d2 + a2);
    }

    //print
    cout << last << endl;
    return 0;
}