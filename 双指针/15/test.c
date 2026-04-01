/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

 // 快排辅助函数
int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;

    //  1.对数组排序
    qsort(nums, numsSize, sizeof(int), cmp);

    // 预分配最大可能的结果空间（最坏情况O(n?)，这里按n?/2估算，实际可动态扩容）
    int maxSize = numsSize * numsSize / 2;
    int** res = (int**)malloc(maxSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxSize * sizeof(int));

    //  2. 遍历固定第一个数（必须去重）
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] > 0) break; // 第一个数大于0，后续不可能和为0
        if (i > 0 && nums[i] == nums[i - 1]) continue; // 跳过重复的第一个数

        int left = i + 1;
        int right = numsSize - 1;

        // 3. 双指针遍历
        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0)
            {
                // 找到符合条件的三元组，分配内存并存储
                res[*returnSize] = (int*)malloc(3 * sizeof(int));
                res[*returnSize][0] = nums[i];
                res[*returnSize][1] = nums[left];
                res[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                // 跳过left指针的重复元素
                while (left < right && nums[left] == nums[left + 1]) left++;
                // 跳过right指针的重复元素
                while (left < right && nums[right] == nums[right - 1]) right--;

                // 移动指针，寻找下一组
                left++;
                right--;
            }
            else if (sum < 0)
            {
                left++; // 和太小，左指针右移
            }
            else
            {
                right--; // 和太大，右指针左移
            }
        }
    }

    return res;
}

/*解题思路  1.排序：先把数组从小到大排序（为了双指针 + 去重）
           2.双指针找另外两个数：
             左指针 left = i+1
             右指针 right = 末尾
           3.三元组中：
             第一个数去重
             左指针去重
             指针去重 */