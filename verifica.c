#include <stdio.h>
#include <stdlib.h>
#include "variabili.h"
#include "lettura_dba.h"
#include "lettura_propeller.h"
#include "lettura_engine.h"

int main(){

lettura_propeller();
lettura_dba();
lettura_engine();

printf("La verifica di lettura e' stata completata.\n");
 }
