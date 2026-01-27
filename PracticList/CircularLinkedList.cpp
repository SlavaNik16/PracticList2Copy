#include <iostream>
#include <fstream>
#include "CircularNode.cpp"
using namespace std;

// Класс кольцевого списка
template <typename T>
class CircularLinkedList {
private:
    CircularNode<T>* head;
    int size;

public:
    // Конструкторы
    CircularLinkedList() : head(nullptr), size(0) {}

    // Деструктор
    ~CircularLinkedList() {
        clear();
    }

    void clear() {
        if (!head) return;

        // Разрываем кольцо
        CircularNode<T>* last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = nullptr;

        // Удаляем все узлы
        CircularNode<T>* current = head;
        while (current != nullptr) {
            CircularNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = nullptr;
        size = 0;
    }


    void add(T val) {
        CircularNode<T>* newNode = new CircularNode<T>(val);

        if (!head) {
            head = newNode;
            head->next = head; // Замыкаем на себя
        }
        else {
            // Находим последний узел
            CircularNode<T>* last = head;
            while (last->next != head) {
                last = last->next;
            }

            // Вставляем новый узел
            last->next = newNode;
            newNode->next = head;
        }
        size++;
    }

    void save(ofstream& f) {
        if (!head) return;

        auto* cur = head;

        do {
            f << cur->data << " ";
            cur = cur->next;
        } while (cur != head);
    }


    void show() {
        if (!head) return;

        auto* cur = head;
        do {
            cout << cur->data << " ";
            cur = cur->next;
        } while (cur != head);

        cout << endl;
    }

    void sortInRange(T minVal, T maxVal) {
        if (!head || head->next == head) return;

        // 1. Подсчитываем количество элементов в диапазоне
        CircularNode<T>* current = head;
        int inRangeCount = 0;
        int totalElements = 0;

        do {
            totalElements++;
            if (current->data >= minVal && current->data <= maxVal) {
                inRangeCount++;
            }
            current = current->next;
        } while (current != head);

        // 2. Пузырьковая сортировка с учетом разделения
        bool swapped;
        CircularNode<T>* lastSorted = nullptr;
        int sortedCount = 0;

        do {
            swapped = false;
            current = head;
            CircularNode<T>* prev = nullptr;
            int position = 0;

            do {
                CircularNode<T>* nextNode = current->next;

                // Проверяем, нужно ли менять местами
                bool shouldSwap = false;

                if (nextNode != head) {
                    // Определяем, в каких частях находятся элементы
                    bool currentInRange = false;
                    bool nextInRange = false;

                    // Считаем, сколько элементов в диапазоне мы прошли
                    CircularNode<T>* checkNode = head;
                    int currentInRangeCount = 0;
                    int nextInRangeCount = 0;

                    for (int i = 0; i <= position; i++) {
                        if (checkNode->data >= minVal && checkNode->data <= maxVal) {
                            currentInRangeCount++;
                        }
                        checkNode = checkNode->next;
                    }

                    checkNode = head;
                    for (int i = 0; i <= position + 1; i++) {
                        if (checkNode->data >= minVal && checkNode->data <= maxVal) {
                            nextInRangeCount++;
                        }
                        checkNode = checkNode->next;
                    }

                    currentInRange = (current->data >= minVal && current->data <= maxVal);
                    nextInRange = (nextNode->data >= minVal && nextNode->data <= maxVal);

                    // Правила сравнения:
                    // 1. Если оба в диапазоне или оба вне диапазона - сравниваем значения
                    // 2. Если первый вне диапазона, а второй в диапазоне - меняем местами
                    // 3. Если первый в диапазоне, а второй нет - не меняем

                    if (currentInRange && nextInRange) {
                        // Оба в диапазоне
                        shouldSwap = current->data > nextNode->data;
                    }
                    else if (!currentInRange && !nextInRange) {
                        // Оба вне диапазона
                        shouldSwap = current->data > nextNode->data;
                    }
                    else if (!currentInRange && nextInRange) {
                        // Текущий вне диапазона, следующий в диапазоне
                        // Нужно переместить следующий (в диапазоне) вперед
                        shouldSwap = true;
                    }
                }

                if (shouldSwap) {
                    T temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;
                    swapped = true;
                }

                prev = current;
                current = nextNode;
                position++;

            } while (current->next != head && current->next != lastSorted);

            lastSorted = current;
            sortedCount++;

        } while (swapped);
    }
};