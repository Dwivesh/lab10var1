#include <iostream>

template <class T> //при создании экземпляра класса Т заменится и будет нужного в коде формата очередь(бул и чар проверить)
class MyPriorityQueue {
private://в привате стр-ра для элем-в очереди: дата для хранения значения, приор для приоритета. некст след эл-т, хед - начало
    struct Node { 
        T data;
        int priority;
        Node* next;
    };

    Node* head;

public:
    MyPriorityQueue() : head(nullptr) {} //конструктор класса, инициализирует указатель на голову очереди как nullptr

    void push(const T& item, int priority) {
        Node* newNode = new Node{ item, priority, nullptr }; //созд-е нового узла с передаваемыми данными и приоритетом

        if ((!head) || (priority > head->priority)) { //если новый элемент имеет приоритет выше(или очередь пуста), то вставим новый в голову очереди
            newNode->next = head; //-> - это оператор доступа к члену структуры или класса через указатель
            head = newNode;
        }
        else {//иначе вставляем новый элемент с учетом приоритета
            Node* a = head;
            while ((a->next) && (priority <= a->next->priority)) {
                a = a->next;
            }
            newNode->next = a->next;
            a->next = newNode;
        }
    }

    void pop() {
        if (head) { //я не поняла что конкретно нужно попытить поэтому поп удаляет элемент с наивысшим приоритетом т е первый в очереди
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    T peek() { //возвращает первый в очереди элемент, но не удаляет его !проверить бул и чар
        if (head) {
            return head->data;
        }
        else {
            throw std::out_of_range("MyPriorityQueue is empty"); //выброс исключения, трай кэтч(?)
        }
    }

    size_t size() { //возвращает количество элементов в очереди
        size_t cont = 0;
        Node* i = head;
        while (i) {
            cont++;
            i = i->next;
        }
        return cont;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyPriorityQueue<T>& MPQ) {//вывод в поток
        Node* potok = MPQ.head;
        while (potok) {
            os << potok->data << " ";
            potok = potok->next;
        }
        return os;
    }

    ~MyPriorityQueue(){ //деструктор
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    MyPriorityQueue<int> Queue1;
    int attr = 2, QuElPr = 0, ElTy = 0;
    std::cout << "If you want to add an element enter 1, else enter 0" << std::endl;    
    std::cin >> attr;
    while (attr) {
        std::cout << "Enter prioritet of an element." << std::endl;
        std::cin >> QuElPr;
        std::cout << "Enter the number of the required data type for the element" << std::endl;
        std::cout << "1 - int   2 - char   3 - bool   4 - double" << std::endl;
        std::cin >> ElTy;
        if (ElTy == 1) {
            int number;
            std::cout << "Enter an integer: " << std::endl;
            std::cin >> number;
            Queue1.push(number, QuElPr);
        }
        else if (ElTy == 4) {
            double dr;
            std::cout << "Enter a double: " << std::endl;
            std::cin >> dr;
            Queue1.push(dr, QuElPr);
        }
        else if (ElTy == 2) {
            char symb;
            std::cout << "Enter a char: " << std::endl;
            std::cin >> symb;
            Queue1.push(symb, QuElPr);
        }
        else if (ElTy == 3) {
            bool usl;
            std::cout << "Enter a bool: " << std::endl;
            std::cin >> usl;
            Queue1.push(usl, QuElPr);
        }
        std::cout << "If you want to add an element enter 1, else enter 0" << std::endl;
        std::cin >> attr;
    }

    std::cout << "Priority Queue: " << Queue1 << std::endl;
    std::cout << "Size: " << Queue1.size() << std::endl;
    std::cout << "Peek: " << Queue1.peek() << std::endl;

    Queue1.pop();
    std::cout << "!We made a pop! " << std::endl;
    std::cout << "Priority Queue: " << Queue1 << std::endl;
    std::cout << "Size: " << Queue1.size() << std::endl;
    std::cout << "Peek: " << Queue1.peek() << std::endl;


    return 0;
}