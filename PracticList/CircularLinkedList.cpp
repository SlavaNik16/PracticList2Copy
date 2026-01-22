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

    void sort() {
        if (!head || head->next == head) return;

        bool swapped;
        CircularNode<T>* current;
        CircularNode<T>* last = nullptr;

        do {
            swapped = false;
            current = head;

            // Проходим по списку до последнего отсортированного элемента
            while (current->next != head && current->next != last) {
                if (current->data > current->next->data) {
                    // Меняем данные, а не узлы (проще и быстрее)
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
            last = current;
        } while (swapped);
    }
};