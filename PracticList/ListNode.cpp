#ifndef LIST_NODE_CPP
#define LIST_NODE_CPP

// Базовый класс для узла списка
template <typename T>
class ListNode {
public:
    //Поле для хранения данных узла
    T data;

    ListNode* prev; // Указатель на предыдущий список
    ListNode* next; // Указатель на следующий список

    //Конструктор
    ListNode(const T& data) : data(data), prev(nullptr), next(nullptr) {}

    // Виртуальный деструктор, для правильного освобождения ресурсов
    virtual ~ListNode() {}
};
#endif
