#ifndef PROPEL_H_INCLUDED
#define PROPEL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "variabili.h"
#include "atmosfera.h"
#include "trim.h"

#define pi 3.14159265

//AGGIUNGERE FILE DI VERIFICA??
//CAMBIARE LA RHO1 CON QUELLA A CUI STIAMO VOLANDO
double propel(double diametro, double rpm_ciclo, double ba[], double velocita, double Pmax_h, double rhoh, double Clalfa, double Cd0, double Cl0, double Cdalfa2, double Cdalfa, double num_pale, double dati_propel[])
{
    double chord=0.198; //corda adimensionalizzata di riferimento (-> CH_AD in propeller.txt) //MODIFICATO
    double pitch = 0.0; // pitch del'elica
    //double diam=2; //diametro elica //MODIFICATO
    double Raggio=diametro/2.0; //raggio elica
    double RPM_ref=rpm_ciclo; //RPM di riferimento
    double tip=16.443; //angolo di beccheggio al tip //MODIFICATO
    double xt=Raggio; //coordinata dimensionalizzata al tip
    double hub=58.875; //angolo di becch-.,m neggio all'hub (al 20% del raggio) //MODIFICATO
    double xs=0.2*Raggio; //coordinata dimensionalizzata all'hub //MODIFICATO
    //double rho1=1.225; //densità [kg/m^3]
    double n=RPM_ref/60; //round-per-second
    double omega=n*2*pi; //velocià angolare [rad/s]
    //double coef1=(tip-hub)/(xt-xs); //coefficiente #1 di supporto al calcolo dell'angolo di svergolamento theta
    //double coef2=hub-coef1*xs+pitch; //coefficiente #2 di supporto al calcolo dell'angolo di svergolamento theta
    double rstep; //calcolo step delle 48 stazioni //MODIFICATO(ho tolto anche l'ogiva)
    double r1[60]; //creazione vettore delle 10 stazioni (-> CSI in propeller.txt) //MODIFICATO
    double theta1[60];
    double alpha1[60];
    double t2[49], a2[49],b2[49]; //MODIFICATO
    double th, phi1, eff, DtDr,DqDr,cl,cd,CT,CQ, tem1,tem2;
    double a, anew;
    double b, bnew;
    int j=0,i;
    int finished=0;
    /*Inizializzazione r1*/
    //for(j=11;j<60;j++){ //MODIFICATO
    //    r1[j]=xs+j*rstep;
    //}

    for(i=11;i<60;i++){
               //printf("\n%lf\n",csi[i]);
                //if (i>11){
        r1[i]=csi[i];
        theta1[i]=ba[i];
       // printf("\n%lf\n",theta1[i]);
        //j++;
                }

    double rad;
    //double velocita; //velocità di volo //MODIFICATO
    float Vlocal,V0,V2;
    float thrust=0.0; //inizializzazione vettore spinta
    float torque=0.0;//inizializzazione vettore coppia

    //AGGIUNTA VELOCITA DA UTENTE //MODIFICATO
    //printf("\n\ninserisci il valore della velocità di volo\n"); //velocità di volo inserita da utente
    //scanf("%f",&Vel);
    //printf("\n");

    for(j=12; j<60; j++){ //MODIFICATO
        rstep=csi[j]-csi[j-1];
        rad=r1[j]; //coordinata j-esima stazione (-> CSI in propeller.txt)
        //theta1[j]=coef1*rad+coef2; //calcolo angolo di svergolamento della j-esima stazione
        //ba[j]=theta1; //angolo di svergolamento della j-esima stazione (-> BA su propeller.txt)
        th=theta1[j]/180.0*pi; //angolo di svergolamento [rad]
        a=0.1; //inizializzazione axial inflow factor (vedi pag.4 PROPEL.pdf)
        b=0.01; //inizializzazione angular inflow (swirl) factor (vedi pag.4 PROPEL.pdf)
        finished=0; //inizializzione flag
        int sum=1; //inizializzione variabile di supporto
        while (finished==0){
            V0=velocita*(1+a); //componente del flusso all'incirca uguale alla velocità di avanzamento del velivolo (Vinf), aumentata tramite l'axial inflow factor
            V2=omega*rad*(1-b); //componente del flusso all'incirca uguale alla velocità angolare della sezione della pala (omega*rad), ridotta tramite l'angular inflow factor
            phi1=atan2(V0,V2); //angolo tra le due componenti del flusso V0 e V2
            alpha1[j]=th-phi1; //angolo di attacco raltivo alla j-esima sezione della pala
            cl=Cl0+Clalfa*alpha1[j]; //L coefficiente di portanza //MODIFICATO
            cd=Cd0+Cdalfa*alpha1[j]+Cdalfa2*alpha1[j]*alpha1[j]; // CD coefficiente di resistenza CD = CD0+CD1*CL+CD2*CL^2 (NB nel nostro caso, CD = CD0+CD_alpha*alpha+CD_alpha2*alpha^2 -> slide lezione 2) //MODIFICATO
            Vlocal=sqrt(V0*V0+V2*V2); // velocità locale del flusso
            CT = cl*cos(phi1)-cd*sin(phi1); //CT coefficiente di spinta adimensionale
            DtDr=0.5*rhoh*Vlocal*Vlocal*num_pale*chord*CT; //contributo di spinta della j-esima sezione
            CQ = cd*cos(phi1)+cl*sin(phi1); //CQ coefficiente di coppia adimensionale
            DqDr=0.5*rhoh*Vlocal*Vlocal*num_pale*chord*rad*CQ; //contributo di coppia della j-esima sezione
            tem1=DtDr/(4.0*pi*rad*rhoh*velocita*velocita*(1+a)); //fattore correttivo del coefficiente "a"
            tem2=DqDr/(4.0*pi*rad*rad*rad*rhoh*velocita*(1+a)*omega); //fattore correttivo del coefficiente "b"
            anew=0.5*(a+tem1); //nuovo valore coefficiente "a"
            bnew=0.5*(b+tem2); //nuovo valore coefficiente "b"
            //processo iterativo per arrivare a convergenza
            if (fabs(anew-a)<1/100000){
                if (fabs(bnew-b)<1/100000){
                    finished=1;
                }
            }
            a=anew; //definizione valore finale coefficiente "a"
            b=bnew; //definizione valore finale coefficiente "b"
            sum=sum+1;
            if (sum>500){
                finished=1;
            }
        }
        a2[j]=a; //definizione valore finale coefficiente "a" per la j-esima stazione//FOTTESEGA DI QUESTA
        b2[j]=b; //definizione valore finale coefficiente "b" per la j-esima stazione//FOTTESEGA DI QUESTA
        thrust=thrust+DtDr*rstep; //sommatoria dei contributi di spinta dalla stazione 1 alla stazione j
        torque=torque+DqDr*rstep; //sommatoria dei contributi di coppia dalla stazione 1 alla stazione j

    }

    //printf("**********************\n");
    //printf("Thrust: %f N\n",thrust);
    //printf("Torque: %f Nm\n",torque);
    //printf("**********************\n");

    float t_ad=thrust/(rhoh*n*n*diametro*diametro*diametro*diametro); //coefficiente di spinta adimensionale
    float q_ad=torque/(rhoh*n*n*diametro*diametro*diametro*diametro*diametro); //coefficiente di coppia adimensionale

    //printf("\n%f\n",rhoh);

    float J=velocita/(n*diametro); //rapporto di avanzamento
    if (t_ad<0){
        eff=0.0; //efficienza elica
    }else{
        eff=t_ad/q_ad*J/(2*pi); //efficienza elica
    }

    P_al=torque*omega/1000;//AGGIUNTA
    if (P_al>Pmax_h){//VEDERE COME è CHIAMATO P_MAX NEGLI ALTRI FILE->CHIEDERE AGLI ALTRI
        eff=0;
        printf("WARNING: hai superato la potenza massima\n");
        printf("Poniamo la potenza all'albero equivalente alla potenza massima per l'attuale quota di volo");
        P_al=Pmax_h;
    } //Dobbiamo vedere che la potenza all'albero non sia maggiore della potenza all'albero per quella specifica quota

    dati_propel[0] = thrust;
    dati_propel[1] = torque;
    dati_propel[2] = P_al;

    return 0;
}

#endif
//COME INSERIRE MANETTA?
//float manetta=P_n/P_d
//la manetta è data dal rapporto tra potenza necessaria e potenza diponibile a quella certa quota
