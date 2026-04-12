int numSquares(int n)
{
    int dp[10000];
    // 初始化：最坏情况全用1，所以dp[i]=i
    for (int i = 0; i <= n; i++) dp[i] = i;

    for (int i = 2; i <= n; i++)
    {
        // 试所有平方数
        for (int j = 1; j * j <= i; j++)
        {
            int square = j * j;
            // 核心公式
            if (dp[i - square] + 1 < dp[i])
            {
                dp[i] = dp[i - square] + 1;
            }
        }
    }
    return dp[n];
}

/*完全平方数的最少数量:
给你一个数 n，用最少几个 1、4、9、16…（自己乘自己的数）加起来等于 n，返回这个最少个数
思路：
1.建一个数组 dp []
dp[i] = 凑出数字 i 最少需要几个平方数

2.  先给最坏情况
全都用 1 凑，所以 dp[i] = i

3.从小到大一个个算最优解
对每个数字 i，试所有比它小的平方数（1、4、9…）
公式：dp [i] = dp [i - 平方数] + 1
哪个小就用哪个                                                                      */