// gamma.cpp : Applique une correction gamma à une image rgb

#include "image_ppm.h"
#include <stdio.h>

float apply_gamma(float x, float gamma) { return 255 * pow(x / 255, gamma); }

int main(int argc, char *argv[]) {
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  float gamma;

  if (argc != 4) {
    printf("Usage: ImageIn.ppm ImageOut.ppm gamma\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);
  sscanf(argv[3], "%f", &gamma);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  int nTaille3 = nTaille * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille3);

  for (int i = 0; i < nTaille3; i += 3) {
    ImgOut[i] = apply_gamma(ImgIn[i], gamma);
    ImgOut[i + 1] = apply_gamma(ImgIn[i + 1], gamma);
    ImgOut[i + 2] = apply_gamma(ImgIn[i + 2], gamma);
  }

  ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
  free(ImgIn);
  free(ImgOut);

  return 1;
}
