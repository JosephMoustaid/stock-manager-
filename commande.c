#include<stdio.h>
#include<stdlib.h>
#include "commande.h"

LigCmd* creerLigCmd(void){
    LigCmd *ligCmd=malloc(sizeof(LigCmd));
    if(ligCmd==NULL) exit(EXIT_FAILURE);
    printf("Num commande : "); scanf("%d",&ligCmd->numCmd); fflush(stdin);
    printf("Ref article : "); scanf("%s",ligCmd->refArt);
    printf("Qte article : ");scanf("%d",&ligCmd->qteArt);
    printf("Prix article : ");scanf("%f",&ligCmd->prixArt);
    return ligCmd;
}

void afficherLigCmd(LigCmd* ligCmd){
    printf("%d \t %s \t %d \t %.2f \n" ,ligCmd->numCmd ,ligCmd->refArt ,  ligCmd->qteArt , ligCmd->prixArt);
}

void creerListeCmdVide(ListeCmd* listeCmd){

    listeCmd->taille=0;
    listeCmd->tete=NULL;
    listeCmd->queue=NULL;
}

Noeud* creerNoeud(Noeud* next, LigCmd* ligCmd){
    Noeud* noeud=malloc(sizeof(Noeud));
    noeud->suivant = next ;
    noeud->ligCmd = ligCmd;
    return noeud;
}

void chercherligCmd(ListeCmd *listeCmd ,int numCmd, Noeud* courant_precedent[2] ){
    courant_precedent[0]=NULL;             //le precedent
    courant_precedent[1]=listeCmd->tete;   //le courant
    while(  courant_precedent[1]!=NULL &&(courant_precedent[1]->ligCmd->numCmd !=numCmd )  )
        {   courant_precedent[0]=courant_precedent[1];
            courant_precedent[1]=courant_precedent[1]->suivant;
        }
}

void ajouterLigCmd(ListeCmd* listeCmd, LigCmd* ligCmd){

    Noeud *courant=listeCmd->tete, *precedent=NULL ,*nouveau ;
    //cherchernnoeud(ligCmd , noeud, precedent);
     while(courant!=NULL  && (courant->ligCmd->numCmd != ligCmd->numCmd )  )
        {   precedent=courant;
            courant=courant->suivant;
        }

    nouveau=creerNoeud(courant, ligCmd);

    if(precedent==NULL)  //au debut
        {  listeCmd->tete=nouveau;}
    else {
        if(precedent!=NULL && courant->suivant!=NULL ) //au milieu
        {   precedent->suivant=nouveau;}
        else //au fin
        {   listeCmd->queue->suivant=nouveau;}
        }
    listeCmd->taille++;
}

void afficherCmd(ListeCmd* listeCmd, int numCmd){
    Noeud *courant_precedent[2], *courant;
    chercherligCmd(listeCmd, numCmd, courant_precedent);
    courant=courant_precedent[1];
    while(courant->ligCmd->numCmd ==numCmd )
    {
        afficherLigCmd(courant->ligCmd);
        if(courant->ligCmd->numCmd !=numCmd)
            break;
        courant=courant->suivant;
    }
    afficherLigCmd(courant->ligCmd);
    printf(">>Total : %.2f \n", courant->ligCmd->prixArt * courant->ligCmd->qteArt );
}


int supprimerCmd(ListeCmd* listeCmd, int numCmd){
    Noeud *courant_precedent[2];
    chercherligCmd(listeCmd,numCmd,courant_precedent);
    while(courant_precedent[1]->ligCmd->numCmd ==numCmd )
    {
        if(courant_precedent[1]==listeCmd->tete)//suppression au début
{
        listeCmd->tete=listeCmd->tete->suivant;
    }
    else{
        if(courant_precedent[1]==listeCmd->queue){//au fin
            listeCmd->queue=courant_precedent[0];
        }
        else{ //au millieu
            courant_precedent[0]->suivant=courant_precedent[1]->suivant;
        }}
    if(courant_precedent[1]->ligCmd->numCmd !=numCmd)
            break;
    courant_precedent[0]=courant_precedent[1];
    courant_precedent[1]=courant_precedent[1]->suivant;

    free(courant_precedent[1]);
    listeCmd->taille--;
    }

}


