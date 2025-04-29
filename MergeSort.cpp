#include "MergeSort.h"
#include <iostream>

void splitList(List* S, List*& a, List*& b, int n) {
    a = S, b = S->next;
    n = 1;
    List* k = a;
    List* p = b;
    while (p != nullptr) {
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
}

void merge(List* a, int q, List* b, int r, List*& cHead, List*& cTail, int& m, int& c) {
    cHead = nullptr;
    cTail = nullptr;

    while (q != 0 && r != 0) {
        c++;
        if (a->number <= b->number) {
            add(a->number, cHead, cTail);
            a = a->next;
            q--;
            m++;
        } else {
            add(b->number, cHead, cTail);
            b = b->next;
            r--;
            m++;
        }
    }

    while (q > 0) {
        add(a->number, cHead, cTail);
        a = a->next;
        q--;
        m++;
    }

    while (r > 0) {
        add(b->number, cHead, cTail);
        b = b->next;
        r--;
        m++;
    }
}

void add(int number, List*& nodeHead, List*& nodeTail) {
    List* newNode = new List;
    newNode->number = number;
    newNode->next = nullptr;
    if (nodeHead == nullptr) {
        nodeHead = newNode;
        nodeTail = newNode;
    }
    else {
        nodeTail->next = newNode;
        nodeTail = newNode;
    }
}

void splitBlock(List* S, List*& a, List*& b, int blockSize) {
    a = S;
    b = nullptr;
    if (!S) return;

    for (int i = 1; i < blockSize && S->next; i++) {
        S = S->next;
    }
    b = S->next;
    S->next = nullptr;
}

// Функция mergesort с использованием расщепления и слияния
void mergeSort(List*& S, int& n, int& m, int& c) {
    m = 0; c = 0;
    if (!S || !S->next) return;

    int totalSize = n;
    int blockSize = 1;

    while (blockSize < totalSize) {
        List* current = S;
        List* newHead = nullptr;
        List* lastNode = nullptr;

        while (current) {
            // Получаем первый блок
            List* a = current;
            List* b = nullptr;
            splitBlock(current, a, b, blockSize);
            current = b;

            // Получаем второй блок
            List* cBlock = nullptr;
            if (current) {
                splitBlock(current, b, cBlock, blockSize);
                current = cBlock;
            }

            // Сливаем блоки
            List* mergedHead = nullptr;
            List* mergedTail = nullptr;
            int aSize = 0;
            List* tempA = a;
            while (tempA) {
                aSize++;
                tempA = tempA->next;
            }

            int bSize = 0;
            List* tempB = b;
            while (tempB) {
                bSize++;
                tempB = tempB->next;
            }

            if (a && b) {
                merge(a, aSize, b, bSize, mergedHead, mergedTail, m, c);
            } else {
                mergedHead = a ? a : b;
                if (mergedHead) {
                    List* temp = mergedHead;
                    while(temp->next){
                        temp = temp->next;
                    }
                    mergedTail = temp;
                }
                m += aSize + bSize;
            }

            // Соединяем с предыдущими результатами
            if (!newHead) {
                newHead = mergedHead;
                lastNode = mergedTail;
            } else {
                if(lastNode) lastNode->next = mergedHead;
                lastNode = mergedTail;
            }
        }

        S = newHead;
        blockSize <<= 1;
    }
}
