#pragma once
#include <string.h>
typedef struct {
    char nume[20];
    char prenume[20];
    int scor;
    int probleme[10];
}Participant;



/*
 functie care creeaza un participant are nevoie de:
 nume
 prenume
 scor
 probleme
*/
Participant create_Participant(char* nume, char* prenume, int scor,int probleme[]);

void destroy_Participant(Participant* p);

void Test_create_destroy_Participant();

