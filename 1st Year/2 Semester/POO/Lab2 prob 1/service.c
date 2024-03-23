#include "service.h"
#include <assert.h>

/**
 * functie care creaza un participant si daca este valid il adauga in lista
 * @param list
 * @param nume
 * @param prenume
 * @param scor
 * @param probleme
 * @return
 */
int adaugare_participant(Lista* list, char* nume, char* prenume,int scor, int probleme[10]){
    Participant p= create_Participant(nume,prenume,scor,probleme);
    int val_cod= valideaza_participant(p);
    if(val_cod!=1)
        return val_cod;
    add(list,p);
    return 0;
}

int deletePerson(Lista* list ,int poz){
    delete(list, poz);
    return 0;
}
/**
 * schimba scorul unui participant cu unul nou
 * @param l
 * @param poz
 * @param scor_nou
 */
void actualizareParticipant(Lista * l, int poz, int scor_nou) {
    TElem modifiedElement= getElem(l,poz);
    modifiedElement.scor=scor_nou;
    ///modfica_participant(l,modifiedElement,scor_nou);
    l->elemente[poz]=modifiedElement;

}

void sortare_participanti(Lista* l) {
    for (int i = 0; i < l->lungime - 1; i++)
        for (int j = i + 1; j < l->lungime; j++)
            if (getElem(l, i).scor > getElem(l, j).scor) {
                TElem aux = getElem(l, i);
                l->elemente[i] = getElem(l, j);
                l->elemente[j] = aux;
            }

}
void Test_adaugare_participant(){
    Lista l=create_empty();
    int score1[10] = { 9,2,3,4,5,6,7,8,9,10 };
    int score2[10] = { -10,-2,-3,-4,-5,-6,-7,-8,-9,-10 };
    int error = adaugare_participant(&l, "", "b", 10, score2);
    assert(error != 0);
    assert(size(&l) == 0);

    error = adaugare_participant(&l, "a", "", 10, score1);
    assert(error != 0);
    assert(size(&l) == 0);
    int score3[10] = { 9,2,3,4,5,6,7,8,9,10 };
    error = adaugare_participant(&l, "aa", "bb", 10, score3);
    assert(error == 0);
    assert(size(&l) == 1);
    sortare_participanti(&l);

    assert(l.elemente[0].scor==10);
    int score4[10] = { 9,2,3,4,5,6,7,8,9,10 };
    error = adaugare_participant(&l, "aaa", "bbb", 5, score3);

    assert(error == 0);
    sortare_participanti(&l);
    assert(l.elemente[1].scor==10);
    deletePerson(&l,0);
    assert(size(&l) == 1);

    actualizareParticipant(&l,0,67);
    assert(l.elemente[0].scor==67);

}


