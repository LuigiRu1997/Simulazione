#ifndef ROUTH_INCLUDED
#define ROUTH_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "variabili.h"
#include "interpol.h"
#include "lettura_dba.h"
#include "lettura_propeller.h"
#include <math.h>

double routh2 (double alphaTrim)
{
    double cd0_velivolo=0.0235;
    double k=0.047;
    double Clap=1.56;
    double Ctu=-0.0841;

    double g = 9.81;
    double pi = 3.14;

    double Cdalfa_trim,Clalfa_trim,Cmalfa_trim,Cxalfa_trim,Cmq_trim,Cmap_trim,Cza_trim,mi,Jy_ad,Cde,A,B,C,C1,C2,C3,C4,C5,D,E,Delta,Cle;
    double zita_ph,omega_ph_ad,omega_ph,T_ph,t_12_PH, num,den,zita_sp,omega_sp,omega_sp_ad,T_sp,t_12_SP;
    double vel=52;

    Cmalfa_trim     =interpol(alpha,cma,alphaTrim);
    printf("\nIl valore di Cma_trim e' %f",Cmalfa_trim);
    Cxalfa_trim     =interpol(alpha,cxa,alphaTrim);
    printf("\nIl valore di Cxalfa_trim e' %f",Cxalfa_trim);
    Cmq_trim        =interpol(alpha,cmq,alphaTrim);
    printf("\nIl valore di Cmq_trim e' %f",Cmq_trim);
    Cmap_trim       =interpol(alpha,cmap,alphaTrim);
    printf("\nIl valore di Cmap_trim e' %f",Cmap_trim);
    Cza_trim        =interpol(alpha,czal,alphaTrim);
    printf("\nIl valore di Cza_trim e' %f",Cza_trim);

    Clalfa_trim =Cxalfa_trim*sin(alphaTrim*pi/180) - Cza_trim*cos(alphaTrim*pi/180);
    printf("\nIl valore di Clalfa_trim e' %f",Clalfa_trim);

    Cle = (massa*9.81)/(0.5*rhoh*superficieAlare*vel*vel); //L=W in equilibrio (cwe=cle)
    printf("\nIl valore del momento di Cle e' %f",Cle);
        //Cdalfa_trim = -Cxalfa_trim*cos(alphaTrim*pi/180)-Cza_trim*sin(alphaTrim*pi/180);
    Cdalfa_trim = 2*k*Clalfa_trim*Cle;
    printf("\nIl valore di Cdalfa_trim e' %f",Cdalfa_trim);

    mi = (2*massa)/(rhoh*superficieAlare*corda);
    printf("\nIl valore della massa adimensionalizzata e' %f",mi);
    Jy_ad = (8*Jy)/(rhoh*superficieAlare*corda*corda*corda);
    printf("\nIl valore del momento di inerzia Y adimensionalizzato e' %f",Jy_ad);
    Cde = cd0_velivolo + k*Cle*Cle;
    printf("\nIl valore di Cde e' %f",Cde);


    A = 2*mi*Jy_ad*(2*mi+Clap);
    printf("\nIl valore del coefficiente A e' %f",A);
    B = 2*mi*Jy_ad*(Clalfa_trim+Cde-Ctu)-Jy_ad*Ctu*Clap-2*mi*Cmq_trim*Clap - 4*mi*mi*(Cmq_trim+Cmap_trim);
    printf("\nIl valore del coefficiente B e' %f",B);
    C1 = Cmq_trim*(Ctu-Clalfa_trim-Cde);
    //printf("\nIl valore di C1 e' %f",C1);
    C2 = (2*mi*Cmalfa_trim + Cmap_trim*Ctu);
    //printf("\nIl valore di C2 e' %f",C2);
    C3 = 2*Cle*(Cle-Cdalfa_trim);
    //printf("\nIl valore di C3 e' %f",C3);
    C4 = Ctu*Clalfa_trim + Cde*Clalfa_trim;
    //printf("\nIl valore di C4 e' %f",C4);
    C5 = Cmq_trim*Clap*Ctu;
    //printf("\nIl valore di C5 e' %f",C5);
    //C = 2*mi*(Cmq_trim*(Ctu-Clalfa_trim-Cde)-2*mi*Cmalfa_trim + Cmap_trim*Ctu)+Jy_ad*((2*Cle)*(Cle-Cdalfa_trim)+Ctu*Clalfa_trim+Cde*Clalfa_trim)+Cmq_trim*Clap*Ctu;
    C = 2*mi*(C1-C2)+Jy_ad*(C3+C4)+C5;
    printf("\nIl valore del coefficiente C e' %f",C);
    D = -2*Cle*Cle*Cmap_trim + 2*mi*Ctu*Cmalfa_trim + Ctu*Cmq_trim*Clalfa_trim -2*Cle*Cmq_trim*(Cle-Cdalfa_trim)+2*Cde*Cmq_trim*Ctu;
    printf("\nIl valore del coefficiente D e' %f",D);
    E = -2*Cle*Cle*Cmalfa_trim;
    printf("\nIl valore del coefficiente E e' %f",E);
    Delta = (B*C*D)-(A*D*D)-(B*B*E);
    printf("\nIl valore del coefficiente Delta e' %f",Delta);

    if (Cmalfa_trim<0)
        {
            printf("\nIl velivolo e' STABILE STATICAMENTE ");
            if (Delta>0 && A >0 && B >0 && D>0)
            {
                printf("\nIl velivolo e' STABILE DINAMICAMENTE");
                //Calcolo le caratteristiche di fugoide:
                zita_ph = Cde/(sqrt(2)*Cle);
                omega_ph_ad = sqrt((Cle*Cle)/(2*mi*mi));
                //omega_ph = (sqrt(2)*g/vel)*(2*vel/corda);
                omega_ph = omega_ph_ad*(2*vel/corda);
                printf("\nValore di OMEGA_PH %f",omega_ph);
                printf("\nValore di zita_ph %f",zita_ph);
                T_ph = (2*pi)/(omega_ph*sqrt(fabs((zita_ph*zita_ph)-1)));
                t_12_PH =0.69 / (zita_ph*omega_ph);
                printf("\nValore del TPH %lf", T_ph);
                printf("\nValore del T12_PH %lf", t_12_PH);
                if (-(zita_ph*omega_ph)<0) // parte reale <0
                {
                    printf("\nIl fugoide e' STABILE");
                }
                else
                {
                    printf("\nIl fugoide e' INSTABILE");
                }

                //Calcolo cordo periodo:
                num = Jy_ad*Clalfa_trim - 2*mi*(Cmq_trim+Cmap_trim);
                den = -2*mi*Jy_ad*(2*mi*Cmalfa_trim+Cmq_trim*Clap);
                zita_sp = num/(2*sqrt(den));
                omega_sp_ad = sqrt(-(Cmalfa_trim/Jy_ad));
                omega_sp = omega_sp_ad *2*vel/corda;
                printf("\nValore di OMEGA_SP %f",omega_sp);
                printf("\nValore di zita_sp %f",zita_sp);
                T_sp = 2*pi / (omega_sp*sqrt(fabs((zita_sp*zita_sp)-1)));
                t_12_SP = 0.69 / (zita_sp*omega_sp);
                printf("\nValore del TSP %lf", T_sp);
                printf("\nValore del T12_SP %lf", t_12_SP);
                if(-(zita_sp*omega_sp)<0) //parte reale <0
                {
                    printf("\nIl corto periodo e' STABILE");
                }
                else
                {
                    printf("\nIl corto periodo e' INSTABILE");
                }

            }
            else
            {
                printf("\n[!]ERRORE: VELIVOLO INSTABILE DINAMICAMENTE");
            }


        }

    else {printf("\nStabilita' statica NON VERIFICATA. VELIVOLO INSTABILE STATICAMENTE");}

}

#endif
