int cntA[maxn], cntB[maxn], A[maxn], B[maxn];
int Sa[maxn], tsa[maxn], height[maxn], Rank[maxn];
char s[maxn];
int n;
void SuffixArray () {
	for (int i = 0; i < 1000; ++i) cntA[i] = 0;
	for (int i = 1; i <= n; ++i) cntA[(int)s[i]]++;
	for (int i = 1; i < 1000; ++i) cntA[i] += cntA[i-1];
	for (int i = n; i >= 1; --i) Sa[ cntA[(int)s[i]]-- ] = i;
	Rank[ Sa[1] ] = 1;
	for (int i = 2; i <= n; ++i) {
		Rank[Sa[i]] = Rank[Sa[i-1]];
		if (s[Sa[i]] != s[Sa[i-1]]) Rank[Sa[i]]++;
	}
	for (int l = 1; Rank[Sa[n]] < n; l <<= 1) {
		for (int i = 0; i <= n; ++i) cntA[i] = 0;
		for (int i = 0; i <= n; ++i) cntB[i] = 0;
		for (int i = 1; i <= n; ++i) {
			cntA[ A[i] = Rank[i] ]++;
			cntB[ B[i] = (i + l <= n) ? Rank[i+l] : 0]++;
		}
		for (int i = 1; i <= n; ++i) cntB[i] += cntB[i-1];
		for (int i = n; i >= 1; --i) tsa[ cntB[B[i]]-- ] = i;
		for (int i = 1; i <= n; ++i) cntA[i] += cntA[i-1];
		for (int i = n; i >= 1; --i) Sa[ cntA[A[tsa[i]]]-- ] = tsa[i];
		Rank[ Sa[1] ] = 1;
		for (int i = 2; i <= n; ++i) {
			Rank[Sa[i]] = Rank[Sa[i-1]];
			if (A[Sa[i]] != A[Sa[i-1]] || B[Sa[i]] != B[Sa[i-1]]) Rank[Sa[i]]++;
		}
	}
	for (int i = 1, j = 0; i <= n; ++i) {
		if (j) --j;
		int tmp = Sa[Rank[i] - 1];
		while (i + j <= n && tmp + j <= n && s[i+j] == s[tmp+j]) ++j;
		height[Rank[i]] = j;
	}
}
