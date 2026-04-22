/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize)
{
    // 初始化返回数组，最多s.length个结果
    int lenS = strlen(s);
    int lenP = strlen(p);
    int* res = (int*)malloc(sizeof(int) * lenS);
    *returnSize = 0; // 结果个数初始0

    // p比s长，直接返回空
    if (lenP > lenS) return res;

    // 计数数组：26个小写字母
    int cntP[26] = { 0 };
    int cntWin[26] = { 0 };

    // 第一步：统计p的字母计数 + 初始化窗口前lenP个字母
    for (int i = 0; i < lenP; i++)
    {
        cntP[p[i] - 'a']++;
        cntWin[s[i] - 'a']++;
    }

    // 判断第一个窗口是不是异位词
    int same = 1;
    for (int i = 0; i < 26; i++)
    {
        if (cntWin[i] != cntP[i])
        {
            same = 0; break;
        }
    }
    if (same) res[(*returnSize)++] = 0;

    // 第二步：滑动窗口，一格一格往后走
    for (int i = lenP; i < lenS; i++)
    {
        // 移出左边旧字符：窗口最左是 i-lenP
        char left = s[i - lenP];
        cntWin[left - 'a']--;
        // 加入右边新字符
        char right = s[i];
        cntWin[right - 'a']++;

        // 判断当前窗口是不是异位词
        same = 1;
        for (int j = 0; j < 26; j++)
        {
            if (cntWin[j] != cntP[j])
            {
                same = 0; break;
            }
        }
        if (same)
        {
            // 当前窗口起始下标 = i-lenP+1
            res[(*returnSize)++] = i - lenP + 1;
        }
    }

    return res;
}

/*  为什么单独判断第一个窗口？
    因为滑动窗口逻辑是「左出右进」，第一个窗口是直接装满的，不能滑动，所以必须单独判断

    把 p 当成标准模板
    s 里有很多长度一样的滑动框
    每个框不用重新数全部字母
    只改滑出去和滑进来的两个字母
    和模板一样就是答案              */