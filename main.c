#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "commande.h"

/*************************************************************** */
int menu(void)
{
    int choix;
    system("cls");
    printf("\t\t\t\tGESTION DES COMMANDES\n\n");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("Taper le numero de l operation a effectuer :\n");
    printf("----------------------------------------------------------------------------------------------\n\n");

    printf("0- Quiter\n");
    printf("-------------------------------------------------------\n");
    printf("1- Consulter les produits\n");
    printf("2- Consulter les produits en rupture de stock\n");
    printf("3- Consulter une commande par son numero\n");
    printf("-------------------------------------------------------\n");
    printf("4- Chercher un produit (soit par nom, reference)\n");
    printf("5- Chercher les produits d une categorie bien determinee\n");
    printf("6- Chercher les produits d une marque bien determinee\n");
    printf("-------------------------------------------------------\n");
    printf("7- Ajouter un produit\n");
    printf("8- Ajouter une commande\n");
    printf("-------------------------------------------------------\n");
    printf("9- Supprimer un produit\n");
    printf("10- Supprimer une commande\n");
    printf("-------------------------------------------------------\n\n");
    printf("\t>Votre choix : ");
    scanf("%d", &choix);
    system("cls");
    return choix;
}
int main()
{
    ListeCommandes* listeCommandes=NULL;
    ListeLigneCommande *listeLigneCommande=NULL;
    ListeProduits *listeProduits=NULL;

    charger_les_donnees(&listeCommandes,&listeLigneCommande,&listeProduits);
    //system("pause");
    int choix;

    char nom[20], reference[10], categorie[20],marque[20];
    int i,numero;

    Element2* courant=NULL;


    Produit *produit;
    LigneCommande *ligneCommande;
    Commande *commande;
    do
    {
        choix = menu();
        switch(choix)
        {
        case 1 :
            if(listeProduits!=NULL)
            {
                courant=listeProduits->element;
                while(courant!=NULL)
                {
                    AfficherProduit(courant->produit);
                    courant=courant->suivant;
                }
            }
            system("pause");
            break;
        case 2 :
            AfficherProduitsEnRepture(listeProduits);
            system("pause");
            break;
        case 3 :
            printf("\n numero :"); scanf("%d",&numero);
            AfficherCommandeParNumero(listeCommandes,numero);
            system("pause");
            break;
        case 4 :
            printf("\n chercher par nom(1) ou reference(autre nombre): ");
            scanf("%d",&i);
            if(i==1) //nom
            {
                printf("\n nom :"); scanf("%s",nom);
                produit=CherecherProduitParNom(listeProduits, nom);
            }
            else //reference
            {
                printf("\n reference :"); scanf("%s",reference);
                produit=CherecherProduitParReference(listeProduits,reference);
            }
            if(produit!=NULL)
                AfficherProduit(produit);
            else
                printf("produit n existe pas");
            system("pause");
            break;
        case 5 :
            printf("\n categorie :"); scanf("%s",categorie);
            produit=CherecherProduitParCategorie(listeProduits, categorie);
            if(produit!=NULL)
                AfficherProduit(produit);
            else
                printf("produit n existe pas");
            system("pause");
            break;
        case 6 :
            printf("\n marque :"); scanf("%s",marque);
            produit=CherecherProduitParMarque(listeProduits, marque);
            if(produit!=NULL)
                AfficherProduit(produit);
            else
                printf("produit n existe pas");
            system("pause");
            break;
        case 7 :
            produit=SaisirProduit();
            listeProduits= AjouterProduit(listeProduits,produit);
            system("pause");
            break;
        case 8 :
            commande=SaisirCommande(listeLigneCommande, listeProduits);
            listeCommandes=AjouterCommande(listeCommandes,commande);
            system("pause");
            break;
        case 9 :
            printf("\n reference :"); scanf("%s",reference);
            i=SupprimerProduit_ListeProduits(listeProduits,reference);
            if(i==1)
                printf("\n produit supprimee !");
            else
                printf("\n produit pas trouvee !");
            system("pause");
            break;
        case 10 :
            printf("\n numero :"); scanf("%d",&numero);
            i=SupprimerCommande(listeCommandes, numero);
            if(i==1)
                printf("\n commande supprimee !");
            else
                printf("\n commande pas trouvee !");
            system("pause");
            break;
        }
    }while(choix!=0);
    sauvegarder_les_donnees(listeCommandes,listeLigneCommande,listeProduits);
    return 0;
}
