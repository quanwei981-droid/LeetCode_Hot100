int findDuplicate(int* nums, int numsSize)
{
    // 1. 初始化快慢指针
    int slow = 0, fast = 0;
    // 2. 慢指针走1步，快指针走2步，直到相遇
    do
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    // 3. 快指针回到起点，和慢指针同速前进，相遇点即为重复数
    fast = 0;
    while (slow != fast)
    {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}

/*  问题转化为环形链表
    数组 nums 可以看作一个链表：下标 i 指向 nums[i]。
    因为数组里有重复数，所以链表中必然存在环，而重复的数就是环的入口节点。

    快慢指针判圈
    慢指针每次走 1 步：slow = nums[slow]
    快指针每次走 2 步：fast = nums[nums[fast]]
    两者一定会在环内相遇。

    找环的入口
    相遇后，将快指针移回起点，两个指针以相同速度前进。
    它们再次相遇的位置，就是环的入口，也就是重复的数字。         */