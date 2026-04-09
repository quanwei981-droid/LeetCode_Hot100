#define MAX_STACK_SIZE 1000
#define INIT_SIZE 100001  // 初始分配大小

char* decodeString(char* s)
{
    int num_stack[MAX_STACK_SIZE];
    char* str_stack[MAX_STACK_SIZE];
    int num_top = -1, str_top = -1;

    // 用变量记录当前分配的总大小，初始1e5+1
    int alloc_size = INIT_SIZE;
    char* current_str = (char*)malloc(alloc_size * sizeof(char));
    current_str[0] = '\0';
    int current_num = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        if (c >= '0' && c <= '9')
        {
            current_num = current_num * 10 + (c - '0');
        }
        else if (c == '[')
        {
            // 入栈：保存当前状态
            num_stack[++num_top] = current_num;
            str_stack[++str_top] = current_str;

            // 重置：给新字符串分配空间
            current_num = 0;
            alloc_size = INIT_SIZE;
            current_str = (char*)malloc(alloc_size * sizeof(char));
            current_str[0] = '\0';
        }
        else if (c == ']')
        {
            // 出栈：拼接字符串
            int k = num_stack[num_top--];
            char* prev_str = str_stack[str_top--];

            int prev_len = strlen(prev_str);
            int curr_len = strlen(current_str);
            int new_len = prev_len + k * curr_len;

            // 动态分配足够大的空间，避免溢出
            char* new_str = (char*)malloc((new_len + 1) * sizeof(char));
            strcpy(new_str, prev_str);
            for (int j = 0; j < k; j++)
            {
                strcat(new_str, current_str);
            }

            // 释放旧内存，更新current_str和分配大小
            free(current_str);
            free(prev_str);
            current_str = new_str;
            alloc_size = new_len + 1;
        }
        else
        {
            // 普通字符：拼接前先检查空间，不够就扩容
            int len = strlen(current_str);
            // 剩余空间 = 总分配大小 - 已用长度（含\0）
            if (len + 2 > alloc_size)
            {
                // 空间不足，扩容2倍
                alloc_size *= 2;
                current_str = realloc(current_str, alloc_size * sizeof(char));
            }
            // 现在空间足够，安全拼接
            current_str[len] = c;
            current_str[len + 1] = '\0';
        }
    }

    return current_str;
}

/*用「栈」来分层保存「括号前的状态」，逐层解码，最终得到完整字符串
1.遇到数字记次数，遇到 "[" 就把当前字符串和数字存进栈，再清空变量去处理括号里的内容。
2.遇到 "]" 就从栈取出之前的字符串和次数，把括号里的内容重复后拼回去，普通字符直接追加*/
