#pragma once

#include <string.h>

#include "Struct.h"

// functie care calculeaza numarul de masini de fiecare tip
// in fucntie de combustibil
void tip(struct masini * v, int n, int * nr_benzina, int * nr_motorina,
         int * nr_hibrid, int * nr_electric) {
  int i;
  // parcurgem fiecare masina din vectorul de masini si in functie de tipul
  // acestei incrementam variabila potrivita
  for (i = 0; i < n; i++) {
    // folosim functia strcmp din biblioteca <string.h> pentru a verifica daca
    // sirul de caractere care retine tipul unei masini coincide cu unul din
    // cele 4 tipuri predefinite
    if (strcmp(v[i].combustibil, "benzina") == 0) {
      * nr_benzina = * nr_benzina + 1;
    } else if (strcmp(v[i].combustibil, "motorina") == 0) {
      * nr_motorina = * nr_motorina + 1;
    } else if (strcmp(v[i].combustibil, "hibrid") == 0) {
      * nr_hibrid = * nr_hibrid + 1;
    } else if (strcmp(v[i].combustibil, "electric") == 0) {
      * nr_electric = * nr_electric + 1;
    }
  }
}

// functie care calculeaza numarul de litri consumati de
// fiecare tip de masini, in fucntie de brand
void consum(struct masini * v, int n, double nr_litri[], int gasit[]) {
  // retine pentru fiecare masina daca i-a fost calculat consumul
  int gas[const] = {0};
  int i, j;
  for (i = 0; i < n ; i++) {
    if (gas[i] == 0) {
      // daca masina nu are consumul calculat
      // marcam masina, caci urmeaza sa ii calculam consumul
      gas[i] = 1;
      nr_litri[i] = (double)((v[i].consum * (double)v[i].km) / (double)const3);
      gasit[i] = 1;
      // parcurgem masinile si calculam consumul pentru toate masinile din
      // acelasi brand
      for (j = i + 1; j < n; j++) {
        if (strcmp(v[j].brand, v[i].brand) == 0) {
          if (gas[j] == 0) {
            gas[j] = 1;
            nr_litri[i] = nr_litri[i] + (double)((v[j].consum * (double)v[j].km) / (double)const3);
          }
        }
      }
    }
  }
}

// functie care verifica daca numarul masinii este valid
void numar(struct masini * v, int n, int valid[]) {
  int i, j, nrlit, nrcf, ok, nrlit2, k;
  for (i = 0; i < n; i++) {
    nrlit = 0;
    nrlit2 = 0;
    nrcf = 0;
    ok = 0;
    j = 0;
    // calculeaza numarul de litere de la inceputul numerului
    while (v[i].numar[j] >= 'A' && v[i].numar[j] <= 'Z') {
      nrlit++;
      j++;
      ok = 1;
    }
    // calculeaza numarul de cifre din numar
    while (v[i].numar[j] >= '0' && v[i].numar[j] <= '9' && ok) {
      nrcf++;
      j++;
    }
    // calculeaza numarul de litere de la finalul numarului
    for (k = j; k < strlen(v[i].numar); k++) {
      if (v[i].numar[k] >= 'A' && v[i].numar[k] <= 'Z')
        nrlit2++;
    }
    // verifica conditiile
    if (nrlit == 1 || nrlit == 2) {
      if (nrcf == 3 || nrcf == 2) {
        if (nrlit2 == 3) {
          valid[i] = 1;
        } else {
            valid[i] = 0;
        }
      } else {
        valid[i] = 0;
      }
    } else {
        valid[i] = 0;
    }
  }
}

// retuneaza in functie de anul fabricatiei o constanta care sa modifice pretul
float pret_an(int an) {
  if(an < 2000) {
    return 0.1;
  }
  if(an >= 2000 && an < 2005) {
    return 2;
  }
  if(an >= 2005 && an < 2010) {
    return 3;
  }
  if(an >= 2010 && an < 2015) {
    return 4;
  }
  if(an >= 2015 && an < 2020) {
    return 5;
  }
  if(an >= 2020) {
    return 6;
  }
}

// retuneaza in functie de km o constanta care sa modifice pretul
float pret_km(int km) {
  if(km < 50000) {
    return 7;
  }
  if(km >= 50000 && km < 100000) {
    return 6;
  }
  if(km >= 100000 && km < 150000) {
    return 5;
  }
  if(km >= 150000 && km < 200000) {
    return 4;
  }
  if(km >= 200000 && km < 250000) {
    return 3;
  }
  if(km >= 250000 && km < 300000) {
    return 2;
  }
  if(km >= 300000) {
    return 1;
  }
}

// retuneaza in functie de brand o constanta care sa modifice pretul
float pret_brand(char *s) {
  if(strcmp(s, "Dacia") == 0) {
    return 2;
  }
  if(strcmp(s, "Skoda") == 0) {
    return 4;
  }
  if(strcmp(s, "Mercedes") == 0) {
    return 6;
  }
  if(strcmp(s, "Tesla") == 0) {
    return 8;
  }
}

// calculeaza pretul in functie de brand, anul fabricatie, consum si numarul
// de km
void pret_estimativ(struct masini *v, int n) {
  int i, pret = 1000;
  float c;
  for(i = 0; i < n; i++) {
    pret = 1000;
    c = pret_an(v[i].an_fabricatie);
    pret = pret * c;
    if(v[i].consum < 7) {
      pret = pret + 200;
    } else {
      pret = pret + 500;
    }
    c = pret_km(v[i].km);
    pret = pret + 100 * c;
    c = pret_brand(v[i].brand);
    pret = pret * c;
    fprintf(fout, "Pretul estimativ al masinii %d este : %d euro\n", i, pret);
  }
}
