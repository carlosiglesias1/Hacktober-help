/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: RITA CERNADAS TUBIO LOGIN 1:rita.cernadas
 * AUTHOR 2: ÁLVARO DÍAZ DÍAZ LOGIN 2: alvaro.ddiaz
 * GROUP: 3.1
 * DATE: 20 / 3 / 20
 */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include <string.h>
#define CODE_LENGTH 2

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif

void new (tPartyName partyName, tList *L){
    /*Objetivo: Crear un nuevo partido e introducirlo al final de la lista con los votos inicializados a 0.
    Entradas: Nombre del partido y lista donde introducirlo.
    Salidas: La lista modificada.
    Precondiciones: No es posible incorporar partidos si ya se ha ejecutado la orden vote y que la lista esté inicializada.
    Postcondiciones: Ninguna.*/

    tItemL dato;

    if (findItem(partyName, *L) == LNULL){ //En caso de que el partido no esté en la lista, lo inicializamos con votos a 0.
        strcpy(dato.partyName, partyName);
        dato.numVotes = 0;
        if (insertItem(dato,LNULL,L) == true )//Insertamos en la lista.
            printf("* New: party %s\n", partyName);
        else{
            printf("+ Error: New not possible\n");
        }
    }
    else { //en caso de que el partido exista.
        printf("+ Error: New not possible\n");
    }
}

void vote (tPartyName partyName, tList *L, tNumVotes *nulos, tNumVotes *votos){
    /*Objetivo: Incrementar en 1 el número de votos de un partido de la lista.
    Entradas: Nombre del partido a votar, la lista y el número de votos y de nulos.
    Salidas: La lista modificada y el número de votos y de nulos modificado.
    Precondiciones: La lista no está vacía.
    Postcondiciones: Ninguna.*/

    tPosL posPart;
    tItemL datos;

    posPart = findItem(partyName,*L); // Buscamos el partido en la lista de partidos.
    if (posPart != LNULL){ // En caso de que el partido esté en la lista.
        datos = getItem(posPart,*L);
        updateVotes(datos.numVotes+1,posPart,L); //Incrementamos el número de votos en 1.
        *votos += 1;
        printf("* Vote: party %s numvotes %d\n", partyName, datos.numVotes+1);
    }
    else{ //El partido no está en la lista, se incrementa el número de votos nulos
        *nulos += 1;
        printf("+ Error: Vote not possible. Party %s not found. NULLVOTE\n", partyName);
    }
}

void stats (tPartyName censados, tList L,tNumVotes nulos,tNumVotes votos){
    /*Objetivo: Mostrar la lista completa de partidos actuales y el porcentaje de participación.
    Entradas: Una lista, los partidos de esta y el número de votos y de nulos.
    Salidas: Mensajes con las estadísticas correspondientes.
    Precondiciones: La lista no está vacía.
    Postcondiciones: Ninguna*/

    tPosL posPart;
    tItemL datos;

    posPart = first(L); // Seleccionamos el primer partido.
    while( posPart != LNULL){ // Recorremos la lista de los partidos.
        datos = getItem(posPart,L);
        if (datos.numVotes != 0) { // En caso de que ese partido tenga votos.
            printf("Party %s numvotes %d (%.2f%%)\n", datos.partyName, datos.numVotes,
                   (double) datos.numVotes * 100 / votos); //comprobar
        }
        else{ // Partido sin votos.
            printf("Party %s numvotes %d (0.00%%)\n", datos.partyName, datos.numVotes);
        }
        posPart = next(posPart,L); // Accedemos al siguiente partido.
    }
    printf("Null votes %d\n", nulos);
    if (censados != 0) {
        printf("Participation: %d votes from %s voters (%.2f%%)\n", votos + nulos, censados,
               (double) (votos + nulos) * 100 / atol(censados));
    }
}

void illegalize (tPartyName partyName, tList* L, tNumVotes *nulos, tNumVotes *votos){
    /*Objetivo: Mostrar la lista completa de partidos actuales y el porcentaje de participación.
    Entradas: Una lista, los partidos de ésta y el número de votos nulos.
    Salidas: Mensajes con las estadisticas correspondientes.
    Precondiciones: La lista no está vacía.
    Postcondiciones: Ninguna.*/

    tPosL posPart;
    tItemL datos;

    posPart = findItem(partyName,*L);
    if( posPart == LNULL){
        printf("+ Error: Illegalize not possible\n");
    }
    else{
        datos = getItem(posPart,*L);
        (*nulos) += datos.numVotes;
        (*votos) -= datos.numVotes;
        datos.numVotes = 0;
        updateVotes(datos.numVotes, posPart,L);
        deleteAtPosition(posPart,L);
        printf("* Illegalize: party %s\n",partyName);
    }
}

void liberarRecursos(tList* L){
    /*Objetivo: Vaciar lista de memoria.
    Entradas:La lista con elementos.
    Salidas: Ninguna.
    Precondiciones: La lista no está vacía.
    Postcondiciones: Ninguna.*/

    tPosL posPart;
    while (!isEmptyList(*L)){ //borramos las posiciones de la lista.
        posPart = first(*L);
        deleteAtPosition(posPart,L);
    }
    deleteList(L); //eliminamos la lista de memoria.
}

void processCommand(char command_number[CODE_LENGTH+1], char command, char param[NAME_LENGTH_LIMIT+1], tList *L, tNumVotes *nulos, tNumVotes *votos) {
    printf("********************\n");
    switch(command) {
        case 'N': {
            printf("%s %c: party %s\n", command_number, command, param);
            new(param,L);
            break;
        }
        case 'V':{
            printf("%s %c: party %s\n", command_number, command, param);
            vote(param,L,nulos, votos);
            break;
        }
        case 'S':{
            printf("%s %c: totalvoters %s\n", command_number, command, param);
            stats(param,*L,*nulos,*votos);
            break;
        }
        case 'I':{
            printf("%s %c: party %s\n", command_number, command, param);
            illegalize(param,L,nulos,votos);
            break;
        }
        default: {
            break;
        }
    }
}

void readTasks(char *filename) {
    FILE *df;
    char command_number[CODE_LENGTH+1], command, param[NAME_LENGTH_LIMIT+1];
    // Declaración de la lista.
    tList L;
    // Declaración de las variables.
    tNumVotes nulos = 0;
    tNumVotes votos = 0;

    createEmptyList(&L);// Inicializamos la lista.
    df = fopen(filename, "r");
    if (df != NULL) {
        while (!feof(df)) {
            char format[16];
            sprintf(format, "%%%is %%c %%%is", CODE_LENGTH, NAME_LENGTH_LIMIT);
            fscanf(df,format, command_number, &command, param);
            processCommand(command_number, command, param,&L,&nulos,&votos);
        }
        fclose(df);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
    liberarRecursos(&L); //eliminamos la lista de memoria.
}

int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}
