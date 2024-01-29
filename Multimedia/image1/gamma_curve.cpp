/**
 * @file gamma_curve.cpp
 * @brief Applique une correction gamma à une image
 */

#include "image_ppm.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  float gamma;

  if (argc != 2) {
    printf("Usage: gamma\n");
    exit(1);
  }

  sscanf(argv[1], "%f", &gamma);

  FILE *f_histo;

  if ((f_histo = fopen("gamma_curve.dat", "wb")) == NULL) {
    printf("\nErreur ecriture histo\n");
    exit(EXIT_FAILURE);
  } else {
    for (int indice = 0; indice < 256; indice++) {
      fprintf(f_histo, "%d %d %d\n", indice, indice,
              apply_gamma(indice, gamma));
    }
  }

  fclose(f_histo);

  return 1;
}
