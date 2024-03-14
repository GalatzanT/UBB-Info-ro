#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int test;
typedef struct {
    char data[20];
    char descriere[200];
    float suma;
    char tip[10];  // "venit" sau "cheltuiala"
} Tranzactie;

Tranzactie tranzactii[100];
int numarTranzactii = 0;


int esteDataValida(const char *data)
{
    return strlen(data) == 10;
}

int esteDescriereValida(const char *descriere)
{
    return strlen(descriere) > 0;
}

int esteSumaValida(float suma)
{
    return suma >= 0;
}
int esteTipValid(const char *tip)
{
    return strcmp(tip, "venit") == 0 || strcmp(tip, "cheltuiala") == 0;
}
void adaugaTranzactie() {
    printf("\nAdaugare tranzactie noua:\n");

    char data[20];
    char descriere[100];
    float suma;
    char tip[10];

    // Citirea detaliilor tranzacției de la utilizator
    printf("Data (AAAA-LA-ZZ): ");
    scanf("%s", data);

    if (!esteDataValida(data)) {
        printf("Informatia scrisa nu respecta cerința. Tranzactia nu a fost adaugata.\n");
        return;
    }

    printf("Descriere: ");
    scanf(" %[^\n]", descriere);

    if (!esteDescriereValida(descriere)) {
        printf("Informatia scrisa nu respecta cerința. Tranzactia nu a fost adaugata.\n");
        return;
    }

    printf("Suma: ");
    scanf("%f", &suma);

    if (!esteSumaValida(suma)) {
        printf("Informatia scrisa nu respecta cerința. Tranzactia nu a fost adaugata.\n");
        return;
    }

    printf("Tip (venit/cheltuiala): ");
    scanf("%s", tip);

    if (!esteTipValid(tip)) {
        printf("Informatia scrisa nu respecta cerința. Tranzactia nu a fost adaugata.\n");
        return;
    }

    // Adăugarea tranzacției numai dacă informațiile introduse sunt corecte
    strcpy(tranzactii[numarTranzactii].data, data);
    strcpy(tranzactii[numarTranzactii].descriere, descriere);
    tranzactii[numarTranzactii].suma = suma;
    strcpy(tranzactii[numarTranzactii].tip, tip);

    // Incrementarea numărului de tranzacții
    numarTranzactii++;

    printf("Tranzactie adaugata cu succes.\n");
}
float calculeazaSold() {
    float sold = 0;

    for (int i = 0; i < numarTranzactii; i++) {
        if (strcmp(tranzactii[i].tip, "venit") == 0) {
            sold += tranzactii[i].suma;
        } else {
            sold -= tranzactii[i].suma;
        }
    }

    return sold;
}

void afiseazaTranzactii() {
    printf("\nIstoric tranzactii:\n");

    for (int i = 0; i < numarTranzactii; i++) {
        printf("%s %s %.2f %s\n", tranzactii[i].data, tranzactii[i].descriere,
               tranzactii[i].suma, tranzactii[i].tip);
    }
}

void genereazaRaportFinanciar()
{
    printf("\nRaport Financiar:\n");
    printf("\nToate veniturile de pana acum sunt:\n");
    for (int i = 0; i < numarTranzactii; i++)
    {
        if(strcmp(tranzactii[i].tip, "venit") == 0)
        {
            printf("%s - %s: %.2f %s\n", tranzactii[i].data, tranzactii[i].descriere,
                   tranzactii[i].suma, tranzactii[i].tip);
        }

    }
    printf("\nToate cheltuielile de pana acum sunt:\n");
    for (int i = 0; i < numarTranzactii; i++)
    {
        if(strcmp(tranzactii[i].tip, "cheltuiala") == 0)
        {
            printf("%s - %s: %.2f %s\n", tranzactii[i].data, tranzactii[i].descriere,
                   tranzactii[i].suma, tranzactii[i].tip);
        }

    }
}

void salveazaDateInFisier() {
    FILE *fisier = fopen("date_financiare.txt", "w");

    if (fisier == NULL) {
        printf("Eroare la deschiderea fișierului pentru scriere.\n");
        return;
    }

    for (int i = 0; i < numarTranzactii; i++) {
        fprintf(fisier, "%s %s %.2f %s\n", tranzactii[i].data, tranzactii[i].descriere,
                tranzactii[i].suma, tranzactii[i].tip);
    }

    fclose(fisier);
}


void incarcaDateDinFisier()
{
    FILE *in_file=fopen("date_financiare.txt","r");
    if (in_file == NULL) {
        printf("Nu s-au gasit date salvate anterior.\n");
        return;
    }

    while (fscanf(in_file, "%s %s %f %s", tranzactii[numarTranzactii].data,
                  tranzactii[numarTranzactii].descriere, &tranzactii[numarTranzactii].suma,
                  tranzactii[numarTranzactii].tip) == 4)
    {
        fprintf(stdout,in_file, "%s %s %f %s\n", tranzactii[numarTranzactii].data,
                tranzactii[numarTranzactii].descriere, &tranzactii[numarTranzactii].suma,
                tranzactii[numarTranzactii].tip) ;
        numarTranzactii++;
    }

    fclose(in_file);
}
void testare() {
    printf("\nTestare Adăugare Tranzacție \n");
    adaugaTranzactie();  // Adăugare tranzacție valida
    printf("\nTestare Afișare Tranzacții\n");
    afiseazaTranzactii();  // Afișare tranzacții după adăugare
    printf("\nTestare Calcul Sold\n");
    printf("Sold Cont: %.2f\n", calculeazaSold());  // Afișare sold
}
    int main() {
        incarcaDateDinFisier();

        int optiune;

        do {
            printf("\n----- Gestionare Financiara -----\n");
            printf("1. Adauga Tranzactie\n");
            printf("2. Afiseaza Tranzactii\n");
            printf("3. Calculeaza Sold\n");
            printf("4. Genereaza Raport Financiar\n");
            printf("5. Salveaza Date in Fisier\n");
            printf("6. Iesire\n");
            printf("Introduceti optiunea: ");
            scanf("%d", &optiune);

            switch (optiune) {
                case 1:
                    adaugaTranzactie();
                    break;
                case 2:
                    afiseazaTranzactii();
                    break;
                case 3:
                    printf("\nSold Cont: %.2f\n", calculeazaSold());
                    break;
                case 4:
                    genereazaRaportFinanciar();
                    break;
                case 5:
                    salveazaDateInFisier();
                    printf("Tranzactiile s-au salvat in fisier\n");
                    break;
                case 6:
                    // Salvați datele înainte de a ieși
                    salveazaDateInFisier();
                    printf("\nInchiderea programului. La revedere!\n");
                    break;
                default:
                    printf("\n Optiune invalida. Incercati din nou.\n");
            }

        } while (optiune != 7);

        return 0;
    }


