/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: RITA CERNADAS TUBIO LOGIN 1:rita.cernadas
 * AUTHOR 2: ÁLVARO DÍAZ DÍAZ LOGIN 2: alvaro.ddiaz
 * GROUP: 3.1
 * DATE: 20 / 3 / 20
 */

#include "static_list.h"

void createEmptyList (tList* L){
    L->lastPos = LNULL;
}

bool isEmptyList (tList L){
    return (L.lastPos == LNULL);
}

tPosL first (tList L){
    return 0;
}

tPosL last (tList L){
    return L.lastPos;
}

tPosL next (tPosL p, tList L){
    if( p == L.lastPos)
        return LNULL;
    else
        return ++p;
}

tPosL previous (tPosL p, tList L){
    if( p == first(L))
        return LNULL;
    else
        return --p;
}


bool insertItem(tItemL d, tPosL p, tList* L) {
    tPosL i;
    if (L->lastPos == MAX - 1)
        return false;
    else {
        L->lastPos++;
        if (p == LNULL) {
            L->data[L->lastPos] = d;
        } else {
            for (i = L->lastPos; i >= p+1; i--)
                L->data[i] = L->data[i-1];
            L->data[p] = d;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList* L) {
    tPosL q;

    L->lastPos--;

    for (q = p; q <= L->lastPos; q++)
        L->data[q] = L->data[q+1];
}

tItemL getItem (tPosL p, tList L){
    return (L.data[p]);
}

void updateVotes (tNumVotes v, tPosL p, tList* L){
    L->data[p].numVotes = v;
}

tPosL findItem(tPartyName partyName, tList L){
    tPosL p;
    if(isEmptyList(L)){
        return LNULL;
    }
    else{
        for(p = 0; ((p<L.lastPos) && (strcmp(L.data[p].partyName,partyName)!=0)); p=next(p,L));
        if(strcmp(L.data[p].partyName,partyName)==0){
            return p;
        }
        else{
            return LNULL;
        }
    }
}

void deleteList (tList* L){
    L->lastPos = LNULL;
}