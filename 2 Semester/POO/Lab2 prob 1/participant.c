#include "participant.h"
#include <assert.h>

Participant create_Participant(char *nume, char *prenume, int scor, int probleme[]) {
    Participant p;
    strcpy_s(p.nume, sizeof(p.nume), nume);
    strcpy_s(p.prenume, sizeof(p.prenume), prenume);
    p.scor = scor;
    for (int i = 0; i < 10; i++)
        p.probleme[i] = probleme[i];
    return p;
}

void destroy_Participant(Participant* p){
    p->prenume[0]='\0';
    p->nume[0]='\0';
    p->scor=-1;
    for(int i=0;i<10;i++)
        p->probleme[i]=-1;

}



void Test_create_destroy_Participant(){
    int scor[] = { 0, 10, 2, 3, 4, 5, 6, 7, 8, 9 };
    Participant p = create_Participant( "Marian", "Vanghelie", 100, scor);
    assert(strcmp(p.nume, "Marian") == 0);
    assert(strcmp(p.prenume, "Vanghelie") == 0);
    assert(p.scor == 100);

    destroy_Participant(&p);
    assert(strlen(p.nume) == 0);
    assert(strlen(p.prenume) == 0);
    assert(p.scor == -1);
}
