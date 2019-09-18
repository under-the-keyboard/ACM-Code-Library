int right_triangle(long long a, long long &b, long long &c) { // 已知直角边，求另外两个边
    if (a & 1) b = a * (a/2) + a/2, c = b + 1;
    else b = a * (a/2) / 2 - 1, c = b + 2;
    return (a > 0 && b > 0 && c > 0); 
}
