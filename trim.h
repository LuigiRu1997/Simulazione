#ifndef TRIM_H_INCLUDED
#define TRIM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "variabili.h"
#define pi 3.14
#define g 9.81

void trim()
{

    double d_alpha=0.2;
    double alpha_min,alpha_max,alpha_ciclo;
    double cz_ciclo,czal_ciclo, cz_tot,alpha_trim,forza;
    double res=10;
    int controllo=0;
    double theta_trim, u_trim, w_trim, h_trim;
    double cm_ciclo,cmal_ciclo,cmde_ciclo,cm_trim,cmal_trim,cmde_trim,de_trim;
    double cx_ciclo,cxal_ciclo,cx_tot,cx_trim,cxal_trim,T_trim;
    double stati[10],comandi[4];

    // valori di velocita' di voo e angolo di rampa scelti da utente
    printf("\nTRIM");

    printf("\nInserire velocita' di volo: ");
    scanf("%g", &vel);

    printf("Inserire angolo di rampa in gradi: ");
    scanf("%g", &rampa);

    alpha_min=alpha[0];
    alpha_max=alpha[125];
    alpha_ciclo=alpha_min;

    while (alpha_ciclo<=alpha_max){
        // calcolo dei coefficienti per ogni alpha, in modo che variando il passo questi cambino di conseguenza
        cz_ciclo=funz(alpha,cz,alpha_ciclo);
        czal_ciclo=funz(alpha,czal,alpha_ciclo);
        cz_tot=cz_ciclo+czal_ciclo*(alpha_ciclo*(pi/180));

        cm_ciclo=funz(alpha,cm,alpha_ciclo);
        cmal_ciclo=funz(alpha,cma,alpha_ciclo);
        cmde_ciclo=funz(alpha,cmde,alpha_ciclo);

        cx_ciclo=funz(alpha,cx,alpha_ciclo);
        cxal_ciclo=funz(alpha,cxa,alpha_ciclo);

        forza=fabs(massa*g*cos((alpha_ciclo+rampa)*(pi/180))+0.5*cz_tot*rhoh*superficieAlare*pow(vel,2));

        if (forza<=res){
            alpha_trim=alpha_ciclo;

            controllo=1;

            cm_trim=cm_ciclo;
            cmal_trim=cmal_ciclo;
            cmde_trim=cmde_ciclo;

            cx_trim=cx_ciclo;
            cxal_trim=cxal_ciclo;

            break;
        }
        else{
            alpha_ciclo=alpha_ciclo+d_alpha;
        }
    }
    if (controllo!=1){
        printf("\n[!]ERRORE: alla velocita' e alla quota indicata non e' possibile trovare la condizione di trim.");
        exit(4);
    }

    // CALCOLO DEL VETTORE DEGLI STATI

    theta_trim=alpha_trim+rampa;

    u_trim=vel*cos(alpha_trim*(pi/180));

    w_trim=vel*sin(alpha_trim*(pi/180));

    h_trim=h;

    //stati=[u_trim,0,w_trim,0,0,0,0,theta_trim,0,h_trim];

    // CALCOLO VETTORE DEI COMANDI

    // calcolo delta elevator trim

    de_trim=-((cm_trim+cmal_trim*alpha_trim*(pi/180))/cmde_trim)*(180/pi);

    if (fabs(de_trim)>fabs(elevatorMax)){
        printf ("\n[!]WARNING: deflessione dell'equilibratore in condizioni di trim superiore alla deflessione massima. Si considera una deflessione di 20 gradi.");
        de_trim=elevatorMax;
    }

    // calcolo T trim

    cx_tot=cx_trim+cxal_trim*alpha_trim*(pi/180);

    T_trim=massa*g*sin(theta_trim*(pi/180))-0.5*cx_tot*rhoh*superficieAlare*pow(vel,2);




    //comandi=[de_trim,0,0,RPM_trim];






















}
#endif
