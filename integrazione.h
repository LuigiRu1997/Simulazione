
#ifndef INTEGRAZIONE_H_INCLUDED
#define INTEGRAZIONE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "variabili.h"
#include <math.h>
#define g 9.81


double integrazione(double stati[][], double comandi[][], double m_fuel, double t[], double dt, double time_max){

double V[],alfa[],beta[];
double X[],Y[],Z[],L[],M[],N[]; //forze aerodinamiche
double RPM; //numero di giri
double residui[12];
int i=0;
double cx1,cy1,cz1,cl1,cm1,cn1;
double u1,v1,w1,p1,q1,r1,fi1,theta1,psi1,h1;
double massa_vel,point;

m_fuel=frazPesoComb*massa;
massa_vel=massa;

t[0]=0;
point=t[0];

while(point<=time_max){

t[i]=t[0]+i*dt;

u1=stati[i][0];
v1=stati[i][1];
w1=stati[i][2];
p1=stati[i][3];
q1=stati[i][4];
r1=stati[i][5];
fi1=stati[i][6];
theta1=stati[i][7];
psi1=stati[i][8];
h1=stati[i][9];


//Calcolo velocità, beta, alfa
V[i]=sqrt(u1*u1+v1*v1+w1*w1);
alfa[i]=atan(w1/u1);
beta[i]=asin(v1/V[i]);

if(V[i]<30){
        printf("\n[!]Errore, la velocità è inferiore alla velocità di stallo!\n");
        system("PAUSE");
        exit(1);
}
else if(V[i]>75){
        printf("\n[!]Errore, la velocità è superiore alla velocità massima!\n");
        system("PAUSE");
        exit(1);
}
else if(h1<=0){
        printf("\n[!]Errore, la quota è minore o uguale a 0!\n");
        system("PAUSE");
        exit(1);
}
else if(h1>4116){
        printf("\n[!]Errore, la quota è superiore alla quota di tangenza!\n");
        system("PAUSE");
        exit(1);
} //i valori di v_max,v_stallo,h_tang si trovano in lezione 1 - slide 16


//Calcolo coefficienti aerodinamici
//in main devo aver calcolato i coefficienti cx_ss,cx_alpha, cx_delta per la condizione di trim con interpol
cx1=cx_ss+cx_alpha*alfa[i]+cx_deltae*comandi[i][1];
cy1=cy_ss+cy_alpha*alfa[i]+cy_deltaa*comandi[i][0]+cy_deltar*comandi[i][2];
cz1=cz_ss+cz_alpha*alfa[i]+cz_deltae*comandi[i][1];
cl1=cl_alpha*alfa[i]+cl_deltaa*comandi[i][0]+cl_deltar*comandi[i][2];
cm1=cm_alpha*alfa[i]+cm_deltae*comandi[i][1];
cn1=cn_alpha*alfa[i]+cn_deltaa*comandi[i][0]+cn_deltar*comandi[i][2];


//Calcolo forze aerodinamiche
X[i]=(0.5*rhoh*S*V[i]*V[i])*cx1;
Y[i]=(0.5*rhoh*S*V[i]*V[i])*cy1;
Z[i]=(0.5*rhoh*S*V[i]*V[i])*cz1;
L[i]=(0.5*rhoh*S*V[i]*V[i]*aperturaAlare)*cl1;
M[i]=(0.5*rhoh*S*V[i]*V[i]*corda)*cm1;
N[i]=(0.5*rhoh*S*V[i]*V[i]*aperturaAlare)*cn1;


//Calcolo spinta, coppia, numero di giri propeller
RPM=((2700-1500)/100)*comandi[i,3];
propel(RPM); //richiamo propel per il calcolo di T,Q
//devo assegnare spinta a T[i] e calcolare P_alb (se non è in globali)


//calcolo carburante e massa velivolo
if(i>0){
m_fuel=point;
m_fuel=m_fuel-dt*dati_engine[5]*P_albero;
if(m_fuel<=0){
        printf("\n[!]Errore, il carburante è finito!\n");
        system("PAUSE");
        exit(1);
}
if(opzMassa==1){
massa_vel=massa_vel-(point-m_fuel);
}
}

//Calcolo residui
residui[0]=(r1*v1-q1*w1)-g*sin(theta1)+X[i]/massa_vel[i]+T[i]/massa_vel;
residui[1]=(p1*w1-r1*u1)+g*sin(fi1)*cos(theta1)+Y[i]/massa_vel;
residui[2]=(q1*u1-p1*v1)+g*cos(fi1)*cos(theta1)+Z[i]massa_vel;
residui[3]=-(Jz-Jy)*q1*r1/Jx+(p1*q1)*Jxz/Jx+L[i]/Jy; // !!! C'è un r_punto che non so come implementare!!!
residui[4]=-(Jx-Jz)*p1*r1/Jy-(p1*p1-r1*r1)*Jxz/Jy+M[i]/Jy;
residui[5]=-(Jy-Jx)*p1*q1/Jz-(q1*r1)*Jxz/Jz+N[i]/Jz; // !!! C'è un p_punto che non so come implementare!!!
residui[6]=p1+q1*sin(fi1)*tan(theta1)+r1*cos(fi1)*tan(theta1);
residui[7]=q1*cos(fi1)-r1*sin(fi1);
residui[8]=q1*sin(fi1)/cos(theta1)+r1*cos(fi1)/cos(theta1);
residui[9]=-u1*sin(theta1)+v1*cos(theta1)*sin(fi1)+w1*cos(theta1)*sin(fi1);
residui[10]=u1*cos(psi1)*cos(theta1)+v1*(cos(psi1)*sin(theta1)*sin(fi1)-sin(psi1)*cos(theta1))+w1*(cos(psi1)*sin(theta1)*cos(fi1)+sin(psi1)*sin(fi1));
residui[11]=u1*sin(psi1)*cos(theta1)-v1*(sin(psi1)*sin(theta1)*sin(fi1)-cos(psi1)*cos(fi1))+w1*(sin(psi1)*sin(theta1)*cos(fi1)-cos(psi1)*sin(fi1));

point=t[0]+(i+1)*dt;

if(point<=time_max){

//Calcolo nuovi stati all'istante di tempo successivo

stati[i+1][0]=stati[i][0]+dt*residui[0];
stati[i+1][1]=stati[i][1]+dt*residui[1];
stati[i+1][2]=stati[i][2]+dt*residui[2];
stati[i+1][3]=stati[i][3]+dt*residui[3];
stati[i+1][4]=stati[i][4]+dt*residui[4];
stati[i+1][5]=stati[i][5]+dt*residui[5];
stati[i+1][6]=stati[i][6]+dt*residui[6];
stati[i+1][7]=stati[i][7]+dt*residui[7];
stati[i+1][8]=stati[i][8]+dt*residui[8];
stati[i+1][9]=stati[i][9]+dt*residui[9];
stati[i+1][10]=stati[i][10]+dt*residui[10];
stati[i+1][11]=stati[i][11]+dt*residui[11];

}

i++;


}

printf("\nIl tempo della simulazione e' finito.\n")
return 1;

}


#endif
