/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize)
{
    *returnSize = numsSize;
    int* answer = (int*)malloc(numsSize * sizeof(int));

    // 第一步：计算前缀积，存入answer数组
    answer[0] = 1;
    for (int i = 1; i < numsSize; i++)
    {
        answer[i] = answer[i - 1] * nums[i - 1];
    }

    // 第二步：从后往前，用一个变量维护后缀积，同时更新answer数组
    int suffix = 1;
    for (int i = numsSize - 1; i >= 0; i--)
    {
        answer[i] = answer[i] * suffix;
        suffix *= nums[i];
    }

    return answer;
}

/*  对于每个位置 i，结果 answer[i] 等于：
    answer[i] = 前缀积（前 i-1 个元素的乘积） × 后缀积（后 i+1 个元素的乘积）
    前缀积数组 prefix：prefix[i] 表示 nums[0] 到 nums[i-1] 的乘积
    后缀积数组 suffix：suffix[i] 表示 nums[i+1] 到 nums[n-1] 的乘积
    第一步就在计算，除要填充的数，和它后面的组成积的那个数，的积
    第二步加上组成积的那个数在计算出最终积，同时更新suffix应对下一组
    为了优化空间，我们可以直接在结果数组上计算前缀积，再用一个变量动态维护后缀积，实现 O (1) 额外空间复杂度 */