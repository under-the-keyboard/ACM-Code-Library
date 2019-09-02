typedef double db; // typedef long double db;
const db inf = 1e100;
const db eps = 1e-9;
const db delta = 0.98;
int Sgn(db k) { return std::fabs(k) < eps ? 0 : (k < 0 ? -1 : 1); }
int Cmp(db k1, db k2) { return Sgn(k1 - k2); }
bool IsInMid(db k1, db k2, db k3) { return Sgn(k1 - k3) * Sgn(k2 - k3) <= 0; }
db Max(db k1, db k2) { return Cmp(k1, k2) > 0 ? k1 : k2; }
db Min(db k1, db k2) { return Cmp(k1, k2) < 0 ? k1 : k2; }
struct Point { db x, y; };
bool operator == (Point k1, Point k2) { return !Cmp(k1.x, k2.x) && !Cmp(k1.y, k2.y); }
Point operator + (Point k1, Point k2) { return (Point){k1.x + k2.x, k1.y + k2.y}; }
Point operator - (Point k1, Point k2) { return (Point){k1.x - k2.x, k1.y - k2.y}; }
Point operator * (Point k1, db k2) { return (Point){k1.x * k2, k1.y * k2}; }
Point operator / (Point k1, db k2) { return (Point){k1.x / k2, k1.y / k2}; }
db operator * (Point k1, Point k2) { return k1.x * k2.x + k1.y * k2.y; }
db operator ^ (Point k1, Point k2) { return k1.x * k2.y - k1.y * k2.x; }
bool IsInMid(Point k1, Point k2, Point k3) { return IsInMid(k1.x, k2.x, k3.x) && IsInMid(k1.y, k2.y, k3.y); }
db GetLen(Point k) { return std::sqrt(k * k); }
db GetLen2(Point k) { return k * k; }
Point GetUnit(Point k) { return k / GetLen(k); }
db GetDis(Point k1, Point k2) { return GetLen(k2 - k1); }
db GetDis2(Point k1, Point k2) { return GetLen2(k2 - k1); }
db GetAng(Point k1, Point k2) { return std::atan2((k1 ^ k2), (k1 * k2)); }
Point Rotate(Point k, db ang) { return (Point){k.x * std::cos(ang) - k.y * std::sin(ang), k.x * std::sin(ang) + k.y + std::cos(ang)}; }
Point Rotate90(Point k) { return (Point){-k.y, k.x}; }
struct Line { Point s, t; };
struct Seg: public Line {}; // typedef Line Seg
db GetLen(Seg k) { return GetDis(k.s, k.t); }
bool IsOn(Point k1, Seg k2) { return !Sgn((k1 - k2.s) ^ (k2.t - k2.s)) && Sgn((k1 - k2.s) * (k1 - k2.t)) <= 0; }
Point Proj(Point k1, Line k2) { Point k = k2.t - k2.s; return k2.s + k * (((k1 - k2.s) * k) / GetLen(k)); }
Point Reflect(Point k1, Line k2) { return Proj(k1, k2) * 2 - k1; }
bool IsParallel(Line k1, Line k2) { return !Sgn((k1.s - k1.t) ^ (k2.s - k2.t)); }
bool IsInter(Seg k1, Seg k2) {
  return
    Cmp(Max(k1.s.x, k1.t.x), Min(k2.s.x, k2.t.x)) >= 0 &&
    Cmp(Max(k2.s.x, k2.t.x), Min(k1.s.x, k1.t.x)) >= 0 &&
    Cmp(Max(k1.s.y, k1.t.y), Min(k2.s.y, k2.t.y)) >= 0 &&
    Cmp(Max(k2.s.y, k2.t.y), Min(k1.s.y, k1.t.y)) >= 0 &&
    Sgn((k2.s - k1.t) ^ (k1.s - k1.t)) * Sgn((k2.t - k1.t) ^ (k1.s - k1.t)) <= 0 &&
    Sgn((k1.s - k2.t) ^ (k2.s - k2.t)) * Sgn((k1.t - k2.t) ^ (k2.s - k2.t)) <= 0;
}
bool IsInter(Line k1, Seg k2) {
  return Sgn((k2.s - k1.t) ^ (k1.s - k1.t)) * Sgn((k2.t - k1.t) ^ (k1.s - k1.t)) <= 0;
}
bool IsInter(Line k1, Line k2) {
  if (!IsParallel(k1, k2)) return true;
  return !Sgn((k1.s - k2.s) ^ (k2.t - k2.s));
}
db GetDis(Point k1, Line k2) {
  return std::fabs((k1 - k2.s) ^ (k2.t - k2.s)) / GetLen(k2);
}
db GetDis(Point k1, Seg k2) {
  if (Sgn((k1 - k2.s) * (k2.t - k2.s)) < 0 || Sgn((k1 - k2.t) * (k2.s - k2.t)) < 0) return Min(GetDis(k1, k2.s), GetDis(k1, k2.t));
  return GetDis(k1, k2);
}
db GetDis(Seg k1, Seg k2) {
  if (IsInter(k1, k2)) return 0.;
  else return Min(Min(GetDis(k1.s, k2), GetDis(k1.t, k2)), Min(GetDis(k1, k2.s), GetDis(k1, k2.t)));
}
Point Cross(Line k1, Line k2) {
  db w1 = (k1.s - k2.s) ^ (k2.t - k2.s), w2 = (k2.t - k2.s) ^ (k1.t - k2.s);
  return (k1.s * w2 + k1.t * w1) / (w1 + w2);
}
// 平面直线图(PSLG)
struct Edge { int u, v; db ang; };
struct PSLG {
  int n, m, face_cnt; // 多边形数
  Point p[maxn];
  std::vector<Edge> e;
  std::vector<int> g[maxn];
  bool vis[maxn * 2];
  int left[maxn * 2], prev[maxn * 2];
  std::vector<Polygon> faces; // 多边形
  db area[maxn]; // 多边形面积
  void Init() {
    n = m = 0;
    for (int i = 0; i < n; ++i) g[i].clear();
    e.clear();
    faces.clear();
  }
  // 有向线段pt.x->pt.y的极角
  db GetAng(Point pt) {
    return std::atan2(pt.y, pt.x);
  }
  void AddEdge(int u, int v) {
    e.push_back((Edge){u, v, GetAng(p[v] - p[u])});
    e.push_back((Edge){v, u, GetAng(p[u] - p[v])});
    m = e.size();
    g[u].push_back(m - 2);
    g[v].push_back(m - 1);
  }
  // 找出faces并计算面积
  void Build() {
    for (int u = 0; u < n; ++u) {
      int sz = g[u].size();
      for (int i = 0; i < sz; ++i)
        for (int j = i + 1; j < sz; ++j)
          if (e[g[u][i]].ang > e[g[u][j]].ang) std::swap(g[u][i], g[u][j]);
      for (int i = 0; i < sz; ++i) prev[g[u][(i + 1) % sz]] = g[u][i];
    }
    face_cnt = 0;
    memset(vis, false, sizeof(vis));
    for (int u = 0; u < n; ++u) {
      int sz = g[u].size();
      for (int i = 0; i < sz; ++i) {
        int v = g[u][i];
        // 卷包裹逆时针找圈
        if (!vis[v]) {
          ++face_cnt;
          Polygon poly;
          while (true) {
            vis[v] = 1;
            left[v] = face_cnt;
            int f = e[v].u;
            poly.push_back(p[f]);
            v = prev[v ^ 1];
            if (v == g[u][i]) break;
            assert(vis[v] == 0);
          }
          faces.push_back(poly);
        }
      }
    }
    for (int i = 0; i < face_cnt; ++i) area[i] = GetArea(faces[i]);
  }
};
struct Circle { Point o; db r; };
// 切点
std::vector<Point> TagentCP(Circle k1, Point k2) {
  db a = GetLen(k2 - k1.o), b = k1.r * k1.r / a, c = std::sqrt(Max(0., k1.r * k1.r - b * b));
  Point k = GetUnit(k2 - k1.o), m = k1.o + k * b, del = Rotate90(k) * c;
  return {m - del, m + del};
}
// 公切线数量
int CheckPosCC(Circle k1, Circle k2) {
  if (Cmp(k1.r, k2.r) == -1) std::swap(k1, k2);
  double dis = k1.o.Dis(k2.o);
  int w1 = Cmp(dis, k1.r + k2.r), w2 = Cmp(dis, k1.r - k2.r);
  if (w1 > 0) return 4;
  if (w1 == 0) return 3;
  else if (w2 > 0) return 2;
  else if (w2 == 0) return 1;
  return 0;
}
// 交点
std::vector<Point> GetCC(Circle k1, Circle k2) {
  int pd = CheckPosCC(k1, k2);
  if (pd == 0 || pd == 4) return {};
  double a = (k2.o - k1.o).Abs2();
  double cosA = (k1.r * k1.r + a - k2.r * k2.r) / (2 * k1.r * sqrt(std::max(a, 0.0)));
  double b = k1.r * cosA, c = sqrt(std::max(0.0, k1.r * k1.r - b * b));
  Point k = (k2.o - k1.o).Unit(), m = k1.o + k * b, del = k.Turn90() * c;
  return {m - del, m + del};
}
Circle GetCircle(Point k1, Point k2, Point k3) {
  db a1 = k2.x - k1.x, b1 = k2.y - k1.y, c1 = (a1 * a1 + b1 * b1) * 0.5;
  db a2 = k3.x - k1.x, b2 = k3.y - k1.y, c2 = (a2 * a2 + b2 * b2) * 0.5;
  db d = a1 * b2 - a2 * b1;
  Point o = (Point){k1.x + (c1 * b2 - c2 * b1) / d, k1.y + (a1 * c2 - a2 * c1) / d};
  return (Circle){o, GetDis(k1, o)};
}
db GetMinCircleR(std::vector<Point> p) {
  Point cur = p[0];
  db pro = 10000, ret = inf;
  while (Sgn(pro) > 0) {
    int idx = 0;
    for (int i = 0; i < p.size(); ++i)
      if (GetDis(cur, p[i]) > GetDis(cur, p[idx]))
        idx = i;
    db r = GetDis(cur, p[idx]);
    ret = Min(ret, r);
    cur = cur + (p[idx] - cur) / r * pro;
    pro *= delta;
  }
  return ret;
}
Circle GetMinCircle(std::vector<Point> p) {
  std::random_shuffle(p.begin(), p.end());
  Circle ret = (Circle){p[0], 0.};
  for (int i = 1; i < p.size(); ++i) {
    if (Cmp(GetDis(ret.o, p[i]), ret.r) <= 0) continue;
    ret = (Circle){p[i], 0.};
    for (int j = 0; j < i; ++j) {
      if (Cmp(GetDis(ret.o, p[j]), ret.r) <= 0) continue;
      ret.o = (p[i] + p[j]) * 0.5;
      ret.r = GetDis(ret.o, p[i]);
      for (int k = 0; k < j; ++j) {
        if (Cmp(GetDis(ret.o, p[k]), ret.r) <= 0) continue;
        ret = GetCircle(p[i], p[j], p[k]);
      }
    }
  }
  return ret;
}
typedef std::vector<Point> Polygon;
db GetArea(Polygon &poly) {
  db ret = 0.;
  for (int i = 0; i < poly.size(); ++i) ret += poly[i] ^ poly[(i + 1) % poly.size()];
  return ret * 0.5;
}
Polygon GrahamScan(std::vector<Point> p) {
  Polygon ret;
  if (p.size() < 3) {
    for (Point &v : p) ret.push_back(v);
    return ret;
  }
  int idx = 0;
  for (int i = 0; i < p.size(); ++i)
    if (Cmp(p[i].x, p[idx].x) < 0 || (!Cmp(p[i].x, p[idx].x) && Cmp(p[i].y, p[idx].y) < 0))
      idx = i;
  std::swap(p[0], p[idx]);
  std::sort(p.begin() + 1, p.end(),
    [&](const Point &k1, const Point &k2) {
      db tmp = (k1 - p[0]) ^ (k2 - p[0]);
      if (Sgn(tmp) > 0) return true;
      else if (!Sgn(tmp) && Cmp(GetDis(k1, p[0]), GetDis(k2, p[0])) <= 0) return true;
      return false;
    }
  );
  ret.push_back(p[0]);
  for (int i = 1; i < p.size(); ++i) {
    while (ret.size() > 1 && Sgn((ret.back() - ret[ret.size() - 2]) ^ (p[i] - ret[ret.size() - 2])) <= 0) ret.pop_back();
    ret.push_back(p[i]);
  }
  return ret;
}
bool IsIn(Point p, const Polygon &ch) {
  Point base = ch[0];
  if (Sgn((p - base) ^ (ch[1] - p)) > 0 || Sgn((p - base) ^ (ch.back() - base)) < 0) return false;
  if (!Sgn((p - base) ^ (ch[1] - p)) && Cmp(GetLen(p - base), GetLen(ch[1] - base)) <= 0) return true;
  int idx = std::lower_bound(ch.begin(), ch.end(), p,
    [&](const Point &k1, const Point &k2) {
      return Sgn((k1 - base) ^ (k2 - base)) > 0;
    }
  ) - ch.begin() - 1;
  return Sgn((ch[idx + 1] - ch[idx]) ^ (p - ch[idx])) >= 0;
}
Polygon Minkowski(const Polygon &k1, const Polygon &k2) {
  int sz1 = k1.size(), sz2 = k2.size();
  std::queue<Point> buf1, buf2;
  for (int i = 0; i < sz1; ++i) buf1.push(k1[(i + 1) % sz1] - k1[i]);
  for (int i = 0; i < sz2; ++i) buf2.push(k2[(i + 1) % sz2] - k2[i]);
  Polygon ret;
  ret.push_back(k1[0] + k2[0]);
  while (!buf1.empty() && !buf2.empty()) {
    Point tmp1 = buf1.front(), tmp2 = buf2.front();
    if (Sgn(tmp1 ^ tmp2) > 0) {
      ret.push_back(ret.back() + tmp1);
      buf1.pop();
    }
    else {
      ret.push_back(ret.back() + tmp2);
      buf2.pop();
    }
  }
  while (!buf1.empty()) {
    ret.push_back(ret.back() + buf1.front());
    buf1.pop();
  }
  while (!buf2.empty()) {
    ret.push_back(ret.back() + buf2.front());
    buf2.pop();
  }
  return GrahamScan(ret);
}
db RotateCaliper(Polygon p) {
  db ret = -inf;
  if (p.size() == 3) {
    ret = Max(ret, GetDis(p[0], p[1]));
    ret = Max(ret, GetDis(p[0], p[2]));
    ret = Max(ret, GetDis(p[1], p[2]));
    return ret;
  }
  int cur = 2, sz = p.size();
  for (int i = 0; i < sz; ++i) {
    while (Cmp(std::fabs((p[i] - p[(i + 1) % sz]) ^ (p[cur] - p[(i + 1) % sz])), std::fabs((p[i] - p[(i + 1) % sz]) ^ (p[(cur + 1) % sz] - p[(i + 1) % sz]))) < 0) cur = (cur + 1) % sz;
    ret = Max(ret, GetDis(p[i], p[cur]));
  }
  return ret;
}
