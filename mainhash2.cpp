#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <windows.h>

// Функция для проверки простого числа
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Функция хеширования
int hash_function(int key, int m) {
    return key % m;
}

// Линейное пробирование
int linearProbe(int hash, int i, int tableSize) {
    return (hash + i) % tableSize;
}

// Квадратичное пробирование
int quadraticProbe(int hash, int i, int tableSize) {
    return (hash + i * i) % tableSize;
}

// Функция для вывода хеш-таблицы
void printHashTable(const std::vector<int>& table) {
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i] == -1) {
            std::cout << "[" << i << "]: empty" << std::endl;
        } else {
            std::cout << "[" << i << "]: " << table[i] << std::endl;
        }
    }
    std::cout << std::endl;
}

// Функция для заполнения таблицы и подсчёта коллизий
void processHashTable(const std::vector<int>& keys, int tableSize,
                    bool printTables = false) {
    std::vector<int> linearTable(tableSize, -1);
    std::vector<int> quadraticTable(tableSize, -1);
    int linearCollisions = 0;
    int quadraticCollisions = 0;

    // Заполнение линейной таблицы
    for (int key : keys) {
        int hash = hash_function(key, tableSize);
        int i = 0;
        while (i < tableSize) {
            int pos = linearProbe(hash, i, tableSize);
            if (linearTable[pos] == -1) {
                linearTable[pos] = key;
                if (i > 0) linearCollisions++;
                break;
            }
            i++;
        }
    }

    // Заполнение квадратичной таблицы
    for (int key : keys) {
        int hash = hash_function(key, tableSize);
        int i = 0;
        while (i < tableSize) {
            int pos = quadraticProbe(hash, i, tableSize);
            if (quadraticTable[pos] == -1) {
                quadraticTable[pos] = key;
                if (i > 0) quadraticCollisions++;
                break;
            }
            i++;
        }
    }

    // Вывод таблицы сравнения коллизий
    std::cout << "| " << std::setw(18) << tableSize
              << "| " << std::setw(23) << keys.size()
              << "| " << std::setw(18) << linearCollisions
              << "| " << std::setw(19) << quadraticCollisions << "|" << std::endl;

    // Вывод самих хеш-таблиц (если требуется)
    if (printTables) {
        std::cout << "\nLinear Probing Hash Table (size " << tableSize << "):\n";
        printHashTable(linearTable);

        std::cout << "Quadratic Probing Hash Table (size " << tableSize << "):\n";
        printHashTable(quadraticTable);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Генерируем 10 простых чисел от 11 до 101
    std::vector<int> primeSizes;
    for (int i = 11; i <= 101; i++) {
        if (isPrime(i)) {
            primeSizes.push_back(i);
            if (primeSizes.size() == 10) break;
        }
    }

    // Набор ключей для демонстрации
    std::vector<int> keys = {12, 22, 32, 42, 52, 62, 72, 82, 92, 102, 13, 23, 33, 43, 53, 63, 73, 83, 93, 103};

    // Вывод заголовка таблицы сравнения
    std::cout << std::left
              << std::setw(20) << "| Размер хеш-таблицы"
              << std::setw(25) << "| Количество ключей"
              << std::setw(20) << "| Линейные пробы"
              << "| Квадратичные пробы |" << std::endl;
    std::cout << std::string(85, '-') << std::endl;

    // Обработка для каждого размера таблицы
    for (size_t i = 0; i < primeSizes.size(); i++) {
        // Для последней таблицы выведем её содержимое
        bool printTables = (i == primeSizes.size() - 1);
        processHashTable(keys, primeSizes[i], printTables);
    }

    return 0;
}