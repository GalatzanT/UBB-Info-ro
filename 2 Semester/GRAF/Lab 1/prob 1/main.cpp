#include <iostream>
#include <fstream>

using namespace std;
ifstream fin ("in.txt");


int main()
{
    int v;
    int e;
    fin>>v>>e;

    int mat_ad[101][101]={0};
    int lis_ad[101][101]={0};
    int mat_inc[101][101]={0};
    int x,y,c=0;
    ///Citim muchile din fisier si rezolvam misiunea
    for(int i=1;i<=e;i++){
        fin>>x>>y;

        ///mat adiacenta
        mat_ad[x][y]=1;
        mat_ad[y][x]=1;

        ///lista adiacenta
        lis_ad[x][0]++;
        lis_ad[y][0]++;
        lis_ad[x][lis_ad[x][0]]=y;
        lis_ad[y][lis_ad[y][0]]=x;

        ///matricea incidenta
        mat_inc[x][c]=1;
        mat_inc[y][c]=1;
        c++;
    }
    ///Afisam matricea adiacenta
    cout<<"Matricea de adiacenta este:"<<endl;
    for(int i=1;i<=v;i++){
        for(int j=1;j<=v;j++)
            cout<<mat_ad[i][j]<<" ";
        cout<<endl;
    }
    ///Afisam lista de adiacenta
    cout<<"Lista de adiacenta este:"<<endl;
    for(int i=1;i<=v;i++){
        for(int j=0;j<=v;j++){
            if(lis_ad[i][j]!=0 or j==0){
                cout<<lis_ad[i][j];
                if(j==0)
                    cout<<": ";
                else
                    cout<<", ";
            }

        }

        cout<<endl;
    }
    ///Afisam matricea adiacenta
    cout<<"Matricea de adiacenta este:"<<endl;
    for(int i=1;i<=v;i++){
        for(int j=0;j<e;j++)
            cout<<mat_inc[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
