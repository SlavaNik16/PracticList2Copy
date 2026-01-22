#ifndef CIRCUKAR_NODE_CPP
#define CIRCUKAR_NODE_CPP

// Базовый класс для узла списка
template <typename T>
class CircularNode {
public:
    //Поле для хранения данных узла
    T data;

    CircularNode* next; // Указатель на следующий список

    //Конструктор
    CircularNode(const T& data) : data(data), next(nullptr) {}

    // Виртуальный деструктор, для правильного освобождения ресурсов
    virtual ~CircularNode() {}
};
#endif
