/**
 * @file interpolation_curve.cpp
 * @brief Visualise la courbe d'interpolation
 */

#include "image_ppm.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  FILE *f;

  if ((f = fopen("interpolation.dat", "wb")) == NULL) {
    printf("\nErreur ecriture histo\n");
    exit(EXIT_FAILURE);
  } else {
    for (int indice = 0; indice < 256; indice++) {
      fprintf(f, "%d %d %d\n", indice,
              (indice < 100)   ? 0
              : (indice > 200) ? 255
                               : interpolation_lin(indice, 100, 200),
              (indice < 100)   ? 0
              : (indice > 200) ? 255
                               : interpolation_sin(indice, 100, 200));
    }
  }

  fclose(f);

  return 1;
}
