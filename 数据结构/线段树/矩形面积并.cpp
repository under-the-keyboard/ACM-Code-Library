// HDU 1542 矩形面积并
#include <bits/stdc++.h>
typedef double db;
const int maxn = 1e2 + 5;
const db eps = 1e-9;
int Sgn(db k) {
  return std::fabs(k) < eps ? 0 : (k < 0 ? -1 : 1);
}
int Cmp(db k1, db k2) {
  return Sgn(k1 - k2);
}
struct Seg {
  db l, r, h;
  int flag;
};
bool operator < (Seg &k1, Seg &k2) {
  return Cmp(k1.h, k2.h) < 0;
}
std::vector<Seg> Segs;
std::vector<db> pos;
int BinarySearch(db k) {
  int ret = (int)pos.size() - 1, l = 0, r = (int)pos.size() - 1;
  while (l <= r) {
    int m = (l + r) >> 1;
    if (Cmp(pos[m], k) >= 0) {
      ret = m;
      r = m - 1;
    }
    else l = m + 1;
  }
  return ret;
}
struct Node {
  int l, r, cnt;
  db len;
};
Node Seg_tree[maxn * 10];
void Pull(int o) {
  if (Seg_tree[o].cnt) Seg_tree[o].len = pos[Seg_tree[o].r + 1] - pos[Seg_tree[o].l];
  else if (Seg_tree[o].l == Seg_tree[o].r) Seg_tree[o].len = 0.0;
  else Seg_tree[o].len = Seg_tree[o << 1].len + Seg_tree[o << 1 | 1].len;
}
void Build(int l, int r, int o) {
  Seg_tree[o].l = l; Seg_tree[o].r = r;
  Seg_tree[o].cnt = 0; Seg_tree[o].len = 0.0;
  if (l == r) return;
  int Mid = (l + r) >> 1;
  Build(l, Mid, o << 1);
  Build(Mid + 1, r, o << 1 | 1);
  Pull(o);
}
void Update(int l, int r, int v, int o) {
  if (l <= Seg_tree[o].l && r >= Seg_tree[o].r) {
    Seg_tree[o].cnt += v;
    Pull(o);
    return;
  }
  int Mid = (Seg_tree[o].l + Seg_tree[o].r) >> 1;
  if (r <= Mid) Update(l, r, v, o << 1);
  else if (l > Mid) Update(l, r, v, o << 1 | 1);
  else {
    Update(l, Mid, v, o << 1);
    Update(Mid + 1, r, v, o << 1 | 1);
  }
  Pull(o);
}
int cas;
int n;
db x1, y1, x2, y2;
db ans;
int main() {
  while (~scanf("%d", &n) && n) {
    Segs.clear();
    pos.clear();
    for (int i = 0; i < n; ++i) {
      scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
      Segs.push_back((Seg){x1, x2, y1, 1});
      Segs.push_back((Seg){x1, x2, y2, -1});
      pos.push_back(x1);
      pos.push_back(x2);
    }
    std::sort(Segs.begin(), Segs.end());
    std::sort(pos.begin(), pos.end(), [&](db k1, db k2) { return Cmp(k1, k2) < 0; });
    int cur = 1;
    for (int i = 1; i < (int)pos.size(); ++i)
      if (Cmp(pos[i], pos[i - 1]) != 0)
        pos[cur++] = pos[i];
    pos.erase(pos.begin() + cur, pos.end());
    Build(0, (int)pos.size(), 1);
    ans = 0.0;
    for (int i = 0; i < (int)Segs.size() - 1; ++i) {
      int l = BinarySearch(Segs[i].l), r = BinarySearch(Segs[i].r);
      Update(l, r - 1, Segs[i].flag, 1);
      ans += (Segs[i + 1].h - Segs[i].h) * Seg_tree[1].len;
    }
    printf("Test case #%d\n", ++cas);
    printf("Total explored area: %.2lf\n\n", ans);
  }
  return 0;
}