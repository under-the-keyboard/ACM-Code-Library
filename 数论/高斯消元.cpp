const int Mod = 1e9 + 7;
const int maxn = 1e3 + 5;
const double eps = 0.0000001;
const int INF = 0x3f3f3f3f;

int n, m;
double a[maxn][maxn], x[maxn];
bool manySolutionFlag = false, noSolution = false;

void Swap(int i, int j) {
    for (int k = 1; k <= n + 1; k ++)
        swap(a[i][k], a[j][k]);
}

bool Check(int i) {
    bool vis = false;
    for (int j = 1; j <= n; j ++) {
        if(fabs(a[i][j]) >= eps) vis = true;
    }
    if(!vis && fabs(a[i][n + 1]) >= eps) return false;
    return true;
}

void GS() {
    for (int i = 1; i <= n; i ++) {
        bool flag = false;
        for (int j = i; j <= m; j ++) {
            if(a[j][i] != 0) {
                Swap(j, i);
                flag = true;
                break;
            }
        }
        if(!flag) {
            manySolutionFlag = true;
        }
        for (int j = i + 1; j <= m; j ++)
            for (int k = n + 1; k >= i; k --)
                a[j][k] = a[j][k] * 1. - a[i][k] * (a[j][i] * 1./a[i][i] * 1.) * 1.;

    }
    for (int i = 1; i <= m; i ++) {
        if(!Check(i)) {
            noSolution = true;
            return ;
        }
    }
    for (int i = n; i >= 1; i --) {
        for (int j = i + 1; j <= n; j ++) {
            a[i][n + 1] = a[i][n + 1] - a[i][j] * x[j];
            a[i][j] = 0;
        }
        x[i] = a[i][n + 1] * 1./a[i][i] * 1.;
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i ++)
        for (int j = 1; j <= n + 1; j ++)
            cin >> a[i][j];
    GS();
    if(noSolution) cout << "No solutions" << endl;
    else if(manySolutionFlag) cout << "Many solutions" << endl;
    else {
        for (int i = 1; i <= n; i ++)
            cout << (int)(x[i] +0.5) << endl;
    }
    return 0;
}


