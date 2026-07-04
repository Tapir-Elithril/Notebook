/*
There are N tasks arranged in a sequence on a machine waiting to be executed, and their order cannot be changed. You need to divide these N tasks into several groups, each containing several consecutive tasks. 
Starting from time 0, the tasks are processed in groups, and the time required to execute the i-th task is Ti. 
Additionally, the machine requires a startup time S before each group of tasks begins, so the time required for a group of tasks is the startup time S plus the sum of the time required for each task in this group.
After a task is executed, it will wait briefly in the machine until all tasks in that group are completely executed. 
That is to say, the tasks in the same group will be completed at the same time. 
The cost of each task is its completion time multiplied by a cost coefficient Ci.
Please plan a grouping scheme for the machine to minimize the total cost.
For all testing data, 1≤N≤1000,0≤S≤50,1≤Ti,Ci≤100
5
1
1 3
3 2
4 3
2 3
1 4

153
We have grouped the tasks into 3 groups, which are {1, 2}, {3}, {4, 5}.
The completion time corresponding to each task, in the order of the task numbers, is {5, 5, 10, 14, 14}. 
Similarly, the cost corresponding to each task, again in the order of the task numbers, is {15, 10, 30, 42, 56}. 
The total cost of these tasks is 153.
*/

#include <stdio.h>
#define MAXN 1000
long long min_cost(int N, int S, int T[], int C[]);
int main() {
    int N, S;
    int T[MAXN], C[MAXN];
    scanf("%d%d", &N, &S);
    for (int i = 0;i < N; ++ i) {
        scanf("%d%d", &T[i], &C[i]);
    }
    printf("%lld\n", min_cost(N, S, T, C));
    return 0;
}
long long min_cost(int N, int S, int T[], int C[]) 
{
    long long dp[MAXN + 1];
    dp[0] = 0; // No tasks, no cost
    for (int i = 1; i <= N; ++i)
    {
        dp[i] = 2147482648;  // Initialize dp[i] to a large number
        long long sum_time = 0;  // Sum of task times in the current group
        long long max_cost = 0;  // Max cost coefficient in the current group
        // Try all possible starting points for the group ending at task i
        for (int j = i - 1; j >= 0; --j) {
            sum_time += T[j];  // Add the task time of task j to the group
            max_cost = (max_cost > C[j] ? max_cost : C[j]);  // Update the max cost coefficient
            long long completion_time = sum_time + S;  // Completion time for this group
            // Calculate cost for this partition
            long long group_cost = completion_time * C[j];
            dp[i] = dp[i] < dp[j] + group_cost ? dp[i] : dp[j] + group_cost;
        }
    }
    return dp[N];
}
