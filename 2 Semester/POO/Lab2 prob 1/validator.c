#include "validator.h"
#include <assert.h>

int valideaza_participant(Participant p ){
    if(strlen(p.nume)==0)
        return 10;
    if(strlen(p.prenume)==0)
        return 11;
    if(p.scor<=0)
        return 12;
    for(int i=0;i<10;i++)
        if(p.probleme[i]<=0 || p.probleme[i]>=11)
            return 13;
    return 1;
}



void Test_validare_participant(){
    int probleme[10]={10,10,10,10,10,10,10,10,10,10};
    Participant p= create_Participant("Mirciulica","Gordon",34,probleme);
    int cod_eroare= valideaza_participant(p);
    assert(cod_eroare==1);
    int probleme1[10]={10,10,10,10,10,10,10,10,10,10};
    Participant p2= create_Participant("Mirciulica","Gordon",-43,probleme1);
    int cod_eroare1= valideaza_participant(p2);
    assert(cod_eroare1==12);
    int probleme2[10]={10,10,10,10,10,10,10,10,100,10};
    Participant p3= create_Participant("Mirciulica","Gordon",43,probleme2);
    int cod_eroare2= valideaza_participant(p3);
    assert(cod_eroare2==13);
}