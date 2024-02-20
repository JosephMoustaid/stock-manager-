#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "commande.h"

/*************************************************************** */
int menu(void)
{
    int choix;
    system("cls");
    printf("\t\tGestion des commandes\n\n");
    printf("0) Fin\n");
    printf("1) Ajouter une ligne de commande\n");
    printf("2) Afficher une commande\n");
    printf("3) Supprimer une commande\n");
    printf("4) Supprimer la liste de commandes\n");
    printf("5) Inverser la liste de commandes\n");
    printf("6) Transformer la liste de commandes en tableau de commandes\n");
    printf("7) Supprimer le tableau de commandes\n\n");
    printf("\t\tVotre choix : ");scanf("%d", &choix);
    system("cls");
    return choix;
}
int main()
{
    int choix;
    LigCmd * ligCmd;
    ListeCmd *listeCmd;
    creerListeCmdVide(listeCmd);
    do
    {
        choix = menu();
        switch(choix)
        {
            case 1 : ajouterLigCmd(listeCmd,creerLigCmd());
                     ajouterLigCmd(listeCmd,creerLigCmd());
                     ajouterLigCmd(listeCmd,creerLigCmd());
                     system("pause");
                     break;
            case 2 :
                     system("pause");
                     break;
            case 3 :
                     break;
            case 4 :
                     break;
            case 5 :
                     break;
            case 6 :
                     break;
            case 7 :
                     break;
        }
    }while(choix!=0);
    return 0;
}
