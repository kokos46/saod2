#include <iostream>
#include <random>
#include <iomanip>

struct Node {
    Node* next;
    union {
        int data;
        unsigned char digits[4];
    };
};

struct Node2 {
    Node2* next;
    union {
        short int data;
        unsigned char digits[2];
    };
};

template <typename T>
void radixSort(T*& head, int byte_count, bool ascending, int& m) {
    T* QHeads[256];
    T* QTails[256];
    m = 0;

    for (int j = 0; j < byte_count; j++) {
        for (int i = 0; i < 256; i++) {
            QHeads[i] = QTails[i] = nullptr;
        }

        T* cur = head;
        head = nullptr;

        while (cur != nullptr) {
            T* next = cur->next;

            unsigned char d = cur->digits[j];

            // Отсоединяем узел - считаем перестановкой
            cur->next = nullptr;
            m++;

            if (QHeads[d] == nullptr) {
                QHeads[d] = QTails[d] = cur;
                // Здесь не считаем перестановкой, т.к. next уже nullptr
            } else {
                QTails[d]->next = cur;
                // Не считаем как перестановку, т.к. это связывание внутри корзины
                QTails[d] = cur;
            }
            cur = next;
        }

        T* newTail = nullptr;
        if (ascending) {
            for (int i = 0; i < 256; i++) {
                if (QHeads[i] != nullptr) {
                    if (head == nullptr) {
                        head = QHeads[i];
                        newTail = QTails[i];
                    } else {
                        newTail->next = QHeads[i];
                        // Не считаем связывание корзин перестановкой
                        newTail = QTails[i];
                    }
                }
            }
        } else {
            for (int i = 255; i >= 0; i--) {
                if (QHeads[i] != nullptr) {
                    if (head == nullptr) {
                        head = QHeads[i];
                        newTail = QTails[i];
                    } else {
                        newTail->next = QHeads[i];
                        // Не считаем связывание корзин перестановкой
                        newTail = QTails[i];
                    }
                }
            }
        }
    }
}

void CreateQueue(Node*& head, Node*& tail, int n) {
    head = nullptr;
    tail = nullptr;

    for (int i = 0; i < n; ++i) {
        Node* newNode = new Node();
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void CreateQueue(Node2*& head, Node2*& tail, int n) {
    head = nullptr;
    tail = nullptr;

    for (int i = 0; i < n; ++i) {
        Node2* newNode = new Node2();
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void FillQueueRand(Node* head, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);

    int count = 0;
    for (Node* i = head; i != nullptr && count < n; i = i->next, ++count) {
        i->data = dis(gen);
    }
}

void FillQueueRand2(Node2* head, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<short int> dis(0, 99);

    int count = 0;
    for (Node2* i = head; i != nullptr && count < n; i = i->next, ++count) {
        i->data = dis(gen);
    }
}

// Заполнение очереди возрастающими числами от start (по умолчанию 0)
void FillQueueIncreasing(Node* head, int n, short int start = 0) {
    int count = 0;
    short int val = start;
    for (Node* i = head; i != nullptr && count < n; i = i->next, ++count, ++val) {
        i->data = val;
    }
}

// Заполнение очереди убывающими числами от start (по умолчанию n-1)
void FillQueueDecreasing(Node* head, int n, short int start = -1) {
    int count = 0;
    short int val = (start == -1) ? static_cast<short int>(n - 1) : start;
    for (Node* i = head; i != nullptr && count < n; i = i->next, ++count, --val) {
        i->data = val;
    }
}


template <typename T>
void PrintQueue(T* head) {
    for (T* i = head; i != nullptr; i = i->next) {
        std::cout << i->data << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n = 10;
    int m = 0;

    // Работа с Node (4 байта)
    Node* head = nullptr;
    Node* tail = nullptr;
    CreateQueue(head, tail, n);
    FillQueueRand(head, n);
    std::cout << "Before sorting (Node): ";
    PrintQueue(head);
    radixSort<Node>(head, 4, true, m);
    std::cout << "After sorting (Node): ";
    PrintQueue(head);
    std::cout << "M = " << m << std::endl;
    std::cout << std::endl;

    // Работа с Node2 (2 байта)
    Node2* head2 = nullptr;
    Node2* tail2 = nullptr;
    CreateQueue(head2, tail2, n);
    FillQueueRand2(head2, n);
    std::cout << "Before sorting (Node2): ";
    PrintQueue(head2);
    radixSort<Node2>(head2, 2, true, m);
    std::cout << "After sorting (Node2): ";
    PrintQueue(head2);
    std::cout << "M = " << m << std::endl;
    std::cout << std::endl;

    Node2* head2r = nullptr;
    Node2* tail2r = nullptr;
    CreateQueue(head2r, tail2r, n);
    FillQueueRand2(head2r, n);
    std::cout << "Before sorting (Node2): ";
    PrintQueue(head2r);
    radixSort<Node2>(head2r, 2, false, m);
    std::cout << "After sorting (Node2) reversed: ";
    PrintQueue(head2r);
    std::cout << "M = " << m << std::endl;
    std::cout << std::endl << std::endl;

    std::cout << "+---+--------+--------+--------+" << std::endl;
    std::cout << "| N |  vozr  |  ubiv  |  rand  |" << std::endl;
    std::cout << "+---+--------+--------+--------+" << std::endl;

    for (int i : {100, 200, 300, 400, 500}) {
        std::cout << "|" << std::setw(3) << i;

        int mtable_inc = 0;
        int mtable_dec = 0;
        int mtable = 0;
        Node* headTable = new Node();
        Node* tailTable = new Node();

        CreateQueue(headTable, tailTable, i);

        FillQueueIncreasing(headTable, i);
        radixSort<Node>(headTable, 4, true, mtable_inc);
        std::cout << "|" << std::setw(8) << mtable_inc;

        FillQueueDecreasing(headTable, i);
        radixSort<Node>(headTable, 4, true, mtable_dec);
        std::cout << "|" << std::setw(8) << mtable_dec;

        FillQueueRand(headTable, i);
        radixSort<Node>(headTable, 4, true, mtable);
        std::cout << "|" << std::setw(8) << mtable << "|";

        std::cout << std::endl;

    }
    std::cout << "+---+--------+--------+--------+" << std::endl;

    return 0;
}