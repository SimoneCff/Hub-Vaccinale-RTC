#ifndef utils_h
#define utils_h

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

struct record_gp {
    char TesSan[8]; //ultime 8 cifre tessera sanitaria
    int From; // indentificatore per vedere da dove provenie 0 CentroVaccinale, 1 ClientS , 2 ClientT
    int durata; //Durata Green Pass
    int status; // Stato Green Pass, 0 valido, 1 scaduto
};

struct record_gp * create_record(char * TS, int durata, int status, int where);
void printgp(struct record_gp * gp);

#endif