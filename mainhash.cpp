#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

struct List {
    int number;
    List* next;
};

int hash_function(int key, int m) {
    return key % m;
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

void printList(List* head) {
    List* current = head;
    while (current != nullptr) {
        std::cout << current->number << " ";
        current = current->next;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int m = 5;

    // Инициализируем массивы указателей nullptr, чтобы избежать "пустых" узлов
    List* lists_heads[m];
    List* lists_tails[m];

    for (int i = 0; i < m; i++) {
        lists_heads[i] = nullptr;
        lists_tails[i] = nullptr;
    }

    int sequence[20] = {3, 17, 8, 12, 1, 19, 6, 14, 5, 10, 0, 7, 13, 2, 18, 4, 9, 15, 11, 16};

    std::cout << "Исходная последовательность: ";
    for (int i: sequence) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (int i : sequence) {
        int h = hash_function(i, m);
        add(i, lists_heads[h], lists_tails[h]);
    }

    // Вывод содержимого всех списков
    for (int i = 0; i < m; i++) {
        std::cout << "List " << i << ": ";
        if (lists_heads[i] == nullptr) {
            std::cout << "(empty)";
        } else {
            printList(lists_heads[i]);
        }
        std::cout << std::endl;
    }

    std::vector<int> prime_numbers = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
    int num_elements = 20;

    std::cout << "Размер хеш-таблицы Количество исходных символов Количество коллизий\n";
    std::cout << "----------------------------------------------------------------------\n";

    for (int m : prime_numbers) {
        List* lists_heads[m];
        List* lists_tails[m];

        for (int i = 0; i < m; i++) {
            lists_heads[i] = nullptr;
            lists_tails[i] = nullptr;
        }

        int collisions = 0;
        for (int i : sequence) {
            int hash_val = hash_function(i, m);
            if (lists_heads[hash_val] != nullptr) {
                collisions++;
            }
            add(i, lists_heads[hash_val], lists_tails[hash_val]);
        }

        std::cout << m << "\t\t" << num_elements << "\t\t" << collisions << "\n";

        // Освобождение памяти
        for (int i = 0; i < m; i++) {
            List* current = lists_heads[i];
            while (current != nullptr) {
                List* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    return 0;
}
