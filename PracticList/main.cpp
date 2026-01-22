#include <iostream>
#include <fstream>
#include "Queue.cpp"
#include "CircularLinkedList.cpp"
using namespace std;

// Практическая работа №3, вариант 3
// Задание: Загрузить из файла вещественные числа в Очередь Двунаправленного списка, 
// потом разложить числа в диапазоне в кольцевой список, упорядочив их по возрастанию.
// Итоговый результат загрузить в новый файл.
// Автор: Бажин К.А., группа: 4335
// Дата: [22.01.2026]

void clearInputBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}

int main() {
    setlocale(LC_ALL, "rus");

    Queue<float> list;
    cout << "Читаем данные из файла...";
    list.load("input.txt");

    if (list.isEmpty()) {
        cout << "\nВещественных данных в файле нет!";
        return 0;
    }

    float from = 0.0, to = -1.0;
    int fromMin = -500, toMax = 500; 
   
    while (from > to) {
        cout << "\nВведите диапазон значений [-500;500]: \n";

        cout << "От: ";
        cin >> from;
        if (cin.fail() || from < fromMin) {
            clearInputBuffer();
            from = fromMin;
            to = fromMin - 1; 
            continue;
        }

        cout << "До: ";
        cin >> to;
        if (cin.fail() || to > toMax) {
            clearInputBuffer();
            to = fromMin - 1;
            continue;
        }

        if (from > to) {
            cout << "Ошибка: начало диапазона должно быть меньше или равно концу!" << endl;
        }
    }

    cout << "\nИзначальные данные из файла: ";
    list.show();
    cout << "\n";

    CircularLinkedList<float> circle;

    float value;
    while (list.tryDequeue(value)) {
        if (value >= from && value <= to) {
            circle.add(value);
        }
    }

    cout << "Внутри диапозона числа: ";
    circle.show();

    circle.sort();

    cout << "\nВнутри диапозона числа (Сортировка по возврастанию): ";
    circle.show();

    cout << "\nПишем данные в файл...";
    ofstream out("output.txt");
    circle.save(out);
    out << "\nТекущий диапазон: ["<<from << "," << to << "] ";
    out.close();

    cout << "\nУспешно сохранено в файл!" << endl;

    return 0;
}
