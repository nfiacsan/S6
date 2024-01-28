// plot "histo_rgb.dat" u 1:2 lt rgb "red" title "rouge" with lines, "" u 1:3 lt
// rgb "green" title "vert" with lines, "" u 1:4 lt rgb "blue" title "bleu" with
// lines

// histo_rgb.cpp: Réalise l'histogramme d'une image couleur

#include "image_ppm.h"
#include <cstdio>
#include <stdio.h>

int main(int argc, char *argv[]) {
  char cNomImgLue[250];
  int histoR[256] = {0};
  int histoG[256] = {0};
  int histoB[256] = {0};
  int nH, nW, nTaille, nR, nG, nB;

  if (argc != 2) {
    printf("Usage: ImageIn.ppm\n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);

  OCTET *ImgIn;

  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  int nTaille3 = nTaille * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nTaille);

  for (int i = 0; i < nTaille3; i += 3) {
    nR = ImgIn[i];
    nG = ImgIn[i + 1];
    nB = ImgIn[i + 2];

    histoR[nR]++;
    histoG[nG]++;
    histoB[nB]++;
  }

  FILE *f_histo;

  if ((f_histo = fopen("histo_rgb.dat", "wb")) == NULL) {
    printf("\nErreur ecriture histo\n");
    exit(EXIT_FAILURE);
  } else {

    for (int indice = 0; indice < 256; indice++) {
      fprintf(f_histo, "%d %d %d %d\n", indice, histoR[indice], histoG[indice],
              histoB[indice]);
    }
  }

  free(ImgIn);
  fclose(f_histo);

  return 1;
}
