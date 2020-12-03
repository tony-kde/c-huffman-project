#include <stdio.h>
#include <stdlib.h>

/** Question A **/
void dec_to_bin(char* nomfich_1, char* nomfich_2){
    FILE *fich1 = NULL, *fich2 = NULL;
    fich1 = fopen(nomfich_1, "r");
    fich2 = fopen(nomfich_2, "w");

    if(fich1 != NULL && fich2 != NULL){

        int lettre, val[8], i;
        while((lettre = fgetc(fich1)) != EOF){
            //Remplir le tableau de 0

            for(i=0;i<8;i++)
                val[i]=0;
            for(i=7; lettre>0; i--){
                val[i]= lettre%2;
                lettre/=2;
            }
            for(i=0; i<8; i++){
                if(val[i] == 0)
                    fputc('0', fich2);
                else
                    fputc('1', fich2);
            }

        }
        fclose(fich1);
        fclose(fich2);
    }
    else
        printf("ERREUR d'ouverture du fichier d'ecriture");
}

/** Question B **/
void afficher_nbr_char(char* nomfichier){
    FILE* fich = NULL;
    fich = fopen(nomfichier, "r");
    if(fich != NULL){
        int cpt=0, n;
        while( (n = fgetc(fich)) != EOF){
            cpt++;
        }
        printf("Il y a %d caracteres dans le fichier\n", cpt);
        fclose(fich);
    }
    else
        printf("ERREUR");
}

/** Question C **/

Element* creer_liste(int ascii){
    if(ascii == EOF)
        return NULL;
    else{
        Element* l = malloc(sizeof(Element));
        l->letter = ascii;
        l->occur = 1;
        l->next = NULL;
        return l;
    }
}


void free_liste(Element** l){
    Element** temp = &(*l);
    while(*l != NULL){
        l = &((*l)->next);
        free(*temp);
        temp = &(*l);
    }
}


Element* creer_liste_lettres(char* nomfich){
    FILE *fich = NULL;
    Element* l = NULL, *temp = NULL;
    int str;
    fich = fopen(nomfich, "r");

    if(fich != NULL){
        l = creer_liste(fgetc(fich));       //Creer 1er élément séparement des autres
        while((str = fgetc(fich)) != EOF){
            if(str != '\n'){                //On ne comptabilise pas retour à la ligne comme un caratère
                temp = l;
                while( ((temp->next) != NULL) && (str != (temp->letter)) )
                    temp = temp->next;
                if(str == temp->letter)
                    (temp->occur)++;
                else
                    temp->next = creer_liste(str);
            }
        }
    }
    return l;
}

/** Question D **/

Element* plus_petit_occur(Element** l){
    if((*l) == NULL)
        return NULL;
    else if( (*l)->occur == 1 ){
        Element* temp = *l;
        *l = (*l)->next;
        temp->next = NULL;
        return temp;
    }
    else{
        Element* temp = (*l)->next, *prec = *l;
        int min = (*l)->occur;
        while(min != 1 && temp != NULL){
            if( temp->occur < min){
                min = temp->occur;
                //Avec prec on garde le noeud précédent l'élément minimum
                //Pour pouvoir le mettre au début de la liste après
                while(prec->next != temp)
                    prec = prec->next;
            }
            temp = temp->next;
        }
        temp = prec->next;
        prec->next = temp->next;
        temp->next = NULL;
        return temp;
    }
}

// Récupère l'occurrence d'un element

int occur_element(Element* l){
    if(l == NULL)
        return 0;
    else{
        int n=l->occur;
        printf("N=%d",n);
        return n;
    }
}

int nbr_elem_inlist(Element *l){
    int n=0;
    while(l != NULL){
        n++;
        l = l->next;
    }
    return n;
}

Arbre* creer_tree_Huffman(Element** l, int n){
    Arbre* a = malloc(sizeof(Arbre));
    if(n == 1){
        a->sad = NULL;
        a->sag = NULL;
        a->elem = plus_petit_occur(l);
        return a;
    }
    else{
        a->sad = creer_tree_Huffman(l, n-1);
        a->elem = malloc(sizeof(Element));
        a->sag->elem = plus_petit_occur(l);
        printf("ZAKKKK");
        a->elem->occur = occur_element(a->sag->elem) + occur_element(a->sad->elem);
        printf("\nICIII ZOB\n");
        a->elem->letter = 32;
        return a;
    }
}

void afficher_arbre(Arbre* a){
    if( a != NULL){
        printf("Lettre :%c | Occur :%d\n", a->elem->letter, a->elem->occur);
        afficher_arbre(a->sag);
        afficher_arbre(a->sad);
    }
}

