#pragma once
#include "myList.h"
#include "validator.h"




/*
 adauga participant
 * */
int adaugare_participant(Lista* list, char* nume, char* prenume,int scor, int probleme[10]);

int deletePerson(Lista* list ,int poz);

void actualizareParticipant(Lista * l, int poz, int scor_nou);

void sortare_participanti(Lista* l);

void Test_adaugare_participant();
