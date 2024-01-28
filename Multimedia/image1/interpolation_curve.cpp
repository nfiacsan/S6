// interpolation_curve.cpp: Visualise la courbe d'interpolation

#include "image_ppm.h"
#include <math.h>
#include <stdio.h>

int interpolation(int value, int S1, int S2) {
  // return (value - S1) * 255 / (S2 - S1);
  double t = (double)(value - S1) / (S2 - S1);
  return (int)(0.5 * (1 + sin((t - 0.5) * M_PI)) * 255);
}

int main(int argc, char *argv[]) {

  FILE *f;

  if ((f = fopen("interpolation.dat", "wb")) == NULL) {
    printf("\nErreur ecriture histo\n");
    exit(EXIT_FAILURE);
  } else {
    for (int indice = 0; indice < 256; indice++) {
      fprintf(f, "%d %d\n", indice,
              (indice < 100)   ? 0
              : (indice > 200) ? 255
                               : interpolation(indice, 100, 200));
    }
  }

  fclose(f);

  return 1;
}
