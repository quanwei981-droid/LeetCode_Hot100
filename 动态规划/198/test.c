int rob(int* nums, int numsSize)
{
    int prev2 = nums[0];                // 第 0 间房的最大值
    int prev1 = (nums[0] > nums[1]) ? nums[0] : nums[1]; // 第 1 间房的最大值

    // 从第 2 间房开始往后算
    for (int i = 2; i < numsSize; i++)
    {
        // 当前房间 i 的最大值：二选一
        int current = (prev1 > prev2 + nums[i]) ? prev1 : (prev2 + nums[i]);

        prev2 = prev1;     // 原来的前1个 → 变成新的 前前个
        prev1 = current;   // 刚算出来的 → 变成新的 前1个
    }
    return prev1;
}

/*
    不能偷相邻房子，每间房只有偷 / 不偷两种选择，取收益更大的那个
    两种选择
    不偷第 i 间
    最大值 = 前一间的最大值
    偷第 i 间
    最大值 = 前前一间的最大值 + 这间房的钱
    每算完一间，把变量往前滚动  */