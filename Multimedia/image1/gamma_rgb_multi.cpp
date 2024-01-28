// gamma.cpp : Applique une correction gamma à une image rgb avec une valeur par
// couleur

#include "image_ppm.h"
#include <stdio.h>

float apply_gamma(float x, float gamma) { return 255 * pow(x / 255, gamma); }

int main(int argc, char *argv[]) {
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  float gR, gG, gB;

  if (argc != 6) {
    printf("Usage: ImageIn.ppm ImageOut.ppm gR gG gB\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);
  sscanf(argv[3], "%f", &gR);
  sscanf(argv[4], "%f", &gG);
  sscanf(argv[5], "%f", &gB);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  int nTaille3 = nTaille * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille3);

  for (int i = 0; i < nTaille3; i += 3) {
    ImgOut[i] = apply_gamma(ImgIn[i], gR);
    ImgOut[i + 1] = apply_gamma(ImgIn[i + 1], gG);
    ImgOut[i + 2] = apply_gamma(ImgIn[i + 2], gB);
  }

  ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgOut);

  return 1;
}
