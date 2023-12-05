#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "Utils.h"

int main() {
  fin = fopen("fisier.in", "r");
  fout = fopen("fisier.out", "w");
  int N, i, nr_benzina, nr_motorina, nr_electric, nr_hibrid, valid[const], ok = 1;
  // vector care retine pe ce pozitie s-a calculat consumul
  // pentru masina de un anumit brand
  int gasit[const]={0};
  double nr_litri[const] = {-1}, pret;
  nr_benzina = 0;
  nr_motorina = 0;
  nr_electric = 0;
  nr_hibrid = 0;
  char aux[const2], op;
  struct masini * v;
  fscanf(fin, "%d", & N);
  // alocam dinamic memorie pentru vectorul de masini v
  v = malloc(N * sizeof(struct masini));
  // citim fiecare camp al strucutrii, alocand dinamic spatiu pentru
  // sirurile de caractere
  for (i = 0; i < N; i++) {
    fscanf(fin, "%s", aux);
    v[i].brand = malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(v[i].brand, aux);
    fscanf(fin, "%s", aux);
    v[i].numar = malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(v[i].numar, aux);
    fscanf(fin, "%s", aux);
    v[i].combustibil = malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(v[i].combustibil, aux);
    fscanf(fin, "%lf", & (v[i].consum));
    fscanf(fin, "%d", & (v[i].km));
    fscanf(fin, "%d", & (v[i].an_fabricatie));
  }
  fscanf(fin, " %c", & op);
  // in functie de operatia citita apelam functia necesara
  if (op == 'a') {
    tip(v, N, & nr_benzina, & nr_motorina, & nr_hibrid, & nr_electric);
    fprintf(fout, "benzina - %d\n", nr_benzina);
    fprintf(fout, "motorina - %d\n", nr_motorina);
    fprintf(fout, "hibrid - %d\n", nr_hibrid);
    fprintf(fout, "electric - %d\n", nr_electric);
  } else if (op == 'b') {
    consum(v, N, nr_litri, gasit);
    for (i = 0; i < N; i++) {
      if (nr_litri[i]!=-1 && gasit[i]!=0) {
        if (strcmp(v[i].combustibil, "benzina") == 0) pret = 8.02;
        else if (strcmp(v[i].combustibil, "motorina") == 0) pret = 9.29;
        else if (strcmp(v[i].combustibil, "hibrid") == 0) pret = 8.02;
        else if (strcmp(v[i].combustibil, "electric") == 0) pret = 0.0;
        fprintf(fout, "%s a consumat %.2lf - %.2lf lei\n", v[i].brand, nr_litri[i], nr_litri[i] * pret);
      }
    }
  } else if (op == 'c') {
    numar(v, N, valid);
    for (i = 0; i < N; i++){
    ok = 1;
    if (valid[i] == 0) {
        fprintf(fout, "%s cu numarul %s: numar invalid\n", v[i].brand, v[i].numar);
        ok = 0;
    }
    if (ok == 1) {
      fprintf(fout, "%s cu numarul %s: numar valid\n", v[i].brand, v[i].numar);
    }
    }
  } else if (op == 'd') {
    pret_estimativ(v, N);
  }
   for (i = 0; i < N; i++) {
    free(v[i].brand);
    free(v[i].numar);
    free(v[i].combustibil); 
  }
  free(v);
}
