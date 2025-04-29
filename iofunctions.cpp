#include "iofunctions.h"
#include <iostream>
#include <random>

void FillStackInc(List *head, int n) {
    int current = 1;
    for (List* i = head; i != nullptr && current <= n; i = i->next) {
        i->number = current++;
    }
}

void FillStackDec(List *head, int n) {
    int current = n;
    for (List* i = head; i != nullptr && current >= 0; i = i->next) {
        i->number = current--;
    }
}

void FillStackRand(List *head, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int current = 0;

    std::uniform_int_distribution<> dis(0, 99);

    for (List* i = head; i != nullptr && current++ < n; i = i->next) {
        i->number = dis(gen);
    }
}


void PrintStack(List *head) {
    for (List* i = head; i != nullptr; i = i->next) {
        std::cout << i->number << " ";
    }
}

void CreateStack(List *head, int n) {
    List* current = head;
    for (int i = 0; i < n - 1; i++) {
        current->next = new List{0, nullptr};
        current = current->next;
    }
}

void CreateQueue(List*& head, List*& tail, int n) {
    head = nullptr;
    tail = nullptr;

    for (int i = 0; i < n; ++i) {
        List* newNode = new List{0, nullptr};
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}


void PrintQueue(List* head) {
    for (List* i = head; i != nullptr; i = i->next) {
        std::cout << i->number << " ";
    }
}

void FillQueueInc(List* head, int n) {
    int current = 1;
    for (List* i = head; i != nullptr && current <= n; i = i->next) {
        i->number = current++;
    }
}

void FillQueueDec(List* head, int n) {
    int current = n;
    for (List* i = head; i != nullptr && current >= 0; i = i->next) {
        i->number = current--;
    }
}

void FillQueueRand(List* head, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    for (List* i = head; i != nullptr; i = i->next) {
        i->number = dis(gen);
    }
}

int ControlSum(List* head) {
    int sum = 0;
    for (List* i = head; i != nullptr; i = i->next) {
        sum += i->number;
    }
    return sum;
}
int SeriesCount(List* head) {
    int count = 1;
    for (List* i = head; i != nullptr && i->next != nullptr; i = i->next) {
        if (i->next->number < i->number) {
            count++;
        }
    }
    return count;
}

void DeleteList(List*& head) {
    while (head != nullptr) {
        List* temp = head;
        head = head->next;
        delete temp;
    }
}

void PrintListForward(List* head) {
    if (head == nullptr) {
        return; // базовый случай: конец списка
    }
    std::cout << head->number << " ";
    PrintListForward(head->next);
}
void PrintListBackward(List* head) {
    if (head == nullptr) {
        return; // базовый случай: конец списка
    }
    PrintListBackward(head->next);
    std::cout << head->number << " ";
}