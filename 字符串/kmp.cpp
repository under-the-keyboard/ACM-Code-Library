int a[N], b[N], Next[N];	//从a数组里匹配b数组
void get_next(int m) {	//求Next数组 
	Next[0] = -1;	 
	int i = 0, j = -1;
	while (i < m) {
		if(j == -1 || b[i] == b[j]) {
			Next[++i] = ++j;	//赋值 
		}else {
			j = Next[j];	//回溯 
		}
	}
}
int kmp(int n, int m) {
	get_next(m);	//求Next数组 
	int i = 0, j = 0;
	int ans = 0;
	while (i < n) {
		if (j == -1 || a[i] == b[j]) {	//当前匹配成功进行下一个匹配 
			i++;
			j++;	
		}else {
			j = Next[j];
		}
		if (j == m) {	//匹配成功 
			ans++;
			j = Next[j];	//进行下一次匹配 
		}
	}
	return ans;
}
