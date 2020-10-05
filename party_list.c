/*
 * TITLE: PROGRAMMING II LABS                  SUBTITLE: Practical 2
 * AUTHOR 1: RITA CERNADAS TUBIO               LOGIN 1: rita.cernadas
 * AUTHOR 2: ÁLVARO DÍAZ DÍAZ                  LOGIN 2: alvaro.ddiaz
 * GROUP: 3.1                                  DATE: 8/05/2020
 */

#include "party_list.h"

void createEmptyList(tList* L){
    *L=LNULL;
}

bool isEmptyList (tList L){
    return (L == LNULL);
}

tPosL first (tList L){
    return L;
}

tPosL last (tList L){
    tPosL p;

    p = L;
    while (p->next != LNULL){ // Recorremos hasta el final de la lista
        p = p-> next;
    }
    return p;
}

tPosL next (tPosL p, tList L){
    if (p->next == LNULL){ //Si es la última posición
        return LNULL;
    }
    else { // Si no es la última
        return p->next;
    }
}

tPosL previous (tPosL p, tList L){
    tPosL q;

    if (p == L){ // Si es la primera posición no tiene anterior, devolvemos NULL
        return LNULL;
    }
    else{ // Sino es la primera
        q = L;
        while(q->next != p){
            q = q->next;
        }
        return q;
    }
}

tItemL getItem (tPosL p, tList L){
    return p -> data;
}

void updateVotes (tNumVotes d, tPosL p, tList *L){
    p->data.numVotes = d;
}

tPosL findPosition(tPartyName partyName, tList L){
    tPosL p;

    p=L;
    while((p->next != LNULL) && (strcmp(p->next->data.partyName, partyName)<0))
        p = p->next;
    return p;
}

tPosL findItem(tPartyName partyName, tList L){
    tPosL p;

    if(isEmptyList(L)) {
        return LNULL;
    }
    else
        for(p=L; ((p!= LNULL) && (strcmp(p->data.partyName, partyName)<0)); p= p->next);
    if( (p!= LNULL )&& (strcmp(p->data.partyName, partyName)==0)) {
        return p;
    }
    else
        return LNULL;
}

bool createNode (tPosL *p){
    *p=malloc(sizeof(struct tNode));
    return (*p)!= LNULL;
}


bool insertItem(tItemL d, tList *L){
    tPosL q,p;
    if(!(createNode (&q)))
        return false;
    else{
        q->data = d;
        q->next = LNULL;
        if (*L == LNULL) //insertar en lista vacia
            *L = q;
        else if (strcmp(d.partyName, (*L)->data.partyName)<0){ //inserccion al principio
            q->next = *L;
            *L = q;
        }
        else{					//buscamos la posicion
            p = findPosition(d.partyName,*L);
            q->next = p->next;	//asigna NULL si insertamos al final
            p->next = q;
        }
        return true;
    }
}

void deleteAtPosition ( tPosL p, tList *L ){
    tPosL q;

    if ( p == *L ) { // Si es la primera posición
        *L = (*L)->next;
    }else if( p->next == LNULL ){ // Si es la última posición
        for( q = *L ; q->next != p; q = q->next );
        q->next = LNULL;
    }else{ // En los casos restantes
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

void deleteList(tList *L) {
    tPosL p;

    while( *L != LNULL ){ // Recorremos las lista y vamos eliminando las posiciones
        p = *L;
        *L = (*L)->next;
        free(p);
    }
}