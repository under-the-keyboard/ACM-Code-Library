vector<int> g[maxn];
struct Topsort{ // 下标1
	priority_queue<int, vector<int>, greater<int>> q1; // 字典序小，正向建图
	priority_queue<int, vector<int>> q2; // 编号小的优先级高，反向建图
	int in[maxn], order[maxn], n, cnt;
	void init () {
		fill(in, in+n+1, 0);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < (int)g[i].size(); ++j) {
				in[g[i][j]]++;
			}
		}
	}
	int min_lex (int len) {
		n = len;
		cnt = 0;
		init();
		for (int i = 1; i <= n; ++i) 
			if (in[i] == 0) q1.push(i);
		while (!q1.empty()) {
			int u = q1.top();
			q1.pop();
			order[++cnt] = u;
			for (int j = 0; j < (int)g[u].size(); ++j) {
				int v = g[u][j];
				in[v]--;
				if (in[v] == 0) q1.push(v);
			}
		}
		return cnt == n;
	}	
	int min_num (int len) {
		cnt = n = len;
		init();
		for (int i = 1; i <= n; ++i) 
			if (in[i] == 0) q2.push(i);
		while (!q2.empty()) {
			int u = q2.top();
			q2.pop();
			order[cnt--] = u;
			for (int j = 0; j < (int)g[u].size(); ++j) {
				int v = g[u][j];
				if (--in[v] == 0) q2.push(v);
			}
		}
		return cnt == 0;
	}
}topsort;
