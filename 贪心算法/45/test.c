int jump(int* nums, int numsSize)
{
    int jumps = 0;          // 记录跳跃次数
    int currentEnd = 0;     // 当前跳跃能到达的最远位置
    int farthest = 0;       // 遍历过程中能到达的最远位置

    for (int i = 0; i < numsSize - 1; i++)
    {
        // 更新能到达的最远位置
        farthest = (i + nums[i] > farthest) ? (i + nums[i]) : farthest;

        // 当到达当前跳跃的边界时，jumps已完成一次跳跃
        if (i == currentEnd)
        {
            jumps++;
            currentEnd = farthest; // 更新下一次跳跃的边界

            // 优化：如果已经能到达终点，直接跳出循环
            if (currentEnd >= numsSize - 1)
            {
                break;
            }
        }
    }

    return jumps;
}

/*遍历数组时，持续更新farthest（当前区间内的最远可达位置）。
当遍历到currentEnd时，说明当前跳的覆盖范围已经走完，必须跳一次（jumps++），
并将currentEnd更新为farthest（下一跳的覆盖范围）*/