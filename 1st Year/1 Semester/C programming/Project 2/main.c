#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int index;
    char nume[50];
    char parola[50];
} Cont;

typedef struct {
    int index;// persoana care face tranzactia
    int index2; //persoana caruia se trimit banii
    char descriere[40];
    char tip2[20]; //venit sau cheltuiala + -
    float suma;
} Tranzactie;

typedef struct {
    int index;
    char nume[50];
    char prenume[50];
    char CNP[13];
    int varsta;
} Client;


#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100
#define MAX_CUSTOMERS 100

Cont conturi[MAX_ACCOUNTS];
Tranzactie tranzactii[MAX_TRANSACTIONS];
Client clienti[MAX_CUSTOMERS];
int nrconturi = 0;
int nrtranzactii = 0;
int nrclienti = 0;

void salveazaTranzactii() {
    FILE *fisier = fopen("Tranzactii.txt", "w");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului Tranzactii.txt pentru scriere\n");
        return;
    }

    for (int i = 0; i < nrtranzactii; i++) {
        fprintf(fisier, "%d %d %s %s %.2f\n", tranzactii[i].index, tranzactii[i].index2, tranzactii[i].descriere,
                tranzactii[i].tip2, tranzactii[i].suma);
    }

    fclose(fisier);
}

void salveazaConturi() {
    FILE *fisier = fopen("Conturi.txt", "w");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului Conturi.txt pentru scriere\n");
        return;
    }

    for (int i = 0; i < nrconturi; i++) {
        fprintf(fisier, "%d %s %s\n", conturi[i].index, conturi[i].nume, conturi[i].parola);
    }

    fclose(fisier);
}

void salveazaClienti() {
    FILE *fisier = fopen("Clientii.txt", "w");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului Clientii.txt pentru scriere\n");
        return;
    }

    for (int i = 0; i < nrclienti; i++) {
        fprintf(fisier, "%d %s %s %s %d\n", clienti[i].index, clienti[i].nume, clienti[i].prenume,
                clienti[i].CNP, clienti[i].varsta);
    }

    fclose(fisier);
}

// Funcție pentru citirea datelor din fișierul Conturi.txt
void citesteConturi() {
    FILE *file = fopen("Conturi.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%d %s %s", &conturi[nrconturi].index, conturi[nrconturi].nume,
                      conturi[nrconturi].parola) == 3) {
            nrconturi++;
        }
        fclose(file);
    } else {
        printf("Eroare la deschiderea fisierului Conturi.txt\n");
    }
}

// Funcție pentru citirea datelor din fișierul Tranzactii.txt
void citesteTranzactii() {
    FILE *file = fopen("Tranzactii.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%d %d %s %s %f", &tranzactii[nrtranzactii].index, &tranzactii[nrtranzactii].index2,
                      tranzactii[nrtranzactii].descriere, tranzactii[nrtranzactii].tip2,
                      &tranzactii[nrtranzactii].suma) ==
               5) {
            nrtranzactii++;
        }
        fclose(file);
    } else {
        printf("Eroare la deschiderea fisierului Tranzactii.txt\n");
    }
}

// Funcție pentru citirea datelor din fișierul Clientii.txt
void citesteClienti() {
    FILE *file = fopen("Clientii.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%d %s %s %s %d", &clienti[nrclienti].index, clienti[nrclienti].nume,
                      clienti[nrclienti].prenume, clienti[nrclienti].CNP, &clienti[nrclienti].varsta) == 5) {
            nrclienti++;
        }
        fclose(file);
    } else {
        printf("Eroare la deschiderea fisierului Clientii.txt\n");
    }
}

float calculare_balanta(int index) {
    float balanta = 0.0;
    // Iterăm prin toate tranzactiile
    for (int i = 0; i < nrtranzactii; i++) {
        // Verificăm dacă tranzacția aparține contului cu indexul dat
        if (tranzactii[i].index2 == index) {
            // Adăugăm sau scădem suma în funcție de tipul tranzacției
            if (strcmp(tranzactii[i].tip2, "venit") == 0) {
                balanta += tranzactii[i].suma;
            } else if (strcmp(tranzactii[i].tip2, "cheltuiala") == 0) {
                balanta -= tranzactii[i].suma;
            }
            // Poți adăuga și alte tipuri de tranzacții în funcție de necesități
        }
    }

    return balanta;
}

void admin() {
    int o;
    printf("Ziua buna domn admin! Ce doresti sa faci azi?\n");
    printf("Balanta contului tau este: %.2f $\n", calculare_balanta(1));
    printf("1.Verfica listele din fisiere:Conturi,Tranzactii,Clienti\n");
    printf("2.Nimic, ma intorc pe meniul principal\n");
    printf("Raspunsul tau:");
    while (scanf("%d", &o) != 1 && o != 1 && o != 2) {
        printf("Optiune invalida. Introduceti un numar valid.\n");
        while (getchar() != '\n');
    }
    if (o == 1) {
        // Afisare pentru testare
        printf("Conturi:\n");
        for (int i = 0; i < nrconturi; i++) {
            printf("%d %s %s\n", conturi[i].index, conturi[i].nume, conturi[i].parola);
        }

        printf("\nTranzactii:\n");
        for (int i = 0; i < nrtranzactii; i++) {
            printf("%d %d %s %s %.2f\n", tranzactii[i].index, tranzactii[i].index2, tranzactii[i].descriere,
                   tranzactii[i].tip2, tranzactii[i].suma);
        }

        printf("\nClienti:\n");
        for (int i = 0; i < nrclienti; i++) {
            printf("%d %s %s %s %d\n", clienti[i].index, clienti[i].nume, clienti[i].prenume, clienti[i].CNP,
                   clienti[i].varsta);
        }
        int o2;
        printf("1.Merci, ma intorc la meniul principal!:");
        if (scanf("%d", &o2) != 1 && o2 != 1) {
            printf("Optiune invalida. Introduceti un numar valid.\n");

        }
        if (o2 == 1)
            printf("Intoarcere la meniul principal...\n");
    }
    if (o == 2)
        printf("Intoarcere la meniul principal...\n");
}


void sterge_din_memorie(int index) {
    // Sterge contul din memorie
    for (int j = 0; j < nrconturi; j++) {
        if (conturi[j].index == index + 1) {
            for (int k = j; k < nrconturi - 1; k++) {
                conturi[k] = conturi[k + 1];
            }
            nrconturi--;
            break;
        }
    }

    // Sterge clientul din memorie
    for (int j = 0; j < nrclienti; j++) {
        if (clienti[j].index == index + 1) {
            for (int k = j; k < nrclienti - 1; k++) {
                clienti[k] = clienti[k + 1];
            }
            nrclienti--;
            break;
        }
    }

    // Sterge tranzactiile din memorie
    for (int j = 0; j < nrtranzactii; j++) {
        if (tranzactii[j].index == index + 1 || tranzactii[j].index2 == index + 1) {
            for (int k = j; k < nrtranzactii - 1; k++) {
                tranzactii[k] = tranzactii[k + 1];
            }
            nrtranzactii--;
            j--;  // Reajustăm indexul pentru a verifica următoarea tranzacție
        }
    }
}

void sterge_cont(int i) {
    // Sterge contul, clientul și tranzactiile din memorie
    sterge_din_memorie(i);
}

void creeaza_tranzactie(int index, int index2, const char *descriere, const char *tip2, float suma) {
    if (nrtranzactii < MAX_TRANSACTIONS) {
        // Verificăm dacă există spațiu în array-ul tranzactii
        tranzactii[nrtranzactii].index = index;
        tranzactii[nrtranzactii].index2 = index2;
        strcpy(tranzactii[nrtranzactii].descriere, descriere);
        strcpy(tranzactii[nrtranzactii].tip2, tip2);
        // Alte inițializări pentru data, tip2 etc. pot fi adăugate aici, în funcție de nevoi
        tranzactii[nrtranzactii].suma = suma;

        // Incrementăm numărul de tranzacții
        nrtranzactii++;

        printf("Tranzactie creata cu succes!\n");
    } else {
        printf("Nu mai este loc pentru tranzactii.\n");
    }
}

float validare_suma() {
    float suma;
    int ok;
    do {
        ok = 0;
        printf("Introduceti suma: ");
        if (scanf("%f", &suma) != 1) {
            printf("Suma introdusa nu este valida. Va rugam sa introduceti un numar valid.\n");
            ok = 1;
            while (getchar() != '\n');  // Curățăm buffer-ul în caz de eroare la citire
        } else {
            if (suma < 0) {
                printf("Suma trebuie sa fie un numar pozitiv.\n");
                ok = 1;
            }
        }
    } while (ok == 1);

    return suma;
}

void factura_cont(int index) {
    float sum = validare_suma();

    printf("Puteti trimite %.2f $ pe BT-PAY la numarul 0747762720\n", sum);
    creeaza_tranzactie(10000, index + 1, "factura", "venit", sum);
}

int verifica_nume(char *nume) {
    for (int i = 0; i < nrclienti; i++) {
        if (strcmp(nume, clienti[i].nume) == 0) {
            return i; // Returnează indexul clientului găsit
        }
    }
    return -1; // Nu s-a găsit niciun client cu acel nume
}

void transfer_bancar(int index) {
    float sum2 = validare_suma();
    char nume[40];
    printf("Introduceti numele destinatarului: ");
    scanf("%s", nume);
    if (verifica_nume(nume) == -1) {
        while (verifica_nume(nume) == -1) {
            printf("Nu s-a găsit niciun client cu acel nume\n");
            printf("Introduceti numele destinatarului: ");
            scanf("%s", nume);
        }
    }
    creeaza_tranzactie(10000, index + 1, "transfer ", "cheltuiala", sum2);
    creeaza_tranzactie(index + 1, verifica_nume(nume), "transfer", "venit", sum2);


}

void raport_financiar(int ind) {
    printf("\nVenituri:\n");
    for (int i = 0; i < nrtranzactii; i++) {
        if (tranzactii[i].index2 == ind + 1 && strcmp(tranzactii[i].tip2,"venit")==0)
            printf("%s %.2f\n",tranzactii[i].descriere,tranzactii[i].suma);
    }
    printf("\nCheltuieli:\n");
    for (int i = 0; i < nrtranzactii; i++) {
        if (tranzactii[i].index2 == ind + 1 && strcmp(tranzactii[i].tip2,"cheltuiala")==0)
            printf("%s %.2f\n", tranzactii[i].descriere,tranzactii[i].suma);
    }

}


void cont_utilizator(int i) {
    printf("Bun venit %s %s,ce doresti sa faci azi?\n ", clienti[i].nume, clienti[i].prenume);

    int ok = 1;
    while (ok == 1) {
        printf("Balanta contului tau este: %.2f $\n", calculare_balanta(i + 1));
        printf("1.Sterge cont:(, intoarcere pe pagina principala....\n");
        printf("2.Adauga banii in contul curent+ Generare facura!\n");
        printf("3.Transfer bancar unui user!\n");
        printf("4.Raport financiar: venituri/cheltuieli!\n");
        printf("5.Log Out!\n");
        int optiune;
        printf("Optiunea ta este:");
        scanf("%d", &optiune);
        while (optiune != 1 && optiune != 2 && optiune != 3 && optiune != 4 && optiune != 5) {
            printf("Optiune invalida. Introduceti un numar valid.\n");
            printf("Optiunea ta este:");
            scanf("%d", &optiune);
            while (getchar() != '\n');
        }
        switch (optiune) {
            case 1:
                sterge_cont(i);
                salveazaConturi();
                salveazaTranzactii();
                salveazaClienti();
                printf("Contul sters cu succes\n");
                ok = 0;
                break;
            case 2:
                factura_cont(i);
                salveazaTranzactii();
                break;
            case 3:
                transfer_bancar(i);
                salveazaTranzactii();
                break;
            case 4:
                raport_financiar(i);
                break;
            case 5:
                ok = 0;
                break;

        }
    }
}

void salvare_cont(char user[100], char parola[100]) {
    FILE *fisier;
    int ultimul_index = 0;
    fisier = fopen("Conturi.txt", "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului Conturi.txt\n");
        return;
    }
    char linie[256];  // Presupunem că o linie nu depășește 256 de caractere
    while (fgets(linie, sizeof(linie), fisier) != NULL) {
        int index_curent;
        if (sscanf(linie, "%d", &index_curent) == 1) {
            // Am găsit un index valid, actualizăm ultimul_index
            ultimul_index = index_curent > ultimul_index ? index_curent : ultimul_index;
        }
    }
    fclose(fisier);
    fisier = fopen("Conturi.txt", "a");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului Conturi.txt\n");
        return;
    }
    fprintf(fisier, "%d %s %s\n", ultimul_index + 1, user, parola);
    fclose(fisier);
    //salveaza si in memorie
    strcpy(conturi[nrconturi].nume, user);
    strcpy(conturi[nrconturi].parola, parola);
    conturi[nrconturi].index = ultimul_index + 1;
    nrconturi++;

}

void salvare_client(char nume[100], char prenume[100], char cnp[100], int varsta) {
    FILE *fisier;
    int ultimul_index = 0;
    fisier = fopen("Clientii.txt", "r");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului Conturi.txt\n");
        return;
    }
    char linie[256];  // Presupunem că o linie nu depășește 256 de caractere
    while (fgets(linie, sizeof(linie), fisier) != NULL) {
        int index_curent;
        if (sscanf(linie, "%d", &index_curent) == 1) {
            // Am găsit un index valid, actualizăm ultimul_index
            ultimul_index = index_curent > ultimul_index ? index_curent : ultimul_index;
        }
    }
    fclose(fisier);
    fisier = fopen("Clientii.txt", "a");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului Conturi.txt\n");
        return;
    }
    fprintf(fisier, "%d %s %s %s %d\n", ultimul_index + 1, nume, prenume, cnp, varsta);
    fclose(fisier);
    //salveaza si in memorie
    strcpy(clienti[nrclienti].nume, nume);
    strcpy(clienti[nrclienti].prenume, prenume);
    strcpy(clienti[nrclienti].CNP, cnp);
    clienti[nrclienti].varsta = varsta;
    clienti[nrclienti].index = ultimul_index + 1;
    nrclienti++;
}


int validare_varsta(int *varsta) {
    if (scanf("%d", varsta) == 1) {
        // Varsta a fost citita corect
        return 1;
    } else {
        // Citirea varstei a esuat
        while (getchar() != '\n'); // Curata buffer-ul
        return 0;
    }
}

int este_cnp_valid(const char *cnp) {
    // Verifică dacă CNP-ul are exact 13 caractere și toate sunt cifre
    if (strlen(cnp) != 13) {
        return 0;  // Lungime incorectă
    }

    for (int i = 0; i < 13; ++i) {
        if (!isdigit(cnp[i])) {
            return 0;  // Caracter nepermis (nu este cifră)
        }
    }

    // Alte verificări specifice pentru CNP pot fi adăugate aici

    return 1;  // CNP-ul este valid
}

void citeste_cnp(char *cnp) {
    int valid = 0;

    do {
        printf("CNP:");
        if (scanf(" %39[^\n]", cnp) == 1) {
            // Verifică CNP-ul și curăță buffer-ul dacă este invalid
            if (!este_cnp_valid(cnp)) {
                valid = 0;
                printf("CNP invalid. ");
            } else {
                valid = 1;
            }
        } else {
            valid = 0;
            printf("Eroare la citirea CNP-ului. ");
        }

        // Curățare buffer
        while (getchar() != '\n');

    } while (!valid);
}


void creare_client() {
    char nume[40];
    printf("Numele tau:");
    scanf(" %39[^\n]", nume);

    char prenume[40];
    printf("Prenumele tau:");
    scanf(" %39[^\n]", prenume);

    char cnp[40];
    citeste_cnp(cnp);
    int varsta = -1;
    printf("Varsta:");
    while (!validare_varsta(&varsta)) {
        printf("Varsta:");
    }
    salvare_client(nume, prenume, cnp, varsta);
}

void autentificare(char user[100], char parola[100]) {
    int ok1 = 0;
    if (strcmp(user, "GalaBoss") == 0 && strcmp(parola, "GalaBoss") == 0) {
        admin();
        ok1 = 1;
    } else {
        for (int i = 0; i < nrconturi; i++)
            if (strcmp(user, conturi[i].nume) == 0 && strcmp(parola, conturi[i].parola) == 0) {
                cont_utilizator(i);
                ok1 = 1;
            }
    }
    if (ok1 == 0) {
        printf("Nu s-a gasit nici un cont:(\n");
        printf("1.Creeaza un cont nou cu userul si parola noua\n");
        printf("2.Inapoi la meniul principal\n");
        printf("Alege o optiune(ex 1,2):");
        int o;
        while (scanf("%d", &o) != 1 && o != 1 && o != 2) {
            printf("Optiune invalida. Introduceti un numar valid.\n");
            while (getchar() != '\n');
        }
        if (o == 1) {
            salvare_cont(user, parola);
            creare_client();
            printf("Contul creat cu succes!\n");
        } else if (o == 2)
            printf("Intoarcere la meniul principal...\n");
    }
}

void run() {
    citesteConturi();
    citesteTranzactii();
    citesteClienti();
    int ok = 1;
    int opt;
    do {
        printf("---BANCA GO4MONEY---\n");
        printf("1.login\n");
        printf("2.iesire\n");
        printf("Alege o optiune!(ex 1,2):");
        while (scanf("%d", &opt) != 1 && opt != 1 && opt != 2) {
            printf("Optiune invalida. Introduceti un numar valid.\n");
            while (getchar() != '\n');
        }
        switch (opt) {
            case 1:
                printf("username:");
                char user[100];
                scanf("%s", user);
                printf("parola:");
                char parola[100];
                scanf("%s", parola);
                autentificare(user, parola);
                break;
            case 2:
                printf("Closing...");
                ok = 0;
        }

    } while (ok != 0);
}
void exportToCSV() {
    FILE *csvFile = fopen("tranzactii.csv", "w");
    if (csvFile == NULL) {
        printf("Eroare la deschiderea .\n");
        return;
    }

    fprintf(csvFile, "TransactionID,Description,Amount\n");

    for (int i = 0; i < numOfRecords; i++) {
        fprintf(csvFile, "%d,%s,%.2f\n", financialData[i].transactionID, financialData[i].description, financialData[i].amount);
    }

    fclose(csvFile);
    printf("Data exported to CSV successfully.\n");
}
int main() {
    run();
    return 0;
}
