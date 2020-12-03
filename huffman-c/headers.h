#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

void dec_to_bin(char* nomfich_1, char* nomfich_2);
void afficher_nbr_char(char* nomfichier);

typedef struct Element
{
    int letter;
    int occur;
    struct Element* next;
} Element;

Element* creer_liste(int ascii);
void free_liste(Element** l);
Element* creer_liste_lettres(char* nomfich);

typedef struct Arbre{
    Element* elem;
    struct Arbre* sag;
    struct Arbre* sad;
}Arbre;

Element* plus_petit_occur(Element** l);
int occur_element(Element* l);

Arbre* creer_tree_Huffman(Element** l, int n);
int nbr_elem_inlist(Element *l);

void afficher_arbre(Arbre* a);

#endif // HEADERS_H_INCLUDED
