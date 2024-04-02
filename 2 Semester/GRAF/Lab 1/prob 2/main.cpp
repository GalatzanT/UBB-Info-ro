#include <iostream>
#include <fstream>

using namespace std;
ifstream f("graf.in");

void ex1(int a[101][101], int v) {
    for (int i = 1; i <= v; i++) {
        int s = 0;
        for (int j = 1; j <= v; j++)
            s += a[i][j];
        if (s == 0)
            cout << i << " ";
    }
}

void ex2(int a[101][101], int v) {
    int nr_vec = 0;
    for (int j = 1; j <= v; j++) {
        nr_vec += a[1][j];
    }
    int ok = 1;
    for (int i = 2; i <= v; i++) {
        int nr_vec_crt = 0;
        for (int j = 1; j <= v; j++)
            nr_vec_crt += a[i][j];
        if (nr_vec != nr_vec_crt)
            ok = 0;
    }
    if (ok)
        cout << "2.Graful e regular"<<endl;
    else
        cout << "2.Graful nu e regular"<<endl;


}

void ex3(int a[101][101], int v) {

    int dr[101][101];
    for (int i = 1; i <= v; i++)
        for (int j = 1; j <= v; j++) {
            if (i == j)
                dr[i][j] = 0;
            else if (a[i][j] == 1)
                dr[i][j] = 1;
            else
                dr[i][j] = 1000;
        }
    ///roy FLoyd
    for (int i = 1; i <= v; i++)
        for (int j = 1; j <= v; j++)
            for (int k = 1; k <= v; k++)
                if (dr[i][j] > dr[i][k] + dr[k][j])
                    dr[i][j] = dr[i][k] + dr[k][j];


    for (int i = 1; i <= v; i++) {
        for (int j = 1; j <= v; j++)
            cout << dr[i][j] << " ";
        cout << endl;
    }


}

///ex4

bool vizitat[101] = {0};

void DFS(int a[101][101], int varf, int v) {
    vizitat[varf] = true;
    for (int i = 1; i <= v; i++)
        if (a[varf][i]==1 &&  !vizitat[i]) {
            DFS(a, i, v);
        }
}

void ex4(int a[101][101], int v) {
    DFS(a, 1, v);
    int ok=1;
    for(int i=1;i<=v;i++)
        if(!vizitat[i])
            ok=0;
    if(ok)
        cout<<"4.Graful e conex";
    else
        cout<<"4.Graful nu e conex";
}


int main() {
    int v, e;
    f >> v >> e;
    int x, y;
    int m_a[101][101];
    for (int i = 1; i <= e; i++) {
        f >> x >> y;

        ///mat adiacenta
        m_a[x][y] = 1;
        m_a[y][x] = 1;
    }
    cout << "1.Nodurile izolate sunt:";
    ex1(m_a, v);
    cout << endl;
    ex2(m_a, v);
    cout << "3.Matricea drumurilor:" << endl;
    ex3(m_a, v);

    ex4(m_a,v);
    return 0;
}
