#ifndef ATMOSFERA_H_INCLUDED
#define ATMOSFERA_H_INCLUDED
#include "variabili.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//---------------------------ATMOSFERA-----------------------------//

void atmosfera()
{
    double p0=101325,t0=15,rho0=1.225,a0=340;
    double R=287.05;
    int scelta,flag;

    printf("\n\t\t\t\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\-ATMOSFERA ISA STANDARD-\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
    printf("\nLa simulazione fa riferimento al modello atmosferico ISA, avente i segeunti valori per quota h=0 m (sea level):\n\n");
    printf("\tPressione: \t\t P = %lf  [Pa]\n",p0);
    printf("\tTemperatura: \t\t T = %g  \t    [gradi C]\n",t0);
    printf("\tDensita': \t\t rho = %g \t    [kg/m^3]\n",rho0);
    printf("\tVelocita' del Suono: \t a = %g \t    [m/s]\n",a0);

    printf("\nSe non si desidera procedere con i suddetti parametri e' possibile modificarli, reinserendoli manualmente o scegliendo una quota differente.\n");

    do
        {
            printf("\nScegliere:\n");
            printf("\t[1] se si desidera procedere con i valori iniziali precedentemente indicati;\n"); // mantiene i valori iniziali di default
            printf("\t[2] se si desidera modificare i valori iniziali a h=0;\n"); //modifica i valori iniziali di default
            printf("\t[3] se di desidera immettere i valori manualmente a una quota specifica (richiesta in seguito);\n");// immette i valori manualmente a una data quota senza richiederla poi

            scanf("%d",&scelta);

            if(scelta!=1 && scelta!=2 && scelta!=3)
            {
                scanf("%*[^\n]"); //svuota il buffer di scanf se immetto un carattere invece che un numero
                printf("[!] WARNING immettere un numero da 1 a 3!\n");
            }

           if (scelta == 1){// mantiene i valori iniziali di default
                flag = 1;
                printf("Si utilizzano i valori di default per l'atmosfera standard a quota zero.\n");
           }
           if (scelta == 2){//modifica i valori iniziali di default
                printf("\n1- Inserire un valore di pressione (h=0) in Pa:");
                scanf("%lf",&p0);
                if(p0<0) {
                    do { //controllo che il numero immesso sia maggiore di zero
                        printf("[!]WARNING immettere un numero positivo!\n");
                        printf("\n1- Inserire un valore di pressione (h=0) in Pa:");
                        scanf("%lf",&p0);
                    } while (p0<0);
                }

                printf("\n2- Inserire un valore di temperatura (h=0) in gradi Celsius:");
                scanf("%lf",&t0);

                printf("\n3- Inserire un valore di densita' (h=0) in kg/m^3:");
                scanf("%lf", &rho0);
                if(rho0<0) {
                    do { //controllo che il numero immesso sia maggiore di zero
                        printf("[!]WARNING immettere un numero positivo!\n");
                        printf("\n3- Inserire un valore di densita' (h=0) in kg/m^3:");
                        scanf("%lf", &rho0);
                    } while (rho0 < 0);
                }

                printf("\n4- Inserire un valore di velocita' (h=0) del suono in m/s:");
                scanf("%lf", &a0);
                if(a0<0) {
                    do { //controllo che il numero immesso sia maggiore di zero o effettivamente un numero
                        printf("[!]WARNING immettere un numero positivo!\n");
                        printf("\n4- Inserire un valore di velocita' (h=0) del suono in m/s:");
                        scanf("%lf",&a0);
                    } while (a0<0);
                }

                flag = 1;
            }

            if (scelta == 3) {// immette i valori manualmente a una data quota senza richiederla poi
                printf("1- Inserire un valore di pressione in Pa:");
                scanf("%lf",&ph);
                if(ph<0) {
                    do { //controllo che il numero immesso sia maggiore di zero
                        printf("[!]WARNING immettere un numero positivo!\n");
                        printf("1- Inserire un valore di pressione in Pa:");
                        scanf("%lf",&ph);
                    } while (ph < 0);
                }

                printf("2- Inserire un valore di temperatura in C:");
                scanf("%lf",&th);

                printf("3- Inserire un valore di densita' in kg/m^3:");
                scanf("%lf",&rhoh);
                if(rhoh<0) {
                    do { //controllo che il numero immesso sia maggiore di zero
                        printf("[!]WARNING immettere un numero positivo!\n");
                        printf("3- Inserire un valore di densita' in kg/m^3:");
                        scanf("%lf",&rhoh);
                    } while (rhoh < 0);
                }

                printf("4- Inserire un valore di velocita' del suono in m/s:");
                scanf("%lf",&ah);
                if(ah<0) {
                    do { //controllo che il numero immesso sia maggiore di zero o effettivamente un numero
                        printf("[!]WARNING immettere un numero positivo!\n");
                        printf("4- Inserire un valore di velocita' del suono in m/s:");
                        scanf("%lf",&ah);
                    } while (ah < 0);

                }
                flag = 2;
            }
    }
    while(scelta!=1 && scelta!=2 && scelta!=3);


    if (flag==1) // calcola le condizioni atmosferiche e di potenza per i valori a quota zero di default o inseriti dall'utente
    {
        printf("\nINSERIRE LA QUOTA DI VOLO: [m] \n");
        scanf("%lf",&h);

        if(h<0)
        {
            do{
                printf("[!]ERRORE: Quota minore di zero!");
                printf("\nINSERIRE LA QUOTA DI VOLO: [m] \n");
                scanf("%lf",&h);
            } while(h<0);
        }

    //if controllo quota di tangenza

        t0= t0 + 273.15;
        th=t0 - 0.0065*h;
        ph=p0*(pow((th/(t0)),5.2561));
        rhoh=ph/(R*(th));
        Pmax_h= dati_engine[0]* pow(rhoh/(rho0),dati_engine[1]);

        printf("\nI dati atmosferici e di potenza per la quota di %lf m sono:\n\n",h);
        printf("Temperatura: \t\t%lf    [K]\n",th);
        printf("Pressione: \t\t%lf [Pa]\n",ph);
        printf("Desita': \t\t%lf      [kg/m^3]\n",rhoh);
        printf("Potenza: \t\t%lf    [kW]\n",Pmax_h);

    }
     if (flag==2) // usa i valori scelti dall'utente
     {
        th=th+273.15;
        Pmax_h=dati_engine[0]* pow(rhoh/(rho0),dati_engine[1]);

        printf("\nI dati atmosferici e di potenza per la quota di %lf m sono:\n\n",h);
        printf("Temperatura: \t\t%lf    [K]\n",th);
        printf("Pressione: \t\t%lf [Pa]\n",ph);
        printf("Desita': \t\t%lf      [kg/m^3]\n",rhoh);
        printf("Potenza: \t\t%lf    [kW]\n",Pmax_h);

     }

    return;
}

#endif

