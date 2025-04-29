#include <iostream>

struct Node {
    Node* next;
    union {
        int data;
        unsigned char digits[4];

    };
};

void radixSort(Node* head) {
    Node* QHeads[256];
    Node* QTails[256];
    for (int)
        for (int i = 0; i < 256; i++) {
            QHeads[i] = QTails[i] = nullptr;
        }
        Node* cur = head;
}

int main() {

    return 0;
}