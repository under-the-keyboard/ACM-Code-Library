typedef double db; // typedef long double db;
const db inf = 1e100;
const db eps = 1e-9;
const db delta = 0.98;
int Sgn(db k) { return std::fabs(k) < eps ? 0 : (k < 0 ? -1 : 1); }
int Cmp(db k1, db k2) { return Sgn(k1 - k2); }
bool IsInMid(db k1, db k2, db k3) { return Sgn(k1 - k3) * Sgn(k2 - k3) <= 0; }
db Max(db k1, db k2) { return Cmp(k1, k2) > 0 ? k1 : k2; }
db Min(db k1, db k2) { return Cmp(k1, k2) < 0 ? k1 : k2; }
struct point { db x, y; };
bool operator == (point k1, point k2) { return !Cmp(k1.x, k2.x) && !Cmp(k1.y, k2.y); }
point operator + (point k1, point k2) { return (point){k1.x + k2.x, k1.y + k2.y}; }
point operator - (point k1, point k2) { return (point){k1.x - k2.x, k1.y - k2.y}; }
point operator * (point k1, db k2) { return (point){k1.x * k2, k1.y * k2}; }
point operator / (point k1, db k2) { return (point){k1.x / k2, k1.y / k2}; }
db operator * (point k1, point k2) { return k1.x * k2.x + k1.y * k2.y; }
db operator ^ (point k1, point k2) { return k1.x * k2.y - k1.y * k2.x; }
bool IsInMid(point k1, point k2, point k3) { return IsInMid(k1.x, k2.x, k3.x) && IsInMid(k1.y, k2.y, k3.y); }
db GetLen(point k) { return std::sqrt(k * k); }
db GetLen2(point k) { return k * k; }
point GetUnit(point k) { db w = GetLen(k); return (point){k.x / w, k.y / w}; }
db GetDis(point k1, point k2) { return GetLen(k2 - k1); }
db GetDis2(point k1, point k2) { return GetLen2(k2 - k1); }
db GetAng(point k1, point k2) { return std::atan2((k1 ^ k2), (k1 * k2)); }
point Rotate(point k, db ang) { return (point){k.x * std::cos(ang) - k.y * std::sin(ang), k.x * std::sin(ang) + k.y + std::cos(ang)}; }
point Rotate90(point k) { return (point){-k.y, k.x}; }
struct line { point s, t; };
struct seg: public line {}; // typedef line seg
db GetLen(seg k) { return GetDis(k.s, k.t); }
bool IsOn(point k1, seg k2) { return !Sgn((k1 - k2.s) ^ (k2.t - k2.s)) && Sgn((k1 - k2.s) * (k1 - k2.t)) <= 0; }
point Proj(point k1, line k2) { point k = k2.t - k2.s; return k2.s + k * (((k1 - k2.s) * k) / GetLen(k)); }
point Reflect(point k1, line k2) { return Proj(k1, k2) * 2 - k1; }
bool IsParallel(line k1, line k2) { return !Sgn((k1.s - k1.t) ^ (k2.s - k2.t)); }
bool IsInter(seg k1, seg k2) {
  return
    Max(k1.s.x, k1.t.x) >= Min(k2.s.x, k2.t.x) &&
    Max(k2.s.x, k2.t.x) >= Min(k1.s.x, k1.t.x) &&
    Max(k1.s.y, k1.t.y) >= Min(k2.s.y, k2.t.y) &&
    Max(k2.s.y, k2.t.y) >= Min(k1.s.y, k1.t.y) &&
    Sgn((k2.s - k1.t) ^ (k1.s - k1.t)) * Sgn((k2.t - k1.t) ^ (k1.s - k1.t)) <= 0 &&
    Sgn((k1.s - k2.t) ^ (k2.s - k2.t)) * Sgn((k1.t - k2.t) ^ (k2.s - k2.t)) <= 0;
}
bool IsInter(line k1, seg k2) {
  return Sgn((k2.s - k1.t) ^ (k1.s - k1.t)) * Sgn((k2.t - k1.t) ^ (k1.s - k1.t)) <= 0;
}
bool IsInter(line k1, line k2) {
  if (!IsParallel(k1, k2)) return true;
  return !Sgn((k1.s - k2.s) ^ (k2.t - k2.s));
}
db GetDis(point k1, line k2) {
  point k = Proj(k1, k2);
  return GetDis(k1, k);
}
db GetDis(point k1, seg k2) {
  point k = Proj(k1, k2);
  if (IsInMid(k2.s, k2.t, k)) return GetDis(k1, k);
  return Min(GetDis(k1, k2.s), GetDis(k1, k2.t));
}
point Cross(line k1, line k2) {
  db w1 = (k1.s - k2.s) ^ (k2.t - k2.s), w2 = (k2.t - k2.s) ^ (k1.t - k2.s);
  return (k1.s * w2 + k1.t * w1) / (w1 + w2);
}
struct circle { point o; db r; };
std::vector<point> TagentCP(circle k1, point k2) {
  db a = GetLen(k2 - k1.o), b = k1.r * k1.r / a, c = std::sqrt(Max(0., k1.r * k1.r - b * b));
  point k = GetUnit(k2 - k1.o), m = k1.o + k * b, del = Rotate90(k) * c;
  return {m - del, m + del};
}
// 返回公切线数量
int CheckPosCC(circle k1, circle k2) {
  if (Cmp(k1.r, k2.r) == -1) std::swap(k1, k2);
  double dis = k1.o.Dis(k2.o);
  int w1 = Cmp(dis, k1.r + k2.r), w2 = Cmp(dis, k1.r - k2.r);
  if (w1 > 0) return 4;
  if (w1 == 0) return 3;
  else if (w2 > 0) return 2;
  else if (w2 == 0) return 1;
  return 0;
}
// 返回两圆交点
std::vector<point> GetCC(circle k1, circle k2) {
  int pd = CheckPosCC(k1, k2);
  if (pd == 0 || pd == 4) return {};
  double a = (k2.o - k1.o).Abs2();
  double cosA = (k1.r * k1.r + a - k2.r * k2.r) / (2 * k1.r * sqrt(std::max(a, 0.0)));
  double b = k1.r * cosA, c = sqrt(std::max(0.0, k1.r * k1.r - b * b));
  point k = (k2.o - k1.o).Unit(), m = k1.o + k * b, del = k.Turn90() * c;
  return {m - del, m + del};
}
circle GetCircle(point k1, point k2, point k3) {
  db a1 = k2.x - k1.x, b1 = k2.y - k1.y, c1 = (a1 * a1 + b1 * b1) * 0.5;
  db a2 = k3.x - k1.x, b2 = k3.y - k1.y, c2 = (a2 * a2 + b2 * b2) * 0.5;
  db d = a1 * b2 - a2 * b1;
  point o = (point){k1.x + (c1 * b2 - c2 * b1) / d, k1.y + (a1 * c2 - a2 * c1) / d};
  return (circle){o, GetDis(k1, o)};
}
db GetMinCircleR(std::vector<point> p) {
  point cur = p[0];
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
circle GetMinCircle(std::vector<point> p) {
  std::random_shuffle(p.begin(), p.end());
  circle ret = (circle){p[0], 0.};
  for (int i = 1; i < p.size(); ++i) {
    if (Cmp(GetDis(ret.o, p[i]), ret.r) <= 0) continue;
    ret = (circle){p[i], 0.};
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
typedef std::vector<point> poly;
poly GrahamScan(std::vector<point> p) {
  poly ret;
  if (p.size() < 3) {
    for (point &v : p) ret.push_back(v);
    return ret;
  }
  int idx = 0;
  for (int i = 0; i < p.size(); ++i)
    if (Cmp(p[i].x, p[idx].x) < 0 || (!Cmp(p[i].x, p[idx].x) && Cmp(p[i].y, p[idx].y) < 0))
      idx = i;
  std::swap(p[0], p[idx]);
  std::sort(p.begin() + 1, p.end(),
    [&](const point &k1, const point &k2) {
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
bool IsIn(point p, const poly &ch) {
  point base = ch[0];
  if (Sgn((p - base) ^ (ch[1] - p)) > 0 || Sgn((p - base) ^ (ch.back() - base)) < 0) return false;
  if (!Sgn((p - base) ^ (ch[1] - p)) && Cmp(GetLen(p - base), GetLen(ch[1] - base)) <= 0) return true;
  int idx = std::lower_bound(ch.begin(), ch.end(), p,
    [&](const point &k1, const point &k2) {
      return Sgn((k1 - base) ^ (k2 - base)) > 0;
    }
  ) - ch.begin() - 1;
  return Sgn((ch[idx + 1] - ch[idx]) ^ (p - ch[idx])) >= 0;
}
poly Minkowski(const poly &k1, const poly &k2) {
  int sz1 = k1.size(), sz2 = k2.size();
  std::queue<point> buf1, buf2;
  for (int i = 0; i < sz1; ++i) buf1.push(k1[(i + 1) % sz1] - k1[i]);
  for (int i = 0; i < sz2; ++i) buf2.push(k2[(i + 1) % sz2] - k2[i]);
  poly ret;
  ret.push_back(k1[0] + k2[0]);
  while (!buf1.empty() && !buf2.empty()) {
    point tmp1 = buf1.front(), tmp2 = buf2.front();
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
db RotateCaliper(poly p) {
  db ret = -inf;
  if (p.size() == 3) {
    ret = Max(ret, GetDis(p[0], p[1]));
    ret = Max(ret, GetDis(p[0], p[2]));
    ret = Max(ret, GetDis(p[1], p[2]));
    return ret;
  }
  int cur = 2, sz = p.size();
  for (int i = 0; i < sz; ++i) {
    while (Cmp(fabs((p[i] - p[(i + 1) % sz]) ^ (p[cur] - p[(i + 1) % sz])), fabs((p[i] - p[(i + 1) % sz]) ^ (p[(cur + 1) % sz] - p[(i + 1) % sz]))) < 0) cur = (cur + 1) % sz;
    ret = Max(ret, GetDis(p[i], p[cur]));
  }
  return ret;
}
