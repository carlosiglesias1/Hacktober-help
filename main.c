/*
 * TITLE: PROGRAMMING II LABS                  SUBTITLE: Practical 2
 * AUTHOR 1: RITA CERNADAS TUBIO               LOGIN 1: rita.cernadas
 * AUTHOR 2: ÁLVARO DÍAZ DÍAZ                  LOGIN 2: alvaro.ddiaz
 * GROUP: 3.1                                  DATE: 8/05/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "center_list.h"
#define CODE_LENGTH 2

void Create (tCenterName centerName, tNumVotes totalVoters, tListC *L){

    tItemC datosCenter;

    if (findItemC(centerName,*L) == NULLC) {                // Si el centro electoral no está en la lista
        strcpy(datosCenter.centerName,centerName);          // Inicializamos los campos del centro
        datosCenter.totalVoters = totalVoters;
        datosCenter.nullVotes = 0;
        datosCenter.validVotes = 0;
        datosCenter.partyList = 0;
        if (!(insertItemC(datosCenter, L))) {               // Si no se puede insertar el centro electoral
            deleteList((tList *) datosCenter.partyList);               // Eliminamos la lista de partidos del centro electoral
            printf("+ Error: Create not possible \n");
        }
        else                                               // Si se puede insertar el centro electoral
            printf("* Create: center %s totalvoters %d\n", centerName, totalVoters);
    }
    else
        printf("+ Error: Create not possible \n");  // Si el centro electoral está en la lista
}

void New (tCenterName centerName, tPartyName partyName, tListC *L) {

    tPosC posCenter;
    tPosL posPart;
    tItemC datosCenter;
    tItemL datosPart;


    if (!(isEmptyListC(*L))) {                              // Si a lista no está vacía
        posCenter = findItemC(centerName, *L);              // Buscamos el centro en la lista
        if (posCenter != NULLC) {                           // Si la posición del centro no es nula
            datosCenter = getItemC(posCenter, *L);          // Seleccionamos los datos del centro e inicializamos los campos
            strcpy(datosPart.partyName, partyName);
            datosPart.numVotes = 0;
            posPart = findItem(partyName, datosCenter.partyList);
            if ((posPart == LNULL) && (insertItem(datosPart, &datosCenter.partyList)) == true) { // Insertamos el partido en la lista de partidos
                updateListC(datosCenter.partyList, posCenter, L); // Actualizamos la lista de partidos
                printf("* New: center %s party %s \n", centerName, partyName);
            }
            else {
                printf("+ Error: New not possible \n");
            }
        }
        else{
            printf("+ Error: New not possible \n");
        }
    }
}

void Vote (tCenterName centerName, tPartyName partyName, tListC *L){
    tPosC posCenter;
    tPosL posPart;
    tItemC datosCenter;
    tItemL datosPart;
    tList listaPartidos;

    posCenter = findItemC(centerName, *L);                  // Seleccionamos la posición del centro
    if (posCenter != NULLC){                                // Si la posición no es nula
        datosCenter = getItemC(posCenter,*L);
        listaPartidos = datosCenter.partyList;
        posPart = findItem(partyName, listaPartidos);
        if (posPart != NULL){                                                              // Si el centro no está una posición nula
            datosPart = getItem(posPart, L);
            updateVotes(++datosPart.numVotes, posPart, &listaPartidos);                   // Actualizamos el número de votos del partido
            updateValidVotesC(datosCenter.validVotes+1,posCenter,L);               // Actualizamos el número de votos válidos do centro electoral
            printf("* Vote: center %s party %s numvotes %d \n",centerName,partyName,datosPart.numVotes);
        }
        else {
            updateNullVotesC(datosCenter.nullVotes + 1, posCenter,L);              // Actualizamos el número de votos nulos do centro electoral
            printf("+ Error: Vote not possible. Party %s not found in center %s. NULLVOTE\n", partyName, centerName);
        }
    }
    else
        printf("+ Error: Vote not possible \n");
}

void Remove (tListC *L) {

    tItemC datosCenter;
    tPosC posCenter;
    bool borrado = false;
    tPosL posPart;

    if (!(isEmptyListC(*L))){                               // Si a lista non está vacía
        posCenter =firstC(*L);
        while(posCenter!= NULLC){                           // Si la posición no es nula
            datosCenter = getItemC(posCenter,*L);
            if(datosCenter.validVotes == 0) {               // Si el número de votos del centro es 0, se elimina
                printf("holi \n");
                while (!(isEmptyList(datosCenter.partyList))) {
                    posPart = first(datosCenter.partyList);
                    deleteAtPosition(posPart,datosCenter.partyList); // Se borran los partidos hasta que la lista este vacia
                }printf("acabe guacho bajá\n");
                 updateListC(datosCenter.partyList,posCenter,L);                           // Actualizamos la lista de centros
                 printf("* Remove: center %s \n",datosCenter.centerName);
                 deleteAtPositionC(posCenter,L);                // Eliminamos la posición del centro de la lista de centros
                 borrado = true;
            }
            else posCenter = nextC(posCenter,*L);
        }
        if (!borrado){
            printf("* Remove: no centers removed\n");
        }
    }
}

void Stats (tListC L){

    tPosC posCenter;
    tPosL posPart;
    tItemC datosCenter;
    tItemL datosPart;

    if (!(isEmptyListC(L))){                        // Si la lista de centros no está vacía
        posCenter = firstC(L);
        while (posCenter != NULLC){                 // Mientras la posición del centro no sea nula en la lista
            datosCenter = getItemC(posCenter,L);
            printf("Center %s\n",datosCenter.centerName);
            posPart = first(datosCenter.partyList);
            while (posPart != NULL){                // Mientras la posición del partido no sea nula en la lista
                datosPart = getItem(posPart,datosCenter.partyList);
                if (datosPart.numVotes != 0) {      // En caso de que ese partido tenga votos.
                    printf("Party %s numvotes %d (%.2f%%)\n", datosPart.partyName, datosPart.numVotes,
                           (double) datosPart.numVotes * 100 / datosCenter.validVotes);
                }
                else{                               // Partido sin votos.
                    printf("Party %s numvotes %d (0.00%%)\n", datosPart.partyName, datosPart.numVotes);
                }
                posPart = next(posPart,datosCenter.partyList); // Accedemos al siguiente partido.
            }
            printf("Null votes %d\n", datosCenter.nullVotes);
            if (datosCenter.totalVoters != 0) {
                printf("Participation: %d votes from %d voters (%.2f%%)\n", datosCenter.validVotes + datosCenter.nullVotes, datosCenter.totalVoters,
                       (double) (datosCenter.validVotes + datosCenter.nullVotes) * 100 / datosCenter.totalVoters);
            }
            posCenter = nextC(posCenter,L);
        }
    }
}
/*

void LiberarRecursos(tListC *L) {

    tPosC posCenter;
    tPosL posPart;
    tItemC datosCenter;

    while(!(isEmptyListC(*L))){
        posCenter = firstC(*L);
        datosCenter = getItemC(posCenter,*L);
        while (!(isEmptyList(datosCenter.partyList))){
            posPart = first(datosCenter.partyList);
            deleteAtPosition(posPart, (tList *) datosCenter.partyList);
        updateListC(datosCenter.partyList,posCenter,L);
        deleteAtPositionC(posCenter,L);
        }
    }

}
*/
void processCommand(char commandNumber[CODE_LENGTH+1], char command, char param1[NAME_LENGTH_LIMIT+1], char param2[NAME_LENGTH_LIMIT+1],tListC *L) {
    printf("******** \n");
    switch (command) {
        case 'C': {
            printf("%s %c: center %s totalvoters %s\n\n", commandNumber, command, param1, param2);
            Create(param1, atol(param2), L);
            break;
        }
        case 'N': {
            printf("%s %c: center %s party %s\n\n", commandNumber, command, param1, param2);
            New(param1, param2, L);
            break;
        }
        case 'V': {
            printf("%s %c: center %s party %s\n\n", commandNumber, command, param1, param2);
            Vote(param1,param2,L);
            break;
        }
        case 'R': {
            printf("%s %c\n\n", commandNumber, command);
            Remove(L);
            break;
        }
        case 'S': {
            printf("%s %c\n\n", commandNumber, command);
            Stats(*L);
            break;
        }
        default: {
            break;
        }

    }
}

void readTasks(char *filename) {
    FILE *df;
    char commandNumber[CODE_LENGTH+1], command, param1[NAME_LENGTH_LIMIT+1], param2[NAME_LENGTH_LIMIT+1];
    tListC L;               // Declaración de la lista.

    createEmptyListC(&L);   // Inicializamos la lista.
    df = fopen(filename, "r");
    if (df != NULL) {
        while (!feof(df)) {
            char format[16];
            sprintf(format, "%%%is %%c ", CODE_LENGTH);
            fscanf(df, format, commandNumber, &command);
            if (command == 'S' || command == 'R') {
                param1[0] = '\0';
                param2[0] = '\0';
            } else {
                sprintf(format, "%%%is %%%is", NAME_LENGTH_LIMIT, NAME_LENGTH_LIMIT);
                fscanf(df, format, param1, param2);
            }
            processCommand(commandNumber, command, param1, param2, &L);
        }
        fclose(df);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
    //   LiberarRecursos(&L);    // Eliminamos la lista de memoria.
}

int main (int nargs, char **args) {

    char *filename = "new.txt";

    if (nargs > 1) {
        filename = args[1];
    } else {
#ifdef INPUT_FILE
        filename = INPUT_FILE;
#endif
    }

    readTasks(filename);

    return 0;
}