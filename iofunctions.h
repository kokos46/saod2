#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

struct List {
    int number;
    List* next;
};

// Заполнение стеков
void FillStackInc(List* head, int n);
void FillStackDec(List* head, int n);
void FillStackRand(List* head, int n);

void PrintStack(List* head); // Печать стека
void CreateStack(List* head, int n); // Инициализация пустого стека

void CreateQueue(List*& head, List*& tail, int n);
void PrintQueue(List* head);

void FillQueueInc(List* head, int n);
void FillQueueDec(List* head, int n);
void FillQueueRand(List* head, int n);

int ControlSum(List* head);
int SeriesCount(List* head);

void DeleteList(List*& head);
void PrintListForward(List* head);
void PrintListBackward(List* head);

#endif //IOFUNCTIONS_H
