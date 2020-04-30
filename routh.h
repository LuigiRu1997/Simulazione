//
//#ifndef ROUTH_INCLUDED
//#define ROUTH_INCLUDED
//#include <stdio.h>
//#include <stdlib.h>
//#include "variabili.h"
//
//
//double routh(double alphatrim, float massa, float Jy, double rhoh, double v, float superficieAlare, float corda, double cxa, double cma, double cmq, double cmap, double cza){
//
//double cwe, cle, cde, cdalpha, clap, ctu, clalpha, mu, Jyad, cd0_velivolo;
//double A,B,C,D,E,delta,omega_ph,omega_ph_ad,zita_ph,omega_sp,omega_sp_ad,zita_sp,t05_ph,T_ph,t05_sp,T_sp;
//double modi[6];
//
//cd0_velivolo=0.0235;
//k=0.047;
//cwe=(m*9.81)/(0.5*rhoh*superficieAlare*v^2) //L=W in equilibrio (cwe=cle)
//cle=cwe;
//cde=cd0_velivolo+k*(cle^2);
//cdalpha=-cxa*cos(alphatrim)-cza*sin(alphatrim);
//clap=1.56;
//ctu=-0.0841;
//clalpha=cxa*cosa(alphatrim)-cza*sin(alphatrim);
//
//mu=(2*massa)/(rhoh*superficieAlare*corda);
//Jyad=(8*Jy)/(rhoh*superficieAlare*((corda)^3);
//
//A=2*mu*Jyad*(2*mu+clap);
//B=2*mu*Jyad*(clalpha+cde-ctu)-Jyad*ctu*clap-2*mu*cmq*clap-4*(mu^4)*(cmq+cmap);
//C=2*mu*(cmq*(ctu-clalpha-cde)-2*mu*cma+cmap*ctu)+Jyad*(2*mu*(cwe-cdalpha)+ctu*clalpha+cde*clalpha)+cmq*clap*ctu;
//D=-2*(cwe^2)*cmap+2*mu*ctu*cma+ctu*cmq*clalpha-2*cwe*cmq*(cle-cdalpha)+2*cde*cmq*ctu;
//E=-2*(cwe^2)*cma;
//delta=B*C*D-A*(D^2)-(B^2)*E;
//
//if(cma<0){
//        printf("Il velivolo è STABILE STATICAMENTE"); //E>0 è già verificato
//            if(delta>0 && A>0 && B>0){
//                    printf("il velivolo è STABILE DINAMICAMENTE");
//                    //Calcolo caratteristiche modi longitudinali con soluzione approssimata
//
//                    //PHUGOID
//                    zita_ph=cde/(sqrt(2)*cle);
//                    omega_ph_ad=((sqrt(2)*g)/v)*(2*v/c);
//                    omega_ph=omega_ph_ad*(2*v/c);
//                    T_ph=(2*pi/(omega_ph*(sqrt(abs((zita_ph^2)-1))))); //omega è adimensionale???
//                    t05_ph=0.69/(2*zita_ph*omega_ph);
//
//                    modi[0]=T_ph;
//                    MODI[1]=T05_PH;BG
//
//                    if((-omega_ph_ad*zita_ph)>0)){
//                    printf("il fugoide è stabile");
//                    modi[2]=1;
//                    }
//                    else{
//                    printf("il fugoide è instabile");
//                    modi[2]=0;
//                    }
//
//
//                    //SHORT PERIOD
//                    zita_sp=(Jyad*clalpha-2*mu*(cmq+cmap))/(2*(-2*mu*Jyad*(2*mu*cma+cmq*clap)^0.5));
//                    omega_sp_ad=sqrt(-cma/Jyad)*(2*v/c);
//                    omega_sp=sqrt(-cma/Jyad);
//                    T_sp=(2*pi/(omega_sp*(sqrt(abs((zita_sp^2)-1))))); //omega è adimensionale???
//                    t05_sp=0.69/(2*zita_sp*omega_sp);
//
//                    modi[3]=T_sp;
//                    modi[4]=t05_sp;
//
//                    if((-omega_sp_ad*zita_sp)>0)){
//                    printf("il corto periodo è stabile");
//                    modi[5]=1;
//                    }
//                    else{
//                    printf("il corto periodo è instabile");
//                    modi[6]=0;
//                    }
//
//                    }
//            else{
//                    printf("[!]ERROR: il velivolo è INSTABILE DINAMICAMENTE");
//                    }
//            }
//        }
//else{
//    printf("[!]ERROR: il velivolo è INSTABILE STATICAMENTE; stabilità dinamica non è verificata"); //OPPURE UN WARNING E SI CAMBIA ALPHA_TRIM?
//    }
//return modi;
//}
//
//
//#endif
