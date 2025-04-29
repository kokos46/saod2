#ifndef MERGESORT_H
#define MERGESORT_H
#include "iofunctions.h"

void splitList(List* S, List*& a, List*& b, int n);
void enqueue(List*& head, List*& tail, List* node);
void merge(List* a, int q, List* b, int r, List*& cHead, List*& cTail, int& m, int& c);
void add(int number, List*& nodeHead, List*& nodeTail);
void mergeSort(List*& S, int& n, int& m, int& c);

#endif //MERGESORT_H
