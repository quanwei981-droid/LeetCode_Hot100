int majorityElement(int* nums, int numsSize)
{
    int candidate = nums[0];
    int count = 1;

    for (int i = 1; i < numsSize; i++)
    {
        if (count == 0)
        {
            candidate = nums[i];
        }
        if (nums[i] == candidate)
        {
            count++;
        }
        else {
            count--;
        }
    }

    return candidate;
}

/*多数元素出现次数超过一半，因此与其他元素两两抵消后（遇相同计数器自增不同则减），最终必然剩下多数元素*/