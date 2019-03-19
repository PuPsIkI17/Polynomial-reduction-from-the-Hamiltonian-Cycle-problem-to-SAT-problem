
// Pislari Vadim 

#include <stdio.h>
#include <stdlib.h>

void legaturi_intre_toate_nodurile(int **arr, int noduri, FILE *out);
void muchii_echivalente(int **arr, int noduri, FILE *out);
void primul_nod_distante(int *arr, int noduri, FILE *out);
void distante(int nr, int noduri, int **arr, FILE *out);

int main(int argc, char *argv[]){

    //deschiderea fisierelor
    FILE *in, *out;
    in = fopen(argv[1],"r"); 
    if (in == NULL){
        printf("nu se poate deschide fisierul\n");
        return 1;
    }
    out = fopen(argv[2],"w");   
    if (out == NULL){
        printf("nu se poate deschide fisierul\n");
        return 1;
    }   

    int noduri, i, j;
    fscanf(in,"%d", &noduri);

    //alocarea matricii de adiacenta
    int **arr = (int **) malloc(noduri * sizeof(int*));
    for(i = 0; i != noduri; i++)
        arr[i] = (int *) malloc(noduri * sizeof(int));

    //matricea de adiacenta initializata cu 0
    for(i = 0; i != noduri; i++){
        for(j = 0; j != noduri; j++)
            arr[i][j] = 0;
    }
    //citirea datelor
    while(1){
        int sursa, destinatie;
        fscanf(in,"%d", &sursa);
        if(sursa == -1) break;
        fscanf(in,"%d",&destinatie);
        arr[sursa - 1][destinatie - 1] = 1;
        arr[destinatie - 1][sursa - 1] = 1;
    }
   

    //
    muchii_echivalente(arr, noduri, out);

    // orice nod trebuie sa apartina exact la 2 muchii 
    // intr-o parcurgere
    legaturi_intre_toate_nodurile(arr, noduri, out);

    // toate muchiile apar o singura data intr-o parcurgere
    primul_nod_distante(arr[0], noduri, out);
    distante(noduri / 2 + 1 , noduri, arr, out);
    fclose(out);
    fclose(in);

    return 0;
}



