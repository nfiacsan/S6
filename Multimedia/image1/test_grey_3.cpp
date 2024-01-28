// test_grey.cpp : Seuille une image en niveau de gris en 4 parties

#include "image_ppm.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S1, S2, S3;

  if (argc != 6) {
    printf("Usage: ImageIn.pgm ImageOut.pgm S1 S2 S3 \n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);
  sscanf(argv[3], "%d", &S1);
  sscanf(argv[4], "%d", &S2);
  sscanf(argv[5], "%d", &S3);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  for (int i = 0; i < nTaille; i++) {
    if (ImgIn[i] < S1)
      ImgOut[i] = 0;
    else if (ImgIn[i] < S2)
      ImgOut[i] = 85;
    else if (ImgIn[i] < S3)
      ImgOut[i] = 170;
    else
      ImgOut[i] = 255;
  }

  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgOut);

  return 1;
}