#include "participant.h"
#pragma once

typedef Participant TElem;
typedef struct{
    TElem elemente[100];
    int lungime;
}Lista;


/*
  creeaza o lista vida
 * */
Lista create_empty();

/*
 adauga un element la safarstitul listei

 * */
void add(Lista* list, TElem p);

TElem getElem(Lista* list, int poz);


int size(Lista* list);


TElem setElem(Lista* list, int poz, TElem el);

TElem delete(Lista* list,int poz);

void TestCreateList();

void TestList();
