struct Manacher{ // 下标0
    int RL[maxn << 1];
    char s[maxn], t[maxn << 1];
    int getlen(char *s) {
        if (s[strlen(s) - 1] == '\n')   s[strlen(s) - 1] = '\0';
        int lens = strlen(s), len = 0;
        t[len++] = '#';
        for (int i = 0; i < lens; ++i) {
            t[len++] = s[i];
            t[len++] = '#';
        }
        int MaxRight = 0, pos = 0, MaxLen = 0;
        for (int i = 0; i < len; ++i) {
            if (i < MaxRight)   RL[i] = min(RL[2 * pos - i], MaxRight - i + 1); // 好多这里写的是 MaxRight - i，个人感觉根据算法思想应该+1计算长度。
            else    RL[i] = 1;
            int l = i - RL[i];
            int r = i + RL[i];
            while (l >= 0 && r < len && t[l] == t[r])   {
                RL[i] += 1;
                l = i - RL[i];
                r = i + RL[i];
            }
            if (RL[i] + i - 1 > MaxRight) {
                MaxRight = RL[i] + i - 1;
                pos = i;
            }
            MaxLen = max(MaxLen, RL[i]);
        }
        return MaxLen - 1; 
    }
}manacher;
