#ifndef VARIABILI_H_INCLUDED
#define VARIABILI_H_INCLUDED

//INIZIALIZZO VARIABILI GLOBALI

float massa;
float aperturaAlare,superficieAlare,corda,mDragRise,dist1,dist2,dist3,dtz,dty,incidenze,rotaryDeriv,cg,Jx,Jy,Jz,Jxz,opzPosBar,newPosBar,posx,posy,posz,elevatorMax,elevatorMin,ailerons,rudder,flapMin,flapMax,opzMassa,frazPesoComb;
double alpha[126];double cx[126];double cy[126];double cz[126];double cl[126];double cm[126];double cn[126];
double cxa[126];double cxap[126];double cxu[126];double cxq[126];double cxb[126];double cxp[126];double cxr[126];
double cyb[126];double cybp[126];double cyp[126];double cyr[126];double cya[126];double cyq[126];
double czal[126];double czap[126];double czu[126];double czq[126];double czb[126];double czp[126];double czr[126];
double clb[126];double clbp[126];double clp[126];double clr[126];double cla[126];double clq[126];
double cma[126];double cmap[126];double cmu[126];double cmq[126];double cmb[126];double cmp[126];double cmr[126];
double cnb[126];double cnbp[126];double cnp[126];double cnr[126];double cna[126];double cnq[126];
double cxde[126];double cxdle[126];double czde[126];double czdle[126];double cyda[126];double cydr[126];
double clda[126];double cldr[126];double cmde[126];double cmdle[126];double cnda[126];double cndr[126];
double diametro,diametro_ogiva,num_pale,inerzia,stazioni,Clalfa,Cd0,Cl0,a0,Cdalfa2,Cdalfa;
double csi[60],rd[60],chad[60],ba[60];
double dati_engine[10],Pmax_h,ph,th,rhoh,ah,h;
double modi[6];
double rampa,alpha_trim,comandi[4],stati[10];
int vel;
#endif
