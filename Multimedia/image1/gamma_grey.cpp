/**
 * @file gamma_grey.cpp
 * @brief Applique une correction gamma à une image
 */

#include "image_ppm.h"
#include <stdio.h>

float apply_gamma(float x, float gamma) { return 255 * pow(x / 255, gamma); }

int main(int argc, char *argv[]) {
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  float gamma;

  if (argc != 4) {
    printf("Usage: ImageIn.pgm ImageOut.pgm gamma\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);
  sscanf(argv[3], "%f", &gamma);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nTaille);
  allocation_tableau(ImgOut, OCTET, nTaille);

  for (int i = 0; i < nTaille; i++) {
    ImgOut[i] = apply_gamma(ImgIn[i], gamma);
  }

  ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgOut);

  return 1;
}
