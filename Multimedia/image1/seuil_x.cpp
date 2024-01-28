// test_couleur.cpp : Seuille une image en niveau de gris en x parties

#include "image_ppm.h"
#include <stdio.h>

int lowest_value(int value, int *seuils) {
  int i = 0;
  while (value > seuils[i]) {
    i++;
  }
  return seuils[i];
}

int main(int argc, char *argv[]) {
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  int *Seuils;

  if (argc < 4) {
    printf("Usage: ImageIn.pgm ImageOut.pgm Sx Sy Sz... \n");
    exit(1);
  }

  int valSeuils[argc - 3];
  valSeuils[0] = 0;
  valSeuils[argc - 3] = 255;
  for (int i = 1; i < argc - 3; i++) {
    valSeuils[i] = 255 / (argc - 3) * i;
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);

  allocation_tableau(Seuils, int, argc - 3);

  for (int i = 3; i < argc; i++) {
    Seuils[i - 3] = atoi(argv[i]);
  }

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  for (int i = 0; i < nTaille; i++) {
    ImgOut[i] = lowest_value(ImgIn[i], valSeuils);
  }

  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgOut);

  return 1;
}
