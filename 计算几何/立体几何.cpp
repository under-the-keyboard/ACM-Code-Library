typedef double db;
const db inf = 1e100;
const db eps = 1e-9;
const db pi = acos(-1.);
const db delta = 0.98;
int Sgn(db k) { return std::fabs(k) < eps ? 0 : (k < 0 ? -1 : 1); }
int Cmp(db k1, db k2) { return Sgn(k1 - k2); }
int Min(db k1, db k2) { return Cmp(k1, k2) < 0 ? k1 : k2; }
int Max(db k1, db k2) { return Cmp(k1, k2) > 0 ? k1 : k2; }
struct point { db x, y, z; }
bool operator == (point k1, point k2) { return !Sgn(k1.x - k2.x) && !Sgn(k1.y, k2.y) && !Sgn(k1.z, k2.z); }
point operator + (point k1, point k2) { return (point){k1.x + k2.x, k1.y + k2.y, k1.z + k2.z}; }
point operator - (point k1, point k2) { return (point){k1.x - k2.x, k1.y - k2.y, k1.z - k2.z}; 
point operator * (point k1, db k2) { return (point){k1.x * k2, k1.y * k2, k1.z * k2};  }
point operator / (point k1, db k2) { return (point){k1.x / k2, k1.y / k2, k1.z / k2};  }
db operator * (point k1, point k2) { k1.x * k2.x + k1.y * k2.y + k1.z * k2.z; }
point operator ^ (point k1, point k2) { return (point){k1.y * k2.z - k1.z * k2.y, k1.z * k2.x - k1.x * k2.z, k1.x * k2.y - k1.y * k2.x}; }
db GetLen(point k) { return std::sqrt(k * k); }
db GetLen2(point k) { return k * k; }
point GetUnit(point k) { return k / GetLen(k); }
db GetDis(point k1, point k2) { return GetLen(k2 - k1); }
db GetDis2(point k1, point k2) { return GetLen2(k2 - k1); }
db GetMinSphereR(std::vector<point> p) {
  point cur = p[0];
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
struct line { point s, t; };
struct seg: public line {};
db GetLen(seg k) { return GetDis(k.s, k.t); }
db GetLen2(seg k) { return GetDis2(k.s, k.t); }
db GetDis(point k1, line k2) { return std::fabs((k1 - k2.s) ^ (k2.t - k2.s)) / GetLen(k2); }
db GetDis(point k1, seg k2) {
  if (Sgn((k1 - k2.s) * (k2.t - k2.s)) < 0 || Sgn((k1 - k2.t) * (k2.s - k2.t)) < 0)
    return Min(GetDis(k1, k2.s), GetDis(k1, k2.t));
  return GetDis(k1, seg); // point to line dis
}
struct sphere { point o; db r; };
db GetV(sphere k) { return 4. / 3. * pi * k.r * k.r * k.r; }
db GetInterV(sphere k1, sphere k2) {
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
