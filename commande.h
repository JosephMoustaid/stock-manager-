#ifndef COMMANDE_H_INCLUDED
#define COMMANDE_H_INCLUDED

typedef struct produit{
    int quantite_stock;
    char nom[15] , refereence[15], categorie[15],marque[15];
}Produit;

typedef struct ligneCommande{
    Produit *produit;
    int quantite_achetee;
}LigneCommande;


//ListeLigneCommande-------------------------------------------------
typedef struct element{
    LigneCommande *ligneCommande;
    struct element *suivant, *precedent;
}Element;
typedef struct listeLigneCommande{
    Element *element;
}ListeLigneCommande;
//-------------------------------------------------------------------


typedef struct date{
    int jour, mois ,annee;
}Date;

typedef struct commande{
    int numero;
    Date date;
    char nom_client[20];
    float  montant_HT, montant_TVA, montant_TTC;
    ListeLigneCommande *listeLigneCommande;
}Commande;

//ListeProduits-------------------------------------------------
typedef struct element2{
    Produit *produit;
    struct element2 *suivant, *precedent;
}Element2;
typedef struct listeProduits{
    Element2 *element;
}ListeProduits;
//ListeCommandes-------------------------------------------------
typedef struct element3{
    Commande *commande;
    struct element3 *suivant, *precedent;
}Element3;
typedef struct listeCommandes{
    Element3 *element;
}ListeCommandes;
//----------------------------------------------------------------

Produit* SaisirProduit(void);
LigneCommande* SaisirLigneCommande(Produit * );
Commande* SaisirCommande(ListeLigneCommande* ,ListeProduits*);

Produit* CherecherProduitParNom(ListeProduits*  , char* );
Produit* CherecherProduitParReference(ListeProduits*  , char* );
Produit* CherecherProduitParCategorie(ListeProduits*  , char* );
Produit* CherecherProduitParMarque(ListeProduits*  , char* );

ListeProduits* AjouterProduit(ListeProduits*  , Produit *);
ListeLigneCommande* AjouterLigneCommande(ListeLigneCommande* , LigneCommande* );
ListeCommandes* AjouterCommande(ListeCommandes*  , Commande *);

int SupprimerProduit_ListeProduits(ListeProduits* ,char*); // on retourne 0 si supprimé , 1 sinon
int SupprimerProduit_listeLigneCommande(ListeLigneCommande* ,char*);
int SupprimerCommande(ListeCommandes* , int );

void AfficherProduit(Produit *); // fonction d'aide
void AfficherCommande(Commande*  ); // fonction d'aide
void AfficherProduitsEnRepture(ListeProduits* );
void AfficherCommandeParNumero(ListeCommandes* ,int);

void charger_les_donnees(ListeCommandes**,ListeLigneCommande**,ListeProduits**);
void sauvegarder_les_donnees(ListeCommandes*,ListeLigneCommande*,ListeProduits*);

#endif // COMMANDE_H_INCLUDED
