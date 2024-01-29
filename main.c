#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structure pour représenter un employé
typedef struct Employe
{
    int code;
    char nom[50];
    char prenom[50];
    char date_naissance[20];
    char titre_poste[20];
    float salaire;
    struct Employe* next;
} Employe;

// Structure pour représenter la liste d'employés
typedef struct
{
    Employe* head;
} ListeEmployes;

// Fonction pour initialiser la liste d'employés
void initListe(ListeEmployes *liste)
{
    liste->head = NULL;
}

// Fonction pour charger les employés depuis un fichier
void chargerEmployes(ListeEmployes *liste)
{
    FILE *fichier = fopen("employees.txt", "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    while (!feof(fichier))
    {
        Employe* newEmploye = malloc(sizeof(Employe));

        if (fscanf(fichier, "%d %s %s %s %s %f",
                   &newEmploye->code,
                   newEmploye->nom,
                   newEmploye->prenom,
                   newEmploye->date_naissance,
                   newEmploye->titre_poste,
                   &newEmploye->salaire) == 6)
        {

            newEmploye->next = NULL;
            if (liste->head == NULL)
            {
                liste->head = newEmploye;
            }
            else
            {
                Employe *it = liste->head;
                while (it->next != NULL)
                {
                    it = it->next;
                }
                it->next = newEmploye;
            }
        }
        else
        {
            free(newEmploye);
        }
    }

    fclose(fichier);
}


//3-a Fonction pour ajouter un employé à la liste
void ajouterEmploye(ListeEmployes *liste)
{
    Employe* newEmploye = malloc(sizeof(Employe));

    // Demander à l'utilisateur de saisir les informations de l'employé
    printf("Code : ");
    scanf("%d", &newEmploye->code);
    printf("Nom : ");
    scanf("%s", newEmploye->nom);
    printf("Prenom : ");
    scanf("%s", newEmploye->prenom);
    printf("Date de naissance : ");
    scanf("%s", newEmploye->date_naissance);
    printf("Titre de poste : ");
    scanf("%s", newEmploye->titre_poste);
    printf("Salaire : ");
    scanf("%f", &newEmploye->salaire);

    newEmploye->next = liste->head;
    liste->head = newEmploye;
}

//3-b Fonction pour supprimer un employe

void supprimerEmploye(ListeEmployes *liste)
{
    int code;
    printf("Entrez le code de l'employe a supprimer : ");
    scanf("%d", &code);

    Employe *precedent = NULL;
    Employe *courant = liste->head;

    while (courant != NULL && courant->code != code)
    {
        precedent = courant;
        courant = courant->next;
    }

    if (courant == NULL)
    {
        printf("Aucun employe avec ce code n'a ete trouve.\n");
        return;
    }

    printf("Etes-vous sur de vouloir supprimer %s %s ? (O/N) : ", courant->prenom, courant->nom);
    char choix;
    scanf(" %c", &choix);

    if (choix == 'O' || choix == 'o')
    {
        if (precedent == NULL)
        {
            liste->head = courant->next;
        }
        else
        {
            precedent->next = courant->next;
        }
        free(courant);
        printf("Employe supprime avec succes.\n");
    }
    else
    {
        printf("Suppression annulee.\n");
    }
}

// 3-c Fonction pour Rechercher un employe:
void rechercherEmploye(ListeEmployes *liste)
{
    int choix;
    int code; // Déclaration de la variable code
    char nomRecherche[50]; // Déclaration de la variable nomRecherche
    char prenomRecherche[50]; // Déclaration de la variable prenomRecherche

    printf("1. Rechercher par code\n");
    printf("2. Rechercher par nom\n");
    printf("3. Rechercher par prenom\n");
    printf("Choix : ");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        // Recherche par code
        printf("Entrez le code de l'employe : ");
        scanf("%d", &code);

        Employe *courant = liste->head;
        while (courant != NULL)
        {
            if (courant->code == code)
            {
                printf("Code : %d\n", courant->code);
                printf("Nom : %s\n", courant->nom);
                printf("Prenom : %s\n", courant->prenom);
                printf("Date de naissance : %s\n", courant->date_naissance);
                printf("Titre de poste : %s\n", courant->titre_poste);
                printf("Salaire : %.2f\n", courant->salaire);
                return;
            }
            courant = courant->next;
        }
        printf("Aucun employe avec ce code n'a ete trouve.\n");
        break;

    case 2:
        // Recherche par nom
        printf("Entrez le nom de l'employe : ");
        scanf("%s", nomRecherche);

        courant = liste->head;
        int countNom = 0;
        while (courant != NULL)
        {
            if (strcmp(courant->nom, nomRecherche) == 0)
            {
                printf("Code : %d\n", courant->code);
                printf("Nom : %s\n", courant->nom);
                printf("Prenom : %s\n", courant->prenom);
                printf("Date de naissance : %s\n", courant->date_naissance);
                printf("Titre de poste : %s\n", courant->titre_poste);
                printf("Salaire : %.2f\n", courant->salaire);
                countNom++;
            }
            courant = courant->next;
        }
        if (countNom == 0)
        {
            printf("Aucun employe avec ce nom n'a ete trouve.\n");
        }
        else
        {
            printf("Nombre total d'employes correspondants : %d\n", countNom);
        }
        break;

    case 3:
        // Recherche par prenom
        printf("Entrez le prenom de l'employe : ");
        scanf("%s", prenomRecherche);

        courant = liste->head;
        int countPrenom = 0;
        while (courant != NULL)
        {
            if (strcmp(courant->prenom, prenomRecherche) == 0)
            {
                printf("Code : %d\n", courant->code);
                printf("Nom : %s\n", courant->nom);
                printf("Prenom : %s\n", courant->prenom);
                printf("Date de naissance : %s\n", courant->date_naissance);
                printf("Titre de poste : %s\n", courant->titre_poste);
                printf("Salaire : %.2f\n", courant->salaire);
                countPrenom++;
            }
            courant = courant->next;
        }
        if (countPrenom == 0)
        {
            printf("Aucun employe avec ce prenom n'a ete trouve.\n");
        }
        else
        {
            printf("Nombre total d'employes correspondants : %d\n", countPrenom);
        }
        break;

    default:
        printf("Choix invalide. Veuillez reessayer.\n");
    }
}



//3-d Fonction pour mettre  à jour les informations des employés

// Fonction pour valider le titre de poste saisi par l'utilisateur
int validerTitrePoste(const char *titre)
{
    if (strcmp(titre, "President") == 0 || strcmp(titre, "VP-Sales") == 0 || strcmp(titre, "VP-Marketing") == 0 || strcmp(titre, "Sales-Manager") == 0 || strcmp(titre, "Sales-Rep") == 0)
    {
        return 1; // titre de poste est valide
    }
    else
    {
        return 0; // titre de poste est invalide
    }
}


void mettreAJourEmploye(ListeEmployes *liste)
{
    int code;
    printf("Entrez le code de l'employe a mettre a jour : ");
    scanf("%d", &code);

    Employe *courant = liste->head;
    while (courant != NULL)
    {
        if (courant->code == code)
        {
            printf("Employe trouve.\n");

            // Afficher les informations actuelles de l'employé
            printf("Informations actuelles de l'employe :\n");
            printf("Nom : %s\n", courant->nom);
            printf("Prenom : %s\n", courant->prenom);
            printf("Titre de poste actuel : %s\n", courant->titre_poste);
            printf("Salaire actuel : %.2f\n", courant->salaire);

            // Demander à l'utilisateur de saisir les nouvelles informations
            char nouveauTitrePoste[50];
            do
            {
                printf("Veuillez choisir un nouveau titre de poste parmi les options suivantes : (President, VP-Sales, VP-Marketing, Sales-Manager, Sales-Rep): ");
                scanf("%s", nouveauTitrePoste);
            }
            while (!validerTitrePoste(nouveauTitrePoste));

            printf("Nouveau salaire : ");
            scanf("%f", &courant->salaire);

            printf("Informations mises a jour avec succes.\n");
            return;
        }
        courant = courant->next;
    }

    // Si aucun employé avec le code spécifié n'est trouvé
    printf("Aucun employe avec ce code n'a ete trouve.\n");
}


// 3-e  Fonction pour sauvegarder les employés dans un fichier
void sauvegarderEmployes(ListeEmployes *liste)
{
    FILE *fichier = fopen("employees.txt", "w");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    Employe *it = liste->head;
    while (it != NULL)
    {
        fprintf(fichier, "%d %s %s %s %s %.2f\n",
                it->code,
                it->nom,
                it->prenom,
                it->date_naissance,
                it->titre_poste,
                it->salaire);

        it = it->next;
    }

    fclose(fichier);
}

// Fonction pour libérer la mémoire allouée pour la liste d'employés
void libererMemoire(ListeEmployes *liste)
{
    Employe *it = liste->head;
    while (it != NULL)
    {
        Employe *temp = it;
        it = it->next;
        free(temp);
    }
    liste->head = NULL; // N'oubliez pas de mettre la tête de la liste à NULL après avoir libéré la mémoire
}



int main()
{
    ListeEmployes liste;
    initListe(&liste);
    chargerEmployes(&liste);

    int choix;
    do
    {
        // Afficher le menu
        printf("\nMenu :\n");
        printf("1. Ajouter un employe\n");
        printf("2. Supprimer un employe\n");
        printf("3. Rechercher un employe\n");
        printf("4. Mettre a jour les informations d'un employe\n");
        printf("5. Sauvegarder dans le fichier employees.txt\n");
        printf("6. Quitter le programme\n");

        // Lire le choix de l'utilisateur
        printf("Choix : ");
        scanf("%d", &choix);

        // Traiter le choix de l'utilisateur
        switch (choix)
        {
        case 1:
            ajouterEmploye(&liste);
            break;
        case 2:
            supprimerEmploye(&liste);
            break;

        case 3:
            rechercherEmploye(&liste);
            break;
        case 4:
            mettreAJourEmploye(&liste);
            break;

        case 5:
            sauvegarderEmployes(&liste);
            break;
        case 6:
            sauvegarderEmployes(&liste);
            printf("Programme termine.\n");
            break;
        default:
            printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
    while (choix != 6);

    libererMemoire(&liste);

    return 0;
}


