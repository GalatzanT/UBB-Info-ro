#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "service.h"

 //function that tests all program
void testAll(){
    Test_create_destroy_Participant();
    TestCreateList();
    TestList();
    Test_validare_participant();
    Test_adaugare_participant();
    printf("Trece testul nu-i ca restul!\n\n\n");
}

///cod furat pentru culoare
void printColoredText(char* message, int colorCode) {
        //albastru inchis: 1 sau 9
        //verde: 2 sau 10
        //rosu: 4 sau 12

        HANDLE  hConsole;


        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // you can loop k higher to see more color choices

        SetConsoleTextAttribute(hConsole, colorCode);
        printf("%s",  message);
        //reset to default
        SetConsoleTextAttribute(hConsole, 7);




    }



void ui_adauga_participant(Lista* list){
    char nume[30];
    char prenume[30];
    int scor;
    int probleme[10];
    getchar();
    printf("Nume participant: ");
    fgets(nume,30,stdin);
    printf("Prenume participant: ");
    fgets(prenume,30,stdin);
    printf("Scor participant: ");
    scanf_s("%d", &scor);
    printf("Scorurile la probleme: ");
    for (int i = 0; i < 10; ++i)
    {
        scanf("%d", &probleme[i]);
    }
    nume[strcspn(nume, "\n")] = 0;
    prenume[strcspn(prenume, "\n")] = 0;
    int ErrorCode= adaugare_participant(list,nume,prenume,scor,probleme);
    if(ErrorCode!=0)
        printColoredText("Eroare!Participant invalid!\n",12);
    else
        printColoredText("Paticipant adaugat cu succes!\n",9);

}

void ui_modifica_participant(Lista* l){
    printf("Pozitia participantului care va fi actualizat: ");
    int poz;
    scanf_s("%d", &poz);
    if (poz>=l->lungime) {
        printf("Pozitie invalida\n");
        return;
    }
    printf("Scor nou: ");
    int scor_nou;
    scanf_s("%d", &scor_nou);
    actualizareParticipant(l,poz,scor_nou);
    printf("Scorul participantului a fost modificat\n");
}

void ui_del_participant(Lista * l) {
    printf("Pozitia participantului care va fi eliminat: ");
    int poz;
    scanf_s("%d", &poz);
    if (poz>=l->lungime) {
        printf("Pozitie invalida\n");
        return;
    }
    deletePerson(l, poz);
    printf("Am sters persoana ceruta! \n");


}


void print_participanti(Lista* list){
    for(int i=0;i<size(list);i++){
        Participant p= getElem(list,i);
        printf("Nume: %s | Prenume: %s | Scor: %d ",p.nume,p.prenume,p.scor);
        printf("Scorurile la probleme: ");
        for (int j = 0; j < 10; ++j)
        {
            printf("%d ", p.probleme[j]);
        }
        printf("\n");
    }
}

//function that prints menu
void printMenu() {
    printColoredText("---Concurs de programare---\n",2);
    printf("1.Adauga participant\n");
    printf("2.Actualizarea scorului unui participant existent\n");
    printf("3.Sterge participant dupa pozitie\n");
    printf("4.Afisearea participantilor\n");
    printf("5.Sortarea participantilor dupa scor\n");
    printf("6.Iesire\n");
    printf("Alege o optiune:\n");
}


void ui_sortare_participanti(Lista* l){
    sortare_participanti(l);
    printf("Lista a fost sortata\n");
}

void adaugadefault(Lista* list){
    int probleme[10]={10,10,10,10,10,10,10,10,10,10};
    adaugare_participant(list,"Galatan","Tudor",69,probleme);
    int probleme1[10]={2,3,2,3,2,3,2,3,2,3};
    adaugare_participant(list,"Michael","Jordan",23,probleme1);
    int probleme2[10]={2,10,2,3,6,3,2,7,2,3};
    adaugare_participant(list,"Chuck","Noris",100,probleme2);
}



//menu
void run(){
    testAll();
    Lista list=create_empty();
    adaugadefault(&list);
    bool is_running = true;
    while(is_running){
        printMenu();
        printf(">>>");
        short int option;
        scanf_s("%hd", &option);
        switch (option) {
            case 1:
                printf("A-ti ales optiunea de adaugare a unui participant!\n");
                ui_adauga_participant(&list);
                break;
            case 2:
                ui_modifica_participant(&list);
                break;
            case 3:
                ui_del_participant(&list);
                break;
            case 6:
                is_running=false;
                break;
            case 4:
                printf("Lista de participanti este:\n");
                print_participanti(&list);
                break;
            case 5:
                ui_sortare_participanti(&list);
                break;
            default:
                printf("Optiune invalida!");
                break;
        }
    }

}