#include <iostream>
#include <string>
using namespace std;

string expr;
string::iterator strIter;
#define MOD 1000000007
int doExpr(int num1, int num2, char oper);
int getNum(void);
int calcExpr();

int doExpr(int num1, int num2, char oper)
{
    int ans;
    if (oper == '+')
        ans = num1 + num2;
    else if (oper == '-')
        ans = num1 - num2;
    else //if (oper == '*')
        ans = num1 * num2;
    return ans % MOD;
}
int getNum(void)
{
    if (*strIter == ' ')
        strIter++;
    if (*strIter == '(')
        return calcExpr();
    int ans = 0;
    while (*strIter >= '0' && *strIter <= '9')
    {
        ans = (ans * 10) + (*strIter - '0');
        strIter++;
    }
    return ans;
}
int calcExpr()
{
    strIter++;
    int num1 = 0, num2 = getNum(), numCurr;
    char oper = '+', operCurr;
    while (*strIter != ')')
    {
        operCurr = *strIter;
        strIter++;
        if (operCurr == ' ')
            continue;
        numCurr = getNum();
        if (operCurr == '*')
            num2 = doExpr(num2, numCurr, '*');
        else
        {
            num1 = doExpr(num1, num2, oper);
            num2 = numCurr;
            oper = operCurr;
        }
    }
    if (*strIter == ' ')
        strIter++;
    strIter++;
    return doExpr(num1, num2, oper);
}

int main(void)
{
    //read
#ifndef HOME
    freopen("expression.in", "r", stdin);
    freopen("expression.out", "w", stdout);
#endif
    getline(cin, expr);
    expr.insert(expr.begin(), '(');
    expr.pop_back(); //the end line
    expr.push_back(')');
    strIter = expr.begin();
    cout << calcExpr() << endl;
    return 0;
}