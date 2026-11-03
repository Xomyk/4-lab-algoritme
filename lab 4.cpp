#include <iostream>
#include <stdexcept>
#include <limits> // для std::numeric_limits

using namespace std;
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