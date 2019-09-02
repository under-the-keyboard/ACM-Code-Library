typedef double db;
const db inf = 1e100;
const db eps = 1e-9;
const db pi = acos(-1.);
const db delta = 0.98;
int Sgn(db k) { return std::fabs(k) < eps ? 0 : (k < 0 ? -1 : 1); }
int Cmp(db k1, db k2) { return Sgn(k1 - k2); }
db Min(db k1, db k2) { return Cmp(k1, k2) < 0 ? k1 : k2; }
db Max(db k1, db k2) { return Cmp(k1, k2) > 0 ? k1 : k2; }
struct Point { db x, y, z; }
bool operator == (Point k1, Point k2) { return !Sgn(k1.x - k2.x) && !Sgn(k1.y, k2.y) && !Sgn(k1.z, k2.z); }
Point operator + (Point k1, Point k2) { return (Point){k1.x + k2.x, k1.y + k2.y, k1.z + k2.z}; }
Point operator - (Point k1, Point k2) { return (Point){k1.x - k2.x, k1.y - k2.y, k1.z - k2.z}; 
Point operator * (Point k1, db k2) { return (Point){k1.x * k2, k1.y * k2, k1.z * k2};  }
Point operator / (Point k1, db k2) { return (Point){k1.x / k2, k1.y / k2, k1.z / k2};  }
db operator * (Point k1, Point k2) { k1.x * k2.x + k1.y * k2.y + k1.z * k2.z; }
Point operator ^ (Point k1, Point k2) { return (Point){k1.y * k2.z - k1.z * k2.y, k1.z * k2.x - k1.x * k2.z, k1.x * k2.y - k1.y * k2.x}; }
db GetLen(Point k) { return std::sqrt(k * k); }
db GetLen2(Point k) { return k * k; }
Point GetUnit(Point k) { return k / GetLen(k); }
db GetDis(Point k1, Point k2) { return GetLen(k2 - k1); }
db GetDis2(Point k1, Point k2) { return GetLen2(k2 - k1); }
db GetMinSphereR(std::vector<Point> p) {
  Point cur = p[0];
  db pro = 10000, ret = inf;
  while (pro > eps) {
    int idx = 0;
    for (int i = 0; i < p.size(); ++i)
      if (Cmp(GetDis(cur, p[i]), GetDis(cur, p[idx])) > 0)
        idx = i;
    db r = GetDis(cur, p[idx]);
    ret = Min(ret, r);
    cur = cur + (p[idx] - cur) / r * pro;
    pro *= delta;
  }
  return ret;
}
struct Line { Point s, t; };
struct Seg: public Line {};
db GetLen(Seg k) { return GetDis(k.s, k.t); }
db GetLen2(Seg k) { return GetDis2(k.s, k.t); }
db GetDis(Point k1, Line k2) { return std::fabs((k1 - k2.s) ^ (k2.t - k2.s)) / GetLen(k2); }
db GetDis(Point k1, Seg k2) {
  if (Sgn((k1 - k2.s) * (k2.t - k2.s)) < 0 || Sgn((k1 - k2.t) * (k2.s - k2.t)) < 0)
    return Min(GetDis(k1, k2.s), GetDis(k1, k2.t));
  return GetDis(k1, Seg); // Point to Line dis
}
struct Sphere { Point o; db r; };
db GetV(Sphere k) { return 4. / 3. * pi * k.r * k.r * k.r; }
db GetInterV(Sphere k1, Sphere k2) {
  db dis = GetDisP2P(k1.o, k2.o);
  if (Sgn(dis - k1.r - k2.r) >= 0) return ret;
  if (Sgn(k2.r - (dis + k1.r)) >= 0) return GetV(k1);
  else if (Sgn(k1.r - (dis + k2.r)) >= 0) return GetV(k2);
  db len1 = ((k1.r * k1.r - k2.r * k2.r) / dis + dis) / 2;
  db len2 = dis - len1;
  db x1 = k1.r - len1, x2 = k2.r - len2;
  db v1 = pi * x1 * x1 * (k1.r - x1 / 3.0);
  db v2 = pi * x2 * x2 * (k2.r - x2 / 3.0);
  return v1 + v2;
}
