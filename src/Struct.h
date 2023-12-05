#pragma once

#define const 101

#define const3 100

#define const2 21

FILE *fin, *fout;

struct masini {
  // siruri de caractere care vor retine brandul, numarul de inmatriculare
  // si tipul de combustibil folosit de masina
  char * brand, * numar, * combustibil;
  double consum;
  int km;
  int an_fabricatie;
};