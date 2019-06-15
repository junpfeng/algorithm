/*************************************************************************
	> File Name: backbag.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年06月14日 星期五 21时37分37秒
    > n个重量和价值分为为wi和vi的物品集合里面，挑选总重量不超过W的物品集合
    > 求所有方案中挑选价值总和最大值
    > 输入：商品数量n、每个商品的重量和价值、被挑选的总重量w
 ************************************************************************/

#include<iostream>
#include <cstring>
using namespace std;


int n, W;
#define MAX_N 10
int w[MAX_N], v[MAX_N];

// j是重量上限，i是第几件物品（从0开始）
int rec(int i, int j)
{
    if (i == n)
    {
        // 已经没有商品了
        return 0;
    }
    else if (j < w[i]) // 这件商品的重量已经超过了剩余可选重量
    {
        // 无法挑选当前物品
        return rec(i + 1, j);
    }
    else
    {
        // 通过max来判别下一个是选还是不选，不选就下一个，选的话，就得把j-w[i]
        return max(rec(i + 1, j), rec(i + 1, j - w[i]) + v[i]); 
        // 这个就是出口：v[i]
    }
}

// ---------最朴素的解决方案-------------------
void solve01()
{
    printf("%d\n", rec(0, W));
}



//---------使用记忆化数组---------------------
//-----------改进了朴素方法------------
//-------全局变量的初值默认是0-------------
int dp[MAX_N + 1][MAX_N - 1]; //Dp数组
int rec02(int i, int j){
    // 已经计算过的格子，直接跳过
    if (dp[i][j] >= 0){
        // 已经计算过的话，就直接使用之前的结果
        return dp[i][j];
    }
    int res;
    if (i == n){
        res = 0;
    }else if (j < w[i])
    {
        res = rec02(i + 1, j);
    }else{
        res = max(rec02(i + 1, j), rec02(i + 1, j - w[i]) + v[i]);
    }

    return dp[i][j] = res;
}

void solve02(){
    memset(dp, -1, sizeof(dp));
    printf("%d\n", rec02(0, W));
}


// ---------逆向动态规划----------------

void solve03()
{
    for (int i = n - 1; i >= 0; --i)
        for (int j = 0; j <= W; ++j)
    if (j < w[i]){
        dp[i][j] = dp[i + 1][j];
    }else{
        dp[i][j] = max(dp[i+1][j], dp[i+1][j-w[i]] + v[i]);
    }
    printf("%d\n", dp[0][W]);
}

//----------正向动态规划---------------

void solve04()
{
    for (int i = 0; i < n; ++i)
    for (int j = 0; j <= W; ++j){
        if (j < w[i]){
            dp[i + 1][j] = dp[i][j];
        }else{
            dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
        }
    }
    printf("%d\n", dp[n][W]);
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> w[i];
        cin >> v[i];
    }
    cin >> W;
//    solve01();
//    solve02();
//    solve03();
      solve04();
}
