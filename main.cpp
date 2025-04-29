#include <algorithm>
#include <iostream>
#include "iofunctions.h"
#include "MergeSort.h"
#include <windows.h>
#include <cmath>
#include <iomanip>
#include <vector>
#include "DigitalSort.h"


int mergeData100[3];
int mergeData200[3];
int mergeData300[3];
int mergeData400[3];
int mergeData500[3];

List* generateList(int n, bool ascending = true, bool descending = false) {
    List* head = nullptr;
    List* tail = nullptr;
    std::vector<int> nums(n);

    if (ascending) {
        for (int i = 0; i < n; ++i) {
            nums[i] = i + 1;
        }
    } else if (descending) {
        for (int i = 0; i < n; ++i) {
            nums[i] = n - i;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            nums[i] = rand() % 1000; // Random numbers
        }
    }

    for (int num : nums) {
        add(num, head, tail);
    }
    return head;
}

void countRunsAndChecksum(List* head, int& runs, int& checksum) {
    runs = 0;
    checksum = 0;
    if (head == nullptr) return;

    runs = 1; // минимум одна серия
    List* current = head;
    while (current != nullptr) {
        checksum += current->number;
        if (current->next != nullptr && current->number > current->next->number) {
            runs++; // новая серия начинается
        }
        current = current->next;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    List* head = new List{0, nullptr};

    List* headq = new List{0, nullptr};
    List* tail = new List{0, nullptr};

    CreateStack(head, 10);
    std::cout << "Inrementing stack: " << std::endl;
    FillStackInc(head, 10);
    PrintStack(head);
    std::cout << std::endl << "Серий: " << SeriesCount(head) << " Контрольная сумма: " << ControlSum(head) <<
            std::endl;
    std::cout << std::endl << std::endl;

    std::cout << "Decrementing stack: " << std::endl;
    FillStackDec(head, 10);
    PrintStack(head);
    std::cout << std::endl << "Серий: " << SeriesCount(head) << " Контрольная сумма: " << ControlSum(head) <<
            std::endl;
    std::cout << std::endl << std::endl;

    std::cout << "Random stack: " << std::endl;
    FillStackRand(head, 10);
    PrintStack(head);
    std::cout << std::endl << "Серий: " << SeriesCount(head) << " Контрольная сумма: " << ControlSum(head) <<
            std::endl;
    std::cout << std::endl << std::endl;

    CreateQueue(headq, tail, 10);
    std::cout << "Incrementing queue: " << std::endl;
    FillQueueInc(headq, 10);
    PrintQueue(headq);
    std::cout << std::endl << "Серий: " << SeriesCount(headq) << " Контрольная сумма: " << ControlSum(headq) <<
        std::endl;
    std::cout << std::endl << std::endl;

    std::cout << "Decrementing queue: " << std::endl;
    FillQueueDec(headq, 10);
    PrintQueue(headq);
    std::cout << std::endl << "Серий: " << SeriesCount(headq) << " Контрольная сумма: " << ControlSum(headq) <<
        std::endl;
    std::cout << std::endl << std::endl;

    std::cout << "Random queue: " << std::endl;
    FillQueueRand(headq, 10);
    PrintQueue(headq);
    std::cout << std::endl << "Серий: " << SeriesCount(headq) << " Контрольная сумма: " << ControlSum(headq) <<
        std::endl;
    std::cout << std::endl << std::endl;

    DeleteList(head);

    PrintListBackward(headq);
    std::cout << std::endl;

    PrintListForward(headq);
    std::cout << std::endl;

    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;

    List* newHead = new List{0, nullptr};
    CreateStack(newHead, 20);
    FillStackRand(newHead, 20);
    std::cout << "Исходный список: ";
    PrintStack(newHead);
    std::cout << std::endl << std::endl;

    List* a = new List{0, nullptr};
    List* b = new List{0, nullptr};

    std::cout << "Полученные списки:" << std::endl;
    splitList(newHead, a, b, 20);
    PrintStack(a);
    std::cout << std::endl;
    PrintStack(b);
    std::cout << std::endl;
    std::cout << std::endl << std::endl;


    a = nullptr;
    List* aTail = nullptr;
    add(1, a, aTail);
    add(3, a, aTail);
    add(5, a, aTail);

    b = nullptr;
    List* bTail = nullptr;
    add(2, b, bTail);
    add(4, b, bTail);
    add(6, b, bTail);

    int m = 0; // перемещения
    int c = 0; // сравнения

    List* cHead = nullptr;
    List* cTail = nullptr;

    std::cout << "Source queue 1: "; PrintQueue(a);
    std::cout << std::endl;
    std::cout << "Source queue 2: "; PrintQueue(b);
    std::cout << std::endl;

    merge(a, 3, b, 3, cHead, cTail, m, c);

    std::cout << "Merged list: ";
    PrintQueue(cHead);

    int runs, checksum;
    countRunsAndChecksum(cHead, runs, checksum);

    std::cout << "Number of runs: " << runs << std::endl;
    std::cout << "Checksum: " << checksum << std::endl;
    std::cout << "Comparisons (actual): " << c << std::endl;
    std::cout << "Movements (actual): " << m << std::endl;

    List* S = nullptr;
    tail = nullptr;

    int values[] = {5, 3, 8, 2, 7, 4, 1, 6};
    for (int v : values) {
        add(v, S, tail);
    }

    std::cout << "Original list: ";
    PrintQueue(S);
    int n = 8;

    mergeSort(S, n, m, c);

    std::cout << "Sorted list: ";
    PrintQueue(S);
    std::cout << std::endl;
    std::cout << "M = " << m << " C = " << c << std::endl;

    std::vector<int> sizes = {100, 200, 300, 400, 500};

    std::cout << "+---+----------+--------+--------+--------+" << std::endl;
    std::cout << "| N | M+C teor |  ubiv  |  rand  |  vozr  |" << std::endl;
    std::cout << "+---+----------+--------+--------+--------+" << std::endl;

    for (int n : sizes) {
        int theoretical = (n * static_cast<int>(log2(n))) * 2 + n;

        List* listDecreasing = generateList(n, false, true);
        List* listRandom = generateList(n, false, false);
        List* listAscending = generateList(n, true, false);


        int mDecreasing = 0, cDecreasing = 0;
        int mRandom = 0, cRandom = 0;
        int mAscending = 0, cAscending = 0;

        mergeSort(listDecreasing, n, mDecreasing, cDecreasing);
        mergeSort(listRandom, n, mRandom, cRandom);
        mergeSort(listAscending, n, mAscending, cAscending);

        std::cout << "|" << std::setw(3) << n
                  << "|" << std::setw(10) << std::fixed << std::setprecision(2) << theoretical
                  << "|" << std::setw(8) << mDecreasing + cDecreasing
                  << "|" << std::setw(8) << mRandom + cRandom
                  << "|" << std::setw(8) << mAscending + cAscending << "|" << std::endl;
    }
    std::cout << "+---+----------+--------+--------+--------+" << std::endl;

    return 0;
}
