/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** res;
int* path;
int* cols;
int idx, len;

void dfs(int* nums, int n, int start)
{
    // 保存当前子集
    res[idx] = malloc(len * sizeof(int)); // 第一步空指针存空集
    for (int i = 0; i < len; i++) res[idx][i] = path[i];
    cols[idx++] = len;

    // 选数字
    for (int i = start; i < n; i++)
    {
        path[len++] = nums[i];
        dfs(nums, n, i + 1);
        len--;
    }
}

int** subsets(int* nums, int n, int* returnSize, int** returnColumnSizes)
{
    int total = 1 << n;
    *returnSize = total;

    // 开空间
    res = malloc(total * sizeof(int*)); // 结果
    path = malloc(n * sizeof(int));
    cols = malloc(total * sizeof(int)); // 返回行大小 

    idx = len = 0;
    dfs(nums, n, 0);

    *returnColumnSizes = cols;
    return res;
}

/*  << 叫左移运算符
    规则：
    数字 1 左移 n 位 = 2ⁿ

    一进入递归，先把当前手里的子集存进答案
    （空集就是这么存的！先存再选数字）
    从当前位置开始，挨个尝试选每一个数字
    选完数字，递归往后走，继续选后面的数字
    递归回来，撤销刚才的选择（回溯），尝试「不选这个数字」的分支
    递归传参start+1 控制只选后面   */