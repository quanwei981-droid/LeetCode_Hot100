/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* partitionLabels(char* s, int* returnSize)
{
    int last[26] = { 0 }; // 存储每个字母最后出现的索引
    int len = strlen(s);

    //  1.遍历字符串，统计每个字母最后一次出现的位置
    for (int i = 0; i < len; i++)
    {
        last[s[i] - 'a'] = i;
    }

    // 最多能分成len段（每个字符一段），所以分配len大小足够
    int* res = (int*)malloc(len * sizeof(int));
    *returnSize = 0; // 结果数组的实际长度

    int left = 0;  // 当前段的左边界
    int right = 0; // 当前段的右边界

    // 2.再次遍历，动态扩展右边界，划分区间
    for (int i = 0; i < len; i++)
    {
        // 更新当前段的右边界，为当前字母最后出现位置和原right的较大值
        right = right > last[s[i] - 'a'] ? right : last[s[i] - 'a'];

        // 当遍历到右边界时，说明当前段可以划分了
        if (i == right)
        {
            res[*returnSize] = right - left + 1;
            (*returnSize)++;
            left = i + 1; // 把下一段的左边界，设置为当前段右边界的下一个索引
        }
    }

    return res;
}

/*贪心策略：每次找到当前区间内所有字母的最远出现位置，当遍历到这个最远位置时，就可以切一刀了
注意：用当前字符减去'a'，就能把字符映射成 0~25 的数组下标*/