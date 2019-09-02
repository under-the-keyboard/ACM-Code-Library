struct KMP{ // 下标0
    int nex[maxn];
    void get_nex(char *buf, int len) {
        nex[0] = -1;
        int i = 0, j = -1;
        while (i < len) {
            if (j == -1 || buf[i] == buf[j]) nex[++i] = ++j;
            else j = nex[j];
        }
    }
    int get_kmp(char *buf1, char *buf2) { // buf1匹配串，buf2模式串
        int len1 = strlen(buf1), len2 = strlen(buf2);
        get_nex(buf2, len2);
        int cnt = 0, i = 0, j = 0;
        while (i < len1) {
            if (j == -1 || buf1[i] == buf2[i]) ++i, ++j;
            else j = nex[j];
            if (j == len2) cnt++, j = nex[j];
        }
        return cnt; // 匹配个数
    }
    // (len - nex[len]) 最小循环节，前提len % (len - nex[len]) = 0
}kmp;