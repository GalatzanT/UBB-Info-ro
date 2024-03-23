#include "myList.h"
#include <assert.h>
Lista create_empty(){
    Lista lst;
    lst.lungime=0;
    return lst;
}

void add(Lista* list, TElem p){
    list->elemente[list->lungime]=p;
    list->lungime++;
}

TElem getElem(Lista* list, int poz)
{
    return list->elemente[poz];
}

int size(Lista* list)
{
    return list->lungime;
}


TElem setElem(Lista* list, int poz, TElem el)
{
    TElem deletedElement = getElem(list, poz);
    list->elemente[poz] = el;
    return deletedElement;
}


TElem delete(Lista* list,int poz){
    TElem deletedElement = getElem(list, poz);
    TElem lastElement = getElem(list, list->lungime - 1);
    setElem(list, poz, lastElement);
    list->lungime--;
    return deletedElement;
}


void TestCreateList() {
    Lista l = create_empty();
    assert(size(&l) == 0);
}

/*
Actualizeaza un participant dupa un id dat
Pre: L-lista de persoane,p-noua persoana, id-idul persoanei pe care vrem sa o modificam
Post: True
*/

void TestList() {
    Lista l = create_empty();
    int probleme[10] = { 10,2,3,4,5,6,7,8,9,10 };
    add(&l, create_Participant( "a", "b", 10, probleme));
    add(&l, create_Participant( "a2", "b2", 20, probleme));
    assert(size(&l) == 2);
    Participant p = getElem(&l, 0);

    assert(strcmp(p.nume, "a") == 0);
    p = getElem(&l, 1);
    assert(strcmp(p.prenume, "b2") == 0);
    delete(&l,1);
    assert(l.lungime==1);
}

