
// Pislari Vadim 

#include <stdio.h>
#include <stdlib.h>

// complexitate O(1)
void muchia(int s, int d, FILE *out){
    //afisarea unei muchii
    fprintf(out, "x%d-%d",s + 1,d + 1);
}

// complexitate O(1)
void distanta(int s, int d, FILE *out){
    //afisarea a celei mai scurte cai a1 - 2
    fprintf(out, "a%d-%d",s + 1,d + 1);
}

// complexitate O(1)
void muchia_negata(int s, int d, FILE *out){
    //afisarea unei muchii negate
    fprintf(out, "~x%d-%d",s + 1,d + 1);
}

// complexitate O(1)
void distanta_negata(int s, int d, FILE *out){
    //afisarea a celei mai scurte cai a1 - 2 negate
    fprintf(out, "~a%d-%d",s + 1,d + 1);
}

// complexitate < O(n^3)
void legatura_unui_singur_nod( int *arr, int nr_muchii, int sursa, FILE *out){
    int i, j, k;
    if(nr_muchii == 1) return;
    fprintf(out, "(");
    for(i = 1; i < nr_muchii; i++){
        // afisarea a doua muchii care au legatura cu sursa
        // si a restor negate
        for(k = i ; k < nr_muchii; k++){
            fprintf(out, "(");
            muchia(sursa, arr[i - 1], out);
            fprintf(out, "&");
            muchia(sursa, arr[k], out);
            for(j = 0; j < nr_muchii; j++){
                if(j != k  && j != i-1){
                    fprintf(out, "&");
                    muchia_negata(sursa, arr[j], out);
                }
            }
            if(k + 1 == nr_muchii && i+1 == nr_muchii)
                fprintf(out, ")");
            else
                fprintf(out, ")|");
        }
    }
    fprintf(out, ")&");
}

// complexitate  O(n^2)
void legaturi_intre_toate_nodurile(int **arr, int noduri, FILE *out){

    // noduri/2 deoarece se verifica daca se poate ajuge cu distanta minima
    // asa cum e ciclu se poate ajunge din ambele partic
    int i, j, k, fin = noduri / 2  ;
    for(i = 0; i != noduri; i++){
        int *vect = malloc(noduri * sizeof(int)), dim = 0;
        // crearea vectorului cu muchii existente
        for(j = 0; j != noduri; j++)
            if(arr[i][j] == 1)
                vect[dim++] = j;
        legatura_unui_singur_nod( vect, dim , i, out);
        if(i== 0) continue;
        // distanta de la nodul 1 pana la orice alt nod
        // inafara de 1 trebuie sa fie jumatate din nr
        // total de noduri, asa cum e un cicul
        fprintf(out, "(");
        for(k = 0; k != fin; k++){
            distanta(k, i, out);
            if(k + 1 != fin)
                fprintf(out, "|");
        }
        fprintf(out, ")&");
    }
}

// complexitate O(1)
void existenta_unui_nod(int i, int j, FILE *out){
     fprintf(out, "((");
     muchia(i, j, out);
     fprintf(out, "|");
     muchia_negata(j, i, out);
     fprintf(out, ")&(");
     muchia_negata(i, j, out);
     fprintf(out, "|");
     muchia(j, i, out);
     fprintf(out, "))&");
}

// complexitate O(n^2)
void muchii_echivalente(int **arr, int noduri, FILE *out){
    int i, j;
    for(i = 0; i != noduri; i++)
        for(j = i; j != noduri; j++)
            if(arr[i][j] == 1)
                existenta_unui_nod(i, j, out);
}

// complexitate O(1)
void primul_nod_muchie(int i, int j, FILE *out){
     fprintf(out, "((");
     distanta(i, j, out);
     fprintf(out, "|");
     muchia_negata(i, j, out);
     fprintf(out, ")&(");
     distanta_negata(i, j, out);
     fprintf(out, "|");
     muchia(i, j, out);
     fprintf(out, "))");
}

// complexitate O(n)
void primul_nod_distante(int *arr, int noduri, FILE *out){
    int j;
    for(j = 0; j != noduri; j++){
        if(arr[j] == 1)
            primul_nod_muchie(0, j, out);
        else
            distanta_negata(0, j, out);
        fprintf(out, "&");
    }
}

// complexitate O(n)
void muchii_singur_nod(int *vect, int dim, int x, int y, FILE *out){
    //((a1-2|~x1-2)&(~a1-2|x1-2))&((a1-3|x1-3)&(~a1-3|x1-3))&~a1-1
    int i;
    for(i = 0; i != dim; i++){
        fprintf(out, "(");
        distanta(x - 1, vect[i], out);
        fprintf(out, "&");
        muchia(vect[i], y, out);
        if(i == dim - 1)
            fprintf(out, ")");
        else
            fprintf(out, ")|");
    }
}

// complexitate O(n)
void distante_singur_nod(int x, int y, FILE *out){
    int i;
    for(i = 0; i != x ; i++){
        distanta(i, y, out);
        if(i != x- 1)
            fprintf(out, "|");
    }
}

// complexitate O(n^3)
void distante(int nr, int noduri, int **arr, FILE *out){
    int i, j, k;
    for(i = 1; i < nr; i++){
        for(j = 1; j < noduri; j++){
            // crearea vectorului cu valorile doar nodurile adiacente
            int *vect = malloc(noduri * sizeof(int)),dim = 0;
            for(k = 1; k < noduri ; k++)
                if(arr[j][k] == 1 && j != k )
                    vect[dim++] = k;

            //(~a2-2|~((a1-1&x1-2)|(a1-3&x3-2)&~(a1-2)))
            fprintf(out, "(");
            distanta(i, j, out);
            fprintf(out, "|~(");
            muchii_singur_nod(vect, dim, i, j, out);
            fprintf(out, "&~(");
            distante_singur_nod(i, j, out);
	    fprintf(out, "))&(");
            
	    //(a2-2|((a1-1&x1-2)|(a1-3&x3-2))&~(a1-2))))
            distanta_negata(i, j, out);
            fprintf(out, "|(");
            muchii_singur_nod(vect, dim, i, j, out);
            fprintf(out, "&~(");
            distante_singur_nod(i, j, out);
            if(i == nr - 1 && j == noduri - 1)
                fprintf(out, "))))");
            else
                fprintf(out, "))))&");
        }
    }
}



