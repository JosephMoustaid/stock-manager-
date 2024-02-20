#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commande.h"

//-----------------------------------------------------------------------
Produit* SaisirProduit(void)
{
    Produit *produit=malloc(sizeof(Produit));
    if(produit==NULL) exit(EXIT_FAILURE);
    fflush(stdin);
    printf(" nom :"); scanf("%s",produit->nom);
    printf(" refereence :"); scanf("%s",produit->refereence);
    fflush(stdin);
    printf(" categorie :"); scanf("%s",produit->categorie);
    printf(" marque :"); scanf("%s",produit->marque);
    printf(" quantitee en stock :"); scanf("%d",&(produit->quantite_stock));
    return produit;
}
//-----------------------------------------------------------------------
LigneCommande* SaisirLigneCommande(Produit *produit)
{
    LigneCommande* ligneCommande=malloc(sizeof(LigneCommande));
    if(ligneCommande==NULL) exit(EXIT_FAILURE);
    ligneCommande->produit=produit;
    printf("\n quantite achetee :"); scanf("%d",&(ligneCommande->quantite_achetee) );
    return ligneCommande;
}
//-----------------------------------------------------------------------
Commande* SaisirCommande(ListeLigneCommande* listeLigneCommande, ListeProduits* listeProduits)
{
    char ref[10];
    int ajouter=1, quantite_achetee;
    LigneCommande* ligneCommande;
    Commande* commande=malloc(sizeof(Commande));
    if(commande==NULL) exit(EXIT_FAILURE);
    commande->listeLigneCommande= listeLigneCommande;
    fflush(stdin);
    printf("\n nom de client :"); scanf("%s",commande->nom_client);
    printf("\n date (jj mm aaaa) :"); scanf("%d %d %d",&(commande->date.jour), &(commande->date.mois), &(commande->date.annee));
    printf("\n numero :"); scanf("%d",&(commande->numero));
    printf("\n montant HT :"); scanf("%f",&(commande->montant_HT));
    printf("\n montant TVA :"); scanf("%f",&(commande->montant_TVA));
    commande->montant_TTC=commande->montant_HT-commande->montant_TVA;
    commande->listeLigneCommande=NULL;
    while(ajouter)
    {
        printf("\n Ajouter une ligneCommande(1-oui 0-non) :"); scanf("%d",&ajouter);
        if(ajouter!=1)
             break;
        ligneCommande=malloc(sizeof(LigneCommande));
        printf("\n referemce :"); scanf("%s",ref);
        ligneCommande->produit=CherecherProduitParReference(listeProduits, ref);
        printf("\n quantite achetee:"); scanf("%d",&(ligneCommande->quantite_achetee));
        commande->listeLigneCommande= AjouterLigneCommande(commande->listeLigneCommande, ligneCommande);
        listeLigneCommande= AjouterLigneCommande(listeLigneCommande, ligneCommande);
    }
    return commande;
}
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
Produit* CherecherProduitParNom(ListeProduits* listeProduits , char* nom)
{
    Element2 *courant=NULL;
    if(listeProduits!=NULL)
        courant=listeProduits->element;
    if(courant==NULL) return NULL;
    while(courant!=NULL && strcmp(courant->produit->nom,nom)!=0)
    {
        courant=courant->suivant;
    }
    if(courant==NULL) return NULL;
    return courant->produit;
}
//-----------------------------------------------------------------------
Produit* CherecherProduitParReference(ListeProduits* listeProduits , char* refeerence)
{
    Element2 *courant=NULL;
    if(listeProduits!=NULL)
        courant=listeProduits->element;
    if(courant==NULL) return NULL;
    while(courant!=NULL && strcmp(courant->produit->refereence,refeerence)!=0)
    {
        courant=courant->suivant;
    }
    if(courant==NULL) return NULL;
    return courant->produit;
}
//-----------------------------------------------------------------------
Produit* CherecherProduitParCategorie(ListeProduits* listeProduits , char* categorie)
{
    Element2 *courant=NULL;
    if(listeProduits!=NULL)
        courant=listeProduits->element;
    if(courant==NULL) return NULL;
    while(courant!=NULL && strcmp(courant->produit->categorie,categorie)!=0)
    {
        courant=courant->suivant;
    }
    if(courant==NULL) return NULL;
    return courant->produit;
}
//-----------------------------------------------------------------------
Produit* CherecherProduitParMarque(ListeProduits* listeProduits , char* marque)
{
    Element2 *courant=NULL;
    if(listeProduits!=NULL)
        courant=listeProduits->element;
    if(courant==NULL) return NULL;
    while(courant!=NULL && strcmp(courant->produit->marque,marque)!=0)
    {
        courant=courant->suivant;
    }
    if(courant==NULL) return NULL;
    return courant->produit;
}
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
ListeProduits* AjouterProduit(ListeProduits* listeProduits , Produit *produit)
{
    Element2* courant=NULL, *nouveau=malloc(sizeof(Element2));
    if(listeProduits!=NULL)
        courant=listeProduits->element;
    if(nouveau==NULL)exit(EXIT_FAILURE);
    nouveau->produit=produit;

    if(courant==NULL)//liste vide
    {
        listeProduits=malloc(sizeof(ListeProduits));
        listeProduits->element=nouveau;
        nouveau->suivant=nouveau->precedent=NULL;
    }
    else
    {
        while(courant->suivant!=NULL)
        {
            courant=courant->suivant;
        }
        nouveau->suivant=NULL;
        nouveau->precedent=courant;
        courant->suivant=nouveau;
    }
    return listeProduits;
}
//-----------------------------------------------------------------------
ListeLigneCommande* AjouterLigneCommande(ListeLigneCommande*  listeLigneCommande, LigneCommande* ligneCommande)
{
    Element* courant=NULL, *nouveau=malloc(sizeof(Element));
    if(listeLigneCommande!=NULL)
        courant=listeLigneCommande->element;
    if(nouveau==NULL)exit(EXIT_FAILURE);
    nouveau->ligneCommande =ligneCommande;

    if(courant==NULL)//liste vide
    {
        listeLigneCommande=malloc(sizeof(ListeLigneCommande));
        listeLigneCommande->element=nouveau;
        nouveau->suivant=nouveau->precedent=NULL;
    }
    else
    {
        while(courant->suivant!=NULL)
        {
            courant=courant->suivant;
        }
        nouveau->suivant=NULL;
        nouveau->precedent=courant;
        courant->suivant=nouveau;
    }
    return listeLigneCommande;
}
//-----------------------------------------------------------------------
ListeCommandes* AjouterCommande(ListeCommandes* listeCommandes, Commande* commande)
{
    Element3* courant=NULL, *nouveau=malloc(sizeof(Element3));
    if(listeCommandes!=NULL)
        courant=listeCommandes->element;
    if(nouveau==NULL)exit(EXIT_FAILURE);

    nouveau->commande=commande;
    if(courant==NULL)//liste vide
    {
        listeCommandes=malloc(sizeof(ListeCommandes));
        listeCommandes->element=nouveau;
        nouveau->suivant=nouveau->precedent=NULL;
    }
    else
    {
        while(courant->suivant!=NULL)
        {
            courant=courant->suivant;
        }
        nouveau->suivant=NULL;
        nouveau->precedent=courant;
        courant->suivant=nouveau;
    }
    return listeCommandes;
}
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
int SupprimerProduit_ListeProduits(ListeProduits* listeProduits,char* refeerence)
{
    Element2* courant=NULL, *precedent=NULL;
    if(listeProduits!=NULL) courant=listeProduits->element;
    if(courant==NULL)  // rien a supprimer
        return 0;
    while(courant!=NULL && strcmp(courant->produit->refereence, refeerence)!=0)
    {
        precedent=courant;
        courant=courant->suivant;
    }
    if(courant==NULL) return 0;  //pas trouvé

    if(precedent==NULL && courant->suivant==NULL)//un seule element
        listeProduits->element=NULL;
    else
    {
        if(precedent==NULL) //debut
        {
            (courant->suivant)->precedent=NULL;
            listeProduits->element=courant->suivant;
        }
        else
        {
            if(courant->suivant==NULL) //fin
            {
                (courant->precedent)->suivant=NULL;
            }
            else //milieu
            {
                precedent->suivant=courant->suivant;
                (courant->suivant)->precedent=precedent;
            }
        }
    }
    free(courant);
    return 1;
}
//-----------------------------------------------------------------------
int SupprimerProduit_listeLigneCommande(ListeLigneCommande* listeLigneCommande,char* refeerence)
{
    Element* courant=NULL , *precedent=NULL;
    if(listeLigneCommande!=NULL) courant=listeLigneCommande->element;
    if(courant==NULL)  // rien a supprimer
        return 0;
    while(courant!=NULL && strcmp(courant->ligneCommande->produit->refereence, refeerence)!=0)
    {
        precedent=courant;
        courant=courant->suivant;
    }
    if(courant==NULL) return 0;  //pas trouvé

    if(precedent==NULL && courant->suivant==NULL)//un seule element
        listeLigneCommande->element=NULL;
    else
    {
        if(precedent==NULL) //debut
        {
            (courant->suivant)->precedent=NULL;
            listeLigneCommande->element=courant->suivant;
        }
        else
        {
            if(courant->suivant==NULL) //fin
            {
                (courant->precedent)->suivant=NULL;
            }
            else //milieu
            {
                 precedent->suivant=courant->suivant;
                (courant->suivant)->precedent=precedent;
            }
        }
    }
    free(courant);
    return 1;
}
//-----------------------------------------------------------------------
int SupprimerCommande(ListeCommandes* listeCommandes, int numero)
{
    Element3* courant=NULL, *precedent=NULL;
    if(listeCommandes!=NULL) courant=listeCommandes->element;
    if(courant==NULL)  // rien a supprimer
        return 0;
    while(courant!=NULL && numero!=courant->commande->numero)
    {
        precedent=courant;
        courant=courant->suivant;
    }
    if(courant==NULL) return 0;  //pas trouvé

    if(precedent==NULL && courant->suivant==NULL)//un seule element
        listeCommandes->element=NULL;
    else
    {
       if(precedent==NULL) //debut
        {
            (courant->suivant)->precedent=NULL;
            listeCommandes->element=courant->suivant;
        }
        else
        {
            if(courant->suivant==NULL) //fin
            {
                (courant->precedent)->suivant=NULL;
            }
            else //milieu
            {
                precedent->suivant=courant->suivant;
                (courant->suivant)->precedent=precedent;
            }
        }
    }

    free(courant);
    return 1;
}
//-----------------------------------------------------------------------



//-----------------------------------------------------------------------
void AfficherProduit(Produit *produit)
{
    printf("\n \t %s |\t %s |\t %s |\t %s |\t %d \n",produit->nom,produit->categorie,produit->refereence,produit->marque, produit->quantite_stock);
}
//-----------------------------------------------------------------------
void AfficherCommande(Commande* commande)
{
    Element* courant=NULL;
    if(commande==NULL) return;
    printf("\n numero : %d",commande->numero);
    printf("\n date : %d / %d / %d",commande->date.jour,commande->date.mois,commande->date.annee);
    printf("\n nom de client : %s",commande->nom_client);
    printf("\n montant HT : %g",commande->montant_HT);
    printf("\n montant TVA : %g",commande->montant_TVA);
    printf("\n montant TTC : %g",commande->montant_TTC);
    if(commande->listeLigneCommande!=NULL)
    {
        courant=commande->listeLigneCommande->element;
        while(courant!=NULL)
        {
            printf("\n quantite achetee : %d",courant->ligneCommande->quantite_achetee);
            AfficherProduit(courant->ligneCommande->produit);
            courant=courant->suivant;
        }
    }


}
//-----------------------------------------------------------------------
void AfficherProduitsEnRepture(ListeProduits* listeProduits)
{

    Element2* courant=NULL;
    if(listeProduits!=NULL)
        courant=listeProduits->element;
    while(courant!=NULL)
    {
        if(courant->produit->quantite_stock < 10)
        {
            AfficherProduit(courant->produit);
        }
        courant=courant->suivant;
    }
}
//-----------------------------------------------------------------------
void AfficherCommandeParNumero(ListeCommandes* listeCommandes,int numero)
{
    Element3* courant=NULL;
    if(listeCommandes!=NULL)
    courant=listeCommandes->element;
    while(courant!=NULL)
    {
        if(courant->commande->numero==numero)
        {
            AfficherCommande(courant->commande);
            break;
        }
        else{
            courant=courant->suivant;
            }
    }
}
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
void charger_les_donnees(ListeCommandes** listeCommandes,ListeLigneCommande** listeLigneCommande,ListeProduits** listeProduits)
{
    int values_read=1, lignesread=1, numero_commande;

    FILE *f_Commandes=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\Commandes.txt","r");
    FILE *f_LignesCommandes=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\LignesCommandes.txt","r");
    FILE *f_Produits=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\Produits.txt","r");

    char empty_line[100];

    Produit* produit=NULL;
    LigneCommande* ligneCommande=NULL;
    Commande* commande=NULL;
    Element3* courant=NULL;

    if (f_Produits == NULL || f_LignesCommandes == NULL || f_Commandes == NULL) {
        printf("Erreur lors de l'ouverture d'un des fichiers :\n");
        if(f_Produits == NULL) printf("Produits.txt \n");
        if(f_LignesCommandes == NULL) printf("LignesCommandes.txt \n");
        if(f_Commandes == NULL) printf("Commandes.txt \n");
        return;
    }

    //chargement de la listeProduits
    while(1) {
        produit = malloc(sizeof(Produit));
        values_read = fscanf(f_Produits, "%d \t %s \t %s \t %s \t %s \n", &(produit->quantite_stock), produit->nom, produit->refereence, produit->categorie, produit->marque);
        if (values_read != 5) {
            free(produit);
            break;
        }
        *listeProduits = AjouterProduit(*listeProduits, produit);
    }

    // Chargement de la listeCommandes
    while(1)
        {
        commande = malloc(sizeof(Commande));
        commande->listeLigneCommande=NULL;
        values_read = fscanf(f_Commandes, "%d \t %d \t %d \t %d \t %s \t %f \t %f \t %f\n", &(commande->numero), &(commande->date.jour), &(commande->date.mois), &(commande->date.annee), commande->nom_client, &(commande->montant_HT), &(commande->montant_TVA), &(commande->montant_TTC));
        if (values_read != 8) {
            free(commande);
            break;
        }
        *listeCommandes = AjouterCommande(*listeCommandes,commande);

        }

    // Chargement de la listeLignesCommandes

    while(1) {
        ligneCommande = malloc(sizeof(LigneCommande));
        ligneCommande->produit = malloc(sizeof(Produit));
        values_read = fscanf(f_LignesCommandes, "%d \t %d \t %s \t %s \t %s \t %s \t %d\n",&numero_commande, &(ligneCommande->produit->quantite_stock), ligneCommande->produit->nom, ligneCommande->produit->refereence, ligneCommande->produit->categorie, ligneCommande->produit->marque, &(ligneCommande->quantite_achetee));
        if (values_read != 7) {
            free(ligneCommande->produit);
            free(ligneCommande);
            break;
        }
        *listeLigneCommande = AjouterLigneCommande(*listeLigneCommande, ligneCommande);

        if(*listeCommandes!=NULL)
        {
            courant=(*listeCommandes)->element;
            while(courant->suivant!=NULL)
            {
                if(courant->commande->numero==numero_commande)
                {
                    courant->commande->listeLigneCommande=AjouterLigneCommande(courant->commande->listeLigneCommande,ligneCommande);
                }
                courant=courant->suivant;
            }
        }
    }
    fclose(f_Commandes);
    fclose(f_LignesCommandes);
    fclose(f_Produits);
}
//-----------------------------------------------------------------------
void sauvegarder_les_donnees(ListeCommandes* listeCommandes,ListeLigneCommande* listeLigneCommande,ListeProduits* listeProduits)
{
    FILE *f_Commandes=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\Commandes.txt", "a");
    FILE *f_LignesCommandes=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\LignesCommandes.txt", "a");
    FILE *f_Produits=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\Produits.txt", "a");

    if (f_Produits == NULL || f_LignesCommandes == NULL || f_Commandes == NULL) {
        printf("Erreur lors de l'ouverture d'un des fichiers :\n");
        if(f_Produits == NULL) printf("Produits.txt \n");
        if(f_LignesCommandes == NULL) printf("LignesCommandes.txt \n");
        if(f_Commandes == NULL) printf("Commandes.txt \n");
        return;
    }
    Element3* courant_commande=NULL;
    Element* courant_ligne_commande=NULL;
    Element2* courant_produit=NULL;

    if(listeCommandes!=NULL) courant_commande=listeCommandes->element;
    if(listeLigneCommande!=NULL) courant_ligne_commande=listeLigneCommande->element;
    if(listeProduits!=NULL) courant_produit=listeProduits->element;

    //ecriture des produits
    if(courant_produit!=NULL)
    {
       f_Produits=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\Produits.txt", "w");
       while(courant_produit!=NULL)
       {
           fprintf(f_Produits,"%d \t %s \t %s \t %s \t %s \n",courant_produit->produit->quantite_stock, courant_produit->produit->nom, courant_produit->produit->refereence, courant_produit->produit->categorie, courant_produit->produit->marque);
           courant_produit=courant_produit->suivant;
           //SupprimerProduit_ListeProduits(listeProduits,courant_produit->precedent->produit->refereence);
       }
       //listeProduits=NULL;
    }

    //ecriture des lignescommandes
    if(courant_commande!=NULL)
    {
            f_Commandes=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\Commandes.txt", "w");
            while(courant_commande!=NULL)
            {
                fprintf(f_Commandes,"%d \t %d \t %d \t %d \t %s \t %.2f \t %.2f \t %.2f \n",courant_commande->commande->numero,courant_commande->commande->date.jour,courant_commande->commande->date.mois,courant_commande->commande->date.annee,courant_commande->commande->nom_client,courant_commande->commande->montant_HT,courant_commande->commande->montant_TVA,courant_commande->commande->montant_TTC);
                if(courant_commande->commande->listeLigneCommande!=NULL)
                {
                    f_LignesCommandes=fopen("C:\\Users\\moustaid\\Documents\\school\\PASD\\projet 2 PASD\\projet 2\\text files\\LignesCommandes.txt", "w");
                    courant_ligne_commande=courant_commande->commande->listeLigneCommande->element;
                    while(courant_ligne_commande!=NULL)
                    {
                        fprintf(f_LignesCommandes,"%d \t %d \t %s \t %s \t %s \t %s \t %d \n",courant_commande->commande->numero,courant_ligne_commande->ligneCommande->produit->quantite_stock,  courant_ligne_commande->ligneCommande->produit->nom,  courant_ligne_commande->ligneCommande->produit->refereence, courant_ligne_commande->ligneCommande->produit->categorie, courant_ligne_commande->ligneCommande->produit->marque , courant_ligne_commande->ligneCommande->quantite_achetee);
                        courant_ligne_commande=courant_ligne_commande->suivant;
                    }
                }
                courant_commande=courant_commande->suivant;
            }
    }
    fclose(f_Produits);
    fclose(f_LignesCommandes);
    fclose(f_Commandes);
}
//-----------------------------------------------------------------------


