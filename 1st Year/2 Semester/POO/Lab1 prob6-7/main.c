#include <stdio.h>
#include <assert.h>
/**
 * kjgk.g.kg.kjg,kjrkugtfyhjkgf
 * @param k
 * @param m fhjmgkhj
 * @param n jkhhgykjhgkjhg
 */
void primele_n_cifre(int k, int m, int n) {
    int cifre[n];
    for (int i = 0; i < n; i++)
        cifre[i] = 0;
    for (int i = 0; i < n; i++) {
        k *= 10;
        cifre[i] = k / m;
        k %= m;
    }
    for (int i = 0; i < n; i++)
        printf("%d", cifre[i]);
    printf("\n");
}


int nr_prim(int x){
    if(x<2)
        return 0;
    if(x==2)
        return 1;
    for(int d=2;d*d<=x;d++)
        if(x%d==0)
            return 0;
    return 1;

}

void ex_2(int n){
    int i=1;
    if(n){
        printf("%d,",i);
        n--;
    }
    while(n){
        printf(" ");
        i++;
        if(nr_prim(i)==1){
            for(int cop_i=i;cop_i>0;cop_i--){
                printf("%d,",cop_i);
                n--;
                if(n==0)
                    break;
            }

        }
        else{
            printf("%d,", i);
            n--;
            if (n == 0)
                break;
            for(int d=2;d<=i/2;d++){
                if(i%d==0){
                    for(int j=1;j<=d;j++) {
                        printf("%d,", d);
                        n--;
                        if (n == 0){
                            d = i;
                            break;
                        }

                    }
                }

            }
        }


    }
    printf("\n");
}



int main() {
    assert(nr_prim(2)==1);
    assert(nr_prim(68)==0);
    while(1){

        printf("1 Determina primele n cifre din scrierea fractiei subunitare\n k/m = 0.c1c2c3..., pentru k si m numere naturale date.\n");
        printf("2 Tipareste un numar precizat de termeni din sirul\n 1, 2,1, 3,2,1, 4,2,2, 5,4,3,2,1, 6,2,2,3,3,3, 7,6, ...\n");
        printf("0 Exit\n");
        int opt;
        scanf("%d",&opt);
        if(opt==1){
            int n;
            float k,m;

            printf("k=");

            ///citim variabilele

            scanf("%f",&k);
            printf("m=");
            scanf("%f",&m);
            printf("n=");
            scanf("%d",&n);

            ///afisam cifrele
            printf("k/m = 0.");
            primele_n_cifre(k,m,n);
        }
        else if(opt==2){
            int n;
            printf("nr de termeni:");
            scanf("%d",&n);
            ex_2(n);
        }
        else if(opt==0)
            break;
        else
            printf("optiune invalida!\n");

    }

    return 0;
}
