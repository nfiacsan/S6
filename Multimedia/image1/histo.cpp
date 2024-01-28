// histo.cpp: Realise l'histogramme d'une image

#include "image_ppm.h"
#include <cstdio>
#include <stdio.h>

int main(int argc, char *argv[]) {
  char cNomImgLue[250];
  int histo[256] = {0};
  int nH, nW, nTaille;

  if (argc != 2) {
    printf("Usage: ImageIn.pgm\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);

  OCTET *ImgIn;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

  for (int i = 0; i < nTaille; i++) {
    histo[ImgIn[i]]++;
  }

  FILE *f_histo;

  if ((f_histo = fopen("histo.dat", "wb")) == NULL) {
    printf("\nErreur ecriture histo\n");
    exit(EXIT_FAILURE);
  } else {

    for (int indice = 0; indice < 256; indice++) {
      fprintf(f_histo, "%d %d\n", indice, histo[indice]);
    }
  }

  free(ImgIn);
  fclose(f_histo);

  return 1;
}
