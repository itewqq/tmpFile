#include <bits/stdc++.h>

#define rep(i, n) for (int i = 1; i <= (n) ; i++)
#define per(i, n) for (int i = (n); i >= 1 ; i--)
using namespace std;

const int maxn = 3005;
const int maxm = 305;

long double p[maxm][maxn];
int n, m, tmp;
long double ans;
long double dev[maxm], dp[maxm][maxn], rec[maxn];

int main()
{
    // freopen("coin.in", "r", stdin);
    // freopen("coin.out", "w", stdout);

    cin >> n >> m ; ans = 0;
    for (int j = 1; j <= (n) ; j++)
        for (int i = 1; i <= (m) ; i++)
            scanf("%d", &tmp), p[i][j] = tmp / 1000.0;
    for (int i = 1; i <= (m) ; i++)
    {
        dp[i][0] = 1;
        for (int j = 1; j <= (n) ; j++)
            dp[i][j] = dp[i][j - 1] * (1 - p[i][j]);//没被选中前缀积？
        dev[i] = 1 - dp[i][n];//选中？
    }
    for (int t = 1; t <= (n) ; t++)//第几个人？
    {
        int x = 1;
        for (int i = 1; i <= (m) ; i++)
            if (dev[x] < dev[i]) //最大的概率
                x = i;
        ans += dev[x];
        for (int j = 1; j <= (n) ; j++)
            rec[j] = dp[x][j];
        rec[0] = dp[x][0]; dp[x][0] = 0;
        for (int j = 1; j <= (n) ; j++)
            dp[x][j] = dp[x][j - 1] * (1 - p[x][j]) + rec[j - 1] * p[x][j];//选走一个之后的更新 dp[x][j]表示前j个里有n个人选了x的概率
        dev[x] -= dp[x][n];//？
    }
    printf("%.10lf", (double)ans);
    return 0;
}

/*

 2 2
 789 211
 333 667
 */
