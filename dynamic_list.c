/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: RITA CERNADAS TUBIO LOGIN 1:rita.cernadas
 * AUTHOR 2: ÁLVARO DÍAZ DÍAZ LOGIN 2: alvaro.ddiaz
 * GROUP: 3.1
 * DATE: * / * / **
 */

#include "dynamic_list.h"


void createEmptyList(tList* L){
    *L=LNULL;
}

bool isEmptyList (tList L){
    return (L == LNULL);
}

tPosL first (tList L){
    return L;
}

tPosL next (tPosL p, tList L){
    return p->next;
}

tPosL last (tList L){
    tPosL p;
    p = L;
    while (p->next != LNULL){
        p = p-> next;
    }
    return p;
}

tPosL previous (tPosL p, tList L){
    tPosL q;
    if (p == L){
        return LNULL;
    }
    else{
        q = L;
        while(q->next != p){
            q = q->next;
        }
    }
    return q;
}

tItemL getItem (tPosL p, tList L){
    return p -> data;
}

void updateVotes (tNumVotes d, tPosL p, tList* L){
    p->data.numVotes = d;
}

tPosL findItem (tPartyName partyName, tList L){
    tPosL p;
    for (p = L; ((p!= LNULL) && (strcmp(p-> data.partyName, partyName)!=0)); p=next(p, L));
    return p;
}

bool createNode (tPosL *p){
    *p=malloc(sizeof(**p));
    return (*p)!= LNULL;
}

bool insertItem (tItemL d, tPosL p, tList *L){
    tPosL q,r;

    if (!createNode(&q)){
        return false;
    }
    else{
        q->data = d;
        q->next = LNULL;

        if(*L == LNULL)
            *L= q;
        else if (p == LNULL){
            for(r = *L; r->next != LNULL; r = r->next);
            r->next = q;
        }
        else if (p == *L){
            q->next = *L;
            *L = q;
        }
        else {
            q->data = p->data;
            p->data = d;
            q->next = p->next;
            p->next = q;
        }

        return true;
    }
}

void deleteAtPosition ( tPosL p, tList *L ){
    tPosL q;
    if ( p==*L ) {
        *L = (*L)->next;
    }else if( p->next == LNULL ) {
        for( q = *L ; q->next != p; q = q->next );
        q->next = LNULL;
    }else{
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

void deleteList( tList *L ) {
    tPosL p;
    while( *L != LNULL ){
        p = *L;
        *L = (*L)->next;
        free(p);
    }
}