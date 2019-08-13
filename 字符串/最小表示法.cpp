int minRepresent(char *s, int len) {
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        int t = s[(i+k) % len] - s[(j+k) % len];
        if (t == 0) k++;
        else {
            if (t < 0)  j = max(j+k+1, i+1);
            else i = max(i+k+1, j+1);
            k = 0;
        }
    }
    return min(i, j);
}
int minRepresent(int start, int end, int len) { // 判断[strat, end]是否为最小表示
    int i = 0+start, j = 1+start, k = 0;
    while (i < end && j < end && k < len) {
        int l = i + k;  if (l >= end) l = l - end + start;
        int r = j + k;  if (r >= end) r = r - end + start;
        int t = s[l] - s[r];
        if (t == 0) k++;
        else {
            if (t < 0)  j = max(j+k+1, i+1);
            else i = max(i+k+1, j+1);
            k = 0;
        }
    }
    return min(i, j) == start;
}