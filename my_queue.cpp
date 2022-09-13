#include <iostream>

namespace Mylib {

    template<typename T>
    class Node {
    public:
        T elem;
        Node* next;

        Node(T t) : elem(t), next(nullptr){};
        Node(T t, Node* p): elem(t), next(p){};
    };

    template<typename T>
    class Queue {
    private:
        // dummy head
        Node<T>* head;
        Node<T>* tail;
        size_t sz;

    public:
        // default constructor
        Queue();

        // Copy constructor
        Queue(const Queue<T> &source);

        // Move constructor
        Queue(Queue<T> &&source);

        void push(const T &elem);

        void pop();

        T front();

        size_t size();

        // Destructor
        ~Queue();
    };

    template<typename T>
    Queue<T>::Queue() {
        head = new Node<T>(T(), nullptr);
        tail = head;
        sz = 0;
    }


    template<typename T>
    Queue<T>::Queue(const Queue<T> &source) {
        head = new Node<T>;
        auto p = head;
        auto q = source.head->next;
        int len = source.sz;
        for (int i = 0; i < len; i++) {
            p->next = new Node<T>(q->elem);
            p = p->next;
            q = q->next;
        }
        sz = source.sz;
    }

    template<typename T>
    Queue<T>::Queue(Queue<T> &&source) {
        sz = source.sz;
        head = source.head;
        tail = source.tail;
        source.head = new Node<T>;
        source.tail = source.head;
        source.sz = 0;
    }

    template<typename T>
    size_t Queue<T>::size() {
        return sz;
    }


    template<typename T>
    void Queue<T>::push(const T &elem) {
        tail->next = new Node<T>(elem, nullptr);
        tail = tail->next;
        sz++;
    }

    template<typename T>
    void Queue<T>::pop() {
        if (!sz) {
            std::cout << "popping from an empty queue" << std::endl;
            exit(-1);
        }
        auto toDelete = head->next;
        head->next = head->next->next;
        delete toDelete;
    }

    template<typename T>
    Queue<T>::~Queue() {
        Node<T>* p = head;
        while (p != nullptr) {
            auto toDelte = p;
            p = p->next;
            delete toDelte;
        }
    }

    template<typename T>
    T Queue<T>::front() {
        if (!sz) {
            std::cout << "peeking into an empty queue" << std::endl;
            exit(-1);
        }
        return head->next->elem;
    }


}

int main() {
    Mylib::Queue<int> q;
    for (int i = 0; i < 10; i++) {
        q.push(i+1);
        printf("adding %d\n", i+1);
        std::cout << q.size() << std::endl;
    }

    for (int i = 0; i < 10; i++) {
        printf("front elem is %d\n", q.front());
        q.pop();
    }
    q.pop();
}