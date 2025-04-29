#include <iostream>
#include <random>

struct Node {
    Node* next;
    union {
        int data;
        unsigned char digits[4];
    };
};

void radixSort(Node*& head) {
    Node* QHeads[256];
    Node* QTails[256];

    for (int j = 0; j < 4; j++) {  // 4 разряда
        for (int i = 0; i < 256; i++) {
            QHeads[i] = QTails[i] = nullptr;
        }

        Node* cur = head;
        head = nullptr; // Сбрасываем head, чтобы потом собрать заново

        while (cur != nullptr) {
            Node* next = cur->next;
            int d = cur->digits[j];
            cur->next = nullptr;

            if (QHeads[d] == nullptr) {
                QHeads[d] = QTails[d] = cur;
            } else {
                QTails[d]->next = cur;
                QTails[d] = cur;
            }
            cur = next;
        }

        Node* newTail = nullptr;
        for (int i = 0; i < 256; i++) {
            if (QHeads[i] != nullptr) {
                if (head == nullptr) {
                    head = QHeads[i];
                    newTail = QTails[i];
                } else {
                    newTail->next = QHeads[i];
                    newTail = QTails[i];
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
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
}

void PrintQueue(Node* head) {
    for (Node* i = head; i != nullptr; i = i->next) {
        std::cout << i->data << " ";
    }
}

void FillQueueRand(Node* head, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    for (Node* i = head; i != nullptr; i = i->next) {
        i->data = dis(gen);
    }
}

int main() {

    Node* head = new Node();
    Node* tail = new Node();
    CreateQueue(head, tail, 10);
    FillQueueRand(head, 10);
    PrintQueue(head);
    std::cout << std::endl;
    radixSort(head);
    PrintQueue(head);

    return 0;
}