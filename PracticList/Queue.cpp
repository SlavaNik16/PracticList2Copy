#include <iostream>
#include <fstream>
#include "ListNode.cpp"
using namespace std;

template <typename T>
class Queue {
private:
    ListNode<T>* front;  // начало очереди (для извлечения)
    ListNode<T>* rear;   // конец очереди (для добавления)
    int size;

public:
    // Конструкторы
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // Деструктор
    ~Queue() {
        clear();
    }

    void clear() {
        T dummy;
        while (tryDequeue(dummy)) {
            // Просто очищаем, значение нам не нужно
        }
    }

    // Добавление элемента в конец очереди
    void enqueue(T val) {
        auto* newNode = new ListNode<T>(val);

        if (isEmpty()) {
            // Если очередь пуста, новый элемент становится и началом и концом
            front = rear = newNode;
        }
        else {
            // Добавляем в конец
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        size++;
    }

    bool tryDequeue(T& value) {
        if (isEmpty()) {
            return false;
        }

        ListNode<T>* temp = front;
        value = temp->data;

        if (front == rear) {
            front = rear = nullptr;
        }
        else {
            front = front->next;
            front->prev = nullptr;
        }

        delete temp;
        size--;
        return true;
    }

    void load(const string& file) {
        ifstream f(file);
        if (!f) return;

        float word;
        while (f >> word) {
            enqueue(word);
        }
    }

    void show() {
        auto* cur = front;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }
};