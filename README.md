# Лабораторная работа №4: Односвязный список

## 🎯 Цель работы
1. Реализовать шаблонный класс односвязного списка (`SinglyLinkedList`) с базовыми операциями.
2. Освоить операции вставки, удаления, поиска и обхода элементов в списках.
3. Научиться правильно управлять памятью при работе со списками (удаление узлов).
4. Проанализировать сложность основных операций.

## 📋 Вариант задания
**Базовый уровень, Вариант №4**
*   **Обязательные методы:** `push_front`, `pop_front`, `find`, `print`.
*   **Дополнительное задание:** Найти минимальный элемент в списке.

## 📚 Теоретическая часть
*   **Связный список** — структура данных, где элементы (узлы) хранятся в памяти не непрерывно. Каждый узел содержит данные и указатель на следующий узел.
*   **Односвязный список** позволяет двигаться только в одном направлении (от начала к концу). Для быстрой вставки в конец обычно хранится указатель `tail`.
*   В отличие от массива, вставка и удаление в начале списка занимают `O(1)`, так как не требуется сдвигать все элементы.

## 💻 Листинг программы (main.cpp)

```cpp
#include <iostream>
#include <stdexcept>
#include <limits> // для std::numeric_limits

using namespace std;

// ==========================================
// Класс Односвязного списка
// ==========================================
template <typename T>
class SinglyLinkedList {
private:
    // Внутренняя структура узла
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head; // Указатель на первый элемент
    Node* tail; // Указатель на последний элемент (для быстрой вставки в конец)
    int count;  // Количество элементов

public:
    // Конструктор по умолчанию
    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    // Деструктор (освобождение памяти)
    ~SinglyLinkedList() {
        clear();
    }

    // Вставка в начало списка O(1)
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
        count++;
    }

    // Удаление из начала списка O(1)
    void pop_front() {
        if (head == nullptr) {
            throw underflow_error("Список пуст (pop_front)");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    // Поиск элемента по значению O(n)
    // Возвращает true, если элемент найден, иначе false
    bool find(const T& value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Дополнительное задание: Найти минимальный элемент O(n)
    T getMin() const {
        if (head == nullptr) {
            throw underflow_error("Список пуст (getMin)");
        }
        T minVal = head->data;
        Node* current = head->next;
        while (current != nullptr) {
            if (current->data < minVal) {
                minVal = current->data;
            }
            current = current->next;
        }
        return minVal;
    }

    // Вывод списка O(n)
    void print() const {
        Node* current = head;
        cout << "[";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << ", ";
            }
            current = current->next;
        }
        cout << "]" << endl;
    }

    // Очистка списка O(n)
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    // Вспомогательные методы
    int size() const { return count; }
    bool empty() const { return head == nullptr; }
};

// ==========================================
// Главная функция (Демонстрация)
// ==========================================
int main() {
    setlocale(LC_ALL, "ru");

    cout << "--- Демонстрация Односвязного списка (Вариант 4) ---" << endl;
    
    SinglyLinkedList<int> list;

    cout << "\n1. Добавление элементов через push_front:" << endl;
    list.push_front(50);
    list.push_front(20);
    list.push_front(80);
    list.push_front(10);
    cout << "Список: ";
    list.print(); // Ожидается: [10, 80, 20, 50]
    cout << "Текущий размер: " << list.size() << endl;

    cout << "\n2. Поиск элементов (метод find):" << endl;
    cout << "Есть ли число 20 в списке? " << (list.find(20) ? "Да" : "Нет") << endl;
    cout << "Есть ли число 99 в списке? " << (list.find(99) ? "Да" : "Нет") << endl;

    cout << "\n3. Поиск минимального элемента (доп. задание):" << endl;
    cout << "Минимальный элемент: " << list.getMin() << endl;

    cout << "\n4. Удаление из начала (pop_front):" << endl;
    list.pop_front();
    cout << "После pop_front список: ";
    list.print(); // Ожидается: [80, 20, 50]

    list.pop_front();
    cout << "После еще одного pop_front: ";
    list.print(); // Ожидается: [20, 50]

    cout << "\n5. Очистка списка и проверка работы с пустым списком:" << endl;
    list.clear();
    cout << "Список после очистки: ";
    list.print();
    cout << "Размер: " << list.size() << endl;

    try {
        list.pop_front();
    } catch (const exception& e) {
        cout << "Исключение при pop_front: " << e.what() << endl;
    }

    try {
        list.getMin();
    } catch (const exception& e) {
        cout << "Исключение при getMin: " << e.what() << endl;
    }

    cout << "\n--- Конец программы ---" << endl;
    return 0;
}
