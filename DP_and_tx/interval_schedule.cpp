/*************************************************************************
	> File Name: interval_schedule.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年06月15日 星期六 13时41分42秒
    > 区间调度问题：对于一个问题，可以贪心的角度有很多时，就会出现
    > 其中一个角度是对的，而其他角度是错的，这也是贪心的缺点

    > 题目描述：有n项工作，每项工作 分别在s1时间开始，在t1时间结束。
    > 对于每项工作，你可以选择参加与否，一旦参加，要全程加入，且不能同时
    > 参加多项工作。求最多能参加几项工作。
 ************************************************************************/

#include<iostream>
using namespace std;
#include <utility>
#include <algorithm>


const int MAX_N = 100000;

// 输入: N项工作、每项的开始时间和结束时间
int N, S[MAX_N], T[MAX_N];

pair<int, int> itv[MAX_N];

void solve(){
    // 对pair进行字典序比较
    // 为了让结束时间早的工作排在前面、将T存入first,S存入second
    for (int i = 0; i < N; ++i){
        itv[i].first = T[i]; // 以结束时间为排序第一准则
        itv[i].second = S[i];
    }

    sort(itv, itv + N);
    int ans = 0, t = 0;
    for (int i = 0; i < N; ++i)
    {
        // 上一个正在做的工作的结束的时间，在当前任务的开始之前
        // 那么当前工作就可可以被做
        if (t < itv[i].second){
            ++ans;
            t = itv[i].first;
        }
    }
    printf("%d\n", ans);
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        cin >> S[i] >> T[i];
    }
    solve();
    return 0;
}
