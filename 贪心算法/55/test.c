bool canJump(int* nums, int numsSize)
{
    // 我目前能到达的最远索引
    int maxReach = 0;
    for (int i = 0; i < numsSize; i++)
    {
        // 如果当前下标i超过了最远可到达位置，说明无法到达i，直接返回false
        if (i > maxReach)
        {
            return false;
        }
        // 更新最远可到达的位置
        if (i + nums[i] > maxReach)
        {
            maxReach = i + nums[i];
        }
        // 如果最远可到达位置已经超过或等于最后一个下标，直接返回true
        if (maxReach >= numsSize - 1)
        {
            return true;
        }
    }
    return maxReach >= numsSize - 1;  //  当循环正常跑完，未在循环内结束，最终判断
}

/*每一步都选[能跳到最远的]位置，不断扩大可达范围，只要能覆盖终点就成功，走不到就失败*/


bool canJump(int* nums, int numsSize)
{
    int n = numsSize;
    if (n == 1)
        return true;
    // 目标位置，一开始是终点
    int tou = n - 1;
    // 从后往前遍历
    for (int i = n - 2; i >= 0; i--)
    {
        // 如果 i 能跳到当前目标 tou
        if (nums[i] >= tou - i)
        {
            tou = i;  // 更新目标为 i
        }
    }
    // 最后目标回到起点 0 就成功
    return tou == 0;
}

/*反向贪心：从终点倒着找能跳到它的位置，不断前移目标，最后看能不能回到起点
（看每次遍历到达tou的步数,在上一个下标里的最大步数满不满足）*/