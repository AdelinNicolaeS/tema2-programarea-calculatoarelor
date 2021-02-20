// STANCA ADELIN-NICOLAE
// 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dimensiune_date(int c) {
  int ok;
  if (c == 'C') {
  ok = 1;
  }
  if (c == 'S') {
  ok = 2;
  }
  if (c == 'I') {
  ok = 4;
  }
  return ok;
}
double media_a(int **a, int n, int *m) {
  int i, j, l, s = 0, nr_el = 0;
  double m_a;
  for (i = 0; i < n; i++) {
    if (i == 0 || i == n-1) {
      for (j = 0; j < m[i]; j++) {
        for (l = 0; l < 4; l++) {
          s = s + ((char *)(&a[i][j]))[l];
          nr_el++;
        }
      }
    } else {
           s = s + ((char *)(&a[i][0]))[0] + ((char *)&a[i][m[i]-1])[3];
           nr_el = nr_el + 2;
           }
  }
  return m_a = (double) s / nr_el;
}
void sterg_schimb(int **a, int index, char op, int i, int data) {
  int index_real, x, y, j_index, aux, auux;
  if (op == 'D') {
      index_real = dimensiune_date(data)*(index - 1);
      j_index = index_real / 4;
      x = dimensiune_date(data);
      y = index_real % 4;
      while (x != 0) {
        ((char *)(&a[i][j_index]))[y] = 0;
        y++;
        x--;
      }
    }
    if (op == 'S') {
      if (data == 'S') {
        index_real = index * 2;
        j_index = index_real / 4;
        aux = ((char *)(&a[i][j_index]))[index_real % 4];
        auux = ((char *)(&a[i][j_index]))[index_real % 4 + 1];
        ((char *)(&a[i][j_index]))[index_real % 4 + 1] = aux;
        ((char *)(&a[i][j_index]))[index_real % 4] = auux;
      } else if (data == 'I') {
          aux = ((char *)(&a[i][index]))[0];
          ((char *)(&a[i][index]))[0] = ((char *)(&a[i][index]))[3];
          ((char *)(&a[i][index]))[3] = aux;
          aux = ((char *)(&a[i][index]))[1];
          ((char *)(&a[i][index]))[1] = ((char *)(&a[i][index]))[2];
          ((char *)(&a[i][index]))[2] = aux;
      }
    }
}
int parcurgere(int i, int j, int **b, int **vizitat, int n, int *m) {
  int x = 0, y = 0, z = 0 , t = 0;
  if (b[i][j] == 0) {
    vizitat[i][j] = 1;
    if ((i + 1) < n && j <4 * m[i + 1]) {
      if (vizitat[i + 1][j] == 0) {
        x = parcurgere(i + 1, j, b, vizitat, n, m);
    }
    }
    if ((i - 1) >= 0 && j <4 *m[i - 1]) {
      if (vizitat[i - 1][j] == 0) {
      y = parcurgere(i - 1, j, b, vizitat, n, m);
    }
    }
    if ((j - 1) >= 0) {
      if (vizitat[i][j - 1] == 0) {
        z = parcurgere(i, j - 1, b, vizitat, n, m);
    }
      }
    if ((j + 1) < 4*m[i]) {
          if (vizitat[i][j + 1] == 0) {
            t = parcurgere(i, j + 1, b, vizitat, n, m);
        }
    }
    return x + y + z + t + 1;
  } else {
    return 0;
         }
}
void elibereaza(int **a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
}
void afisare(int **a, int n, int *m) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m[i]; j++) {
      printf("%08X ", a[i][j]);
    }
    printf("\n");
  }
}
int main() {
  int i_min, j_min, numar = 0, **vizitat, mx = -1, x, y, val, z;
  int index, j_index, **b, index_real, k, l, n, **a, i, j, *m, ct1;
  double m_a;
  char op, data;
  scanf("%d", &n);
  a = malloc (n*sizeof(int*));
  m = calloc (n, sizeof(int));
  for (i = 0; i < n; i++) {
    scanf("%d", &m[i]);
    a[i] = calloc(m[i], sizeof(int));
    for (j = 0; j < m[i]; j++)
      scanf("%X", &a[i][j]);
  }
  m_a = media_a(a, n, m);
  printf("task 1\n%.8f\ntask 2\n", m_a);
  scanf("%d", &k);
  for (l = 0; l < k; l++) {
    scanf(" %c", &op);
    scanf(" %c", &data); scanf(" %d", &i); scanf(" %d", &index);
    if (op == 'M') {
      scanf("%X", &val);
            x = dimensiune_date(data);
            index_real = x * (index - 1);
            j_index = index_real / 4;
            if (m[i] < j_index + 1) {
            a[i] = realloc(a[i], (j_index + 1) * sizeof(int));
            for (ct1 = m[i]; ct1 < j_index; ct1++) {
              a[i][ct1] = 0;
            }
            m[i] = j_index + 1;
            }
            y = index_real % 4; z = 0;
            while (x != 0) {
                ((char *)&a[i][j_index])[y] = ((char *)&val)[z];
                z++;
                y++;
                x--;
            }
    } else {
            sterg_schimb(a, index, op, i, data);
           }
  }
  afisare(a, n, m);
  printf("task 3\n");
  b = malloc(n * sizeof(int *));
  for (i = 0; i < n; i++) {
    b[i] = calloc(4 * m[i], sizeof(int));
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < m[i]; j++) {
      for (k = 0; k < 4; k++) {
        b[i][4 * j + k] = ((char *)(&a[i][j]))[k];
      }
    }
  }
  mx = -1;
  vizitat = malloc(n * sizeof(int *));
  for (i = 0; i < n; i++) {
    vizitat[i] = calloc(4 * m[i], sizeof(int));
  }
  for (i = 0; i < n; i++) {
      for (j = 0; j < 4 * m[i]; j++) {
        if (b[i][j] == 0) {
          numar = parcurgere(i, j, b, vizitat, n, m);
          if (numar > mx) {
            mx = numar;
            i_min = i;
            j_min = j;
          }
        }
      }
    }
  printf("%d %d %d\n", i_min, j_min, mx);
  elibereaza(b, n); elibereaza(vizitat, n); elibereaza(a, n); free(m);
}
