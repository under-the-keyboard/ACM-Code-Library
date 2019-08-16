double Com(double X) {
    return sqrt((X - x) * (X - x) + (a * X * X + b * X + c - y) * (a * X * X + b * X + c - y));
}
void Binary(double l, double r) {
    if(l + eps <= r) {
        double lm, rm;
        double k = r - l;
        lm = l + (1./3) * k;
        rm = r - (1./3) * k;
        if(fabs(Com(lm) - Com(rm)) <= eps) {
             printf("%.3lf\n", Com(lm));
             return ;
        }
        if(Com(lm) < Com(rm))
            Binary(l, rm);
        else Binary(lm, r);
    }
}