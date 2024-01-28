// profil.cpp : Histogramme d'une ligne ou d'une colonne d'une image

#include "image_ppm.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char cNomImgLue[250];
  int histo[256] = {0};
  int nH, nW, nTaille, numL;
  char orientation;

  if (argc != 4) {
    printf("Usage: ImageIn.pgm L/C numL/C\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%c", &orientation);
  sscanf(argv[3], "%d", &numL);

  OCTET *ImgIn;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  if ((orientation == 'L' && nH < numL) || (orientation == 'C' && nW < numL)) {
    printf("Erreur numL\n");
    exit(1);
  }

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

  int i = numL;
  if (orientation == 'L') {
    for (int j = 0; j < nW; j++) {
      histo[ImgIn[i * nW + j]]++;
    }
  } else {
    for (int j = 0; j < nH; j++) {
      histo[ImgIn[j * nH + i]]++;
    }
  }

  FILE *f_histo;

  if ((f_histo = fopen("profil.dat", "wb")) == NULL) {
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
