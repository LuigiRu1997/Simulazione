
#ifndef INTERPOL_H_INCLUDED
#define INTERPOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


float interpol(double a[],double c[],float x){

float a1,a2,c1,c2;
int i=1;
int s=0;
float da,m,cx;

    while(i){
        if(x>=a[s] && x<=a[s+1]){
        a1=a[s];
        a2=a[s+1];
        c1=c[s];
        c2=c[s+1];
        i=0; }
        else{
            s++;
        }
    }
    da=x-a1;
    m=(c2-c1)/(a2-a1);
    cx=c1+(m*da);

    //VERIFICA FUNZIONE DI INTERPOLAZIONE
//    if((cx<=c[s+1]+0.000001 && cx>=c[s]-0.000001)||(cx>=c[s+1]-0.000001 && cx<=c[s]+0.000001)){  //i valori di +-10e-6 servono per comprendere errori di approssimazione da calcolo in righe 27-28
//        printf("il valore del coefficiente calcolato %12.6f si trova nell'intervallo [%lf,%lf]\n\n",cx,c[s],c[s+1]);
//    }
//    else{
//        printf("[!]ERROR la verifica della funzione non è andata a buon fine!\n il valore %12.6f NON si trova nell'intervallo [%lf,%lf]\n",cx,c[s],c[s+1]);}

 return cx;
}


#endif
