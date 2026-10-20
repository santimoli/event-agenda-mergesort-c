#ifndef HEADER_MERGESORT_H
#define HEADER_MERGESORT_H

#include "HeaderMergesort.h"
#include "HeaderEvento.h"
#include "HeaderUtils.h"

#define maxN 2048

#define less(A,B) (compararEventos(A,B) < 0)
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

typedef ptrEvento Item;

void mergesort(Item a[], int l, int r);

#endif //HEADER_MERGESORT_H


