#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "variabili.h"
#include "lettura_dba.h"
#include "lettura_propeller.h"
#include "lettura_engine.h"
#include "interpol.h"
#include "atmosfera.h"
#include "routh2.h"
#define g 9.81
#define pi 3.14

int main(){
float x,cas;
double alphaTrim;
float cxa_trim, cma_trim, cmq_trim, cmap_trim, cza_trim;
double v, delta_routh;
lettura_propeller();
lettura_dba();
lettura_engine();
atmosfera();
alphaTrim=1.69; //valori di alpha_trim e velocità presi a caso

routh2(alphaTrim);



//delta_routh = routh(alpha_trim,v,cxa_trim,cma_trim,cmq_trim,cmap_trim,cza_trim);
//printf("t05_ph=%lf, T_ph=%lf, ph_st=%lf, t05_sp=%lf, T_sp=%lf, sp_st=%lf \n\n ",modi[0],modi[1],modi[2],modi[3],modi[4],modi[5]);

/*
   //TEST FUNZIONE INTERPOL
    printf("\n\ninserisci valore alpha\n"); //alpha inserito da utente
    scanf("%f",&x);
    printf("\n");
    while(x<alpha[0] || x>alpha[125]){ //verifico se alpha è nel range
        printf("[!]WARNING immettere valore alpha compreso nel range\n");
        scanf("%f",&x);
    }
    cas=funz(alpha,cx,x); //interpolazione
    printf("Valore del coefficiente: %12.8f\n",cas);
*/


 }
