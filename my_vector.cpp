// C++ program to implement Custom Vector
// class
#include <iostream>
#include <cstring>
#include <time.h>
using namespace std;

namespace Mylib {
    template<typename T>
    class Vector {
    private:
        size_t cap;
        size_t sz;
        T *arr;

        void ensureCap() {
            cap = std::max(size_t (1), cap << 1);
            T *buf = new T[cap];
            // void * memcpy ( void * destination, const void * source, size_t num );
            memcpy(buf, arr, sz * sizeof(T));
            if (arr != nullptr)
                delete[] arr;
            arr = buf;
        }


    public:
        Vector();

        Vector(size_t capacity);

        size_t capacity() {
            return cap;
        }

        Vector(const Vector<T> &source);

        Vector(Vector<T> &&source);

        T& operator[](size_t index);

        void push_back(T elem);

        template<typename ...Args>
        void emplace_back(Args... args);

        void pop_back();

        size_t size();

        ~Vector();
    };

    template<typename T>
    Vector<T>::Vector() {
        cap = 8;
        sz = 0;
        arr = new T[cap];
    }

    template<typename T>
    Vector<T>::Vector(size_t capacity) {
        if (!capacity) {
            Vector();
        }
        cap = capacity;
        arr = new T[cap];
        sz = 0;
    }

    template<typename T>
    Vector<T>::Vector(const Vector<T> &source) {
        cap = source.cap;
        arr = new T[cap];
        sz = source.sz;
        for (int i = 0; i < sz; i++) {
            arr[i] = source.arr[i];
        }
    }

    template<typename T>
    Vector<T>::Vector(Vector<T> &&source) {
        cap = source.cap;
        arr = source.arr;
        sz = source.sz;
        source.cap = 0;
        source.sz = 0;
        source.arr = nullptr;
    }

    template<typename T>
    T &Vector<T>::operator[](size_t index) {
        if (index >= sz) {
            std::cout << "Index Error: " << index << " is  out of range of " << sz << std::endl;
            exit(-1);
        }
        return arr[index];
    }

    template<typename T>
    void Vector<T>::push_back(T elem) {
        if (cap == sz) {
            ensureCap();
        }
        arr[sz++] = elem;
    }

    template<typename T>
    void Vector<T>::pop_back() {
        if (!sz) {
            cout << "Error popping from an empty vector" << endl;
            exit(1);
        }
        sz--;
    }

    template<typename T>
    size_t Vector<T>::size() {
        return sz;
    }



    template<typename T>
    Vector<T>::~Vector() {
        delete[] arr;
        sz = 0;
        cap = 0;
        arr = nullptr;
    }

    template<typename T>
    template<typename... Args>
    void Vector<T>::emplace_back(Args... args) {
        // TODO
        ensureCap();
        // plasement new : expr new (addr) T(std::)
        // xx(C&& a) {
        //   A(a);
        // }
        // A(C&)
        // A(C&&)
        //
        new (&arr[sz++]) T(std::forward<Args>(args)...);
    }

}

// #include "assert.h
// void assert( int expression );
void TestVector() {
    Mylib::Vector<int> v1(1);
    for (int i = 0; i < 10000; i++) {
        v1.push_back(i);
//        std::printf("pushing back %d, size: %zu, cap: %zu\n", i, v1.size(), v1.capacity());
    }
    for (int i = 0; i < 10000; i++) {
        assert(v1[i] == i);
    }
}

void Timer(std::function<void()> fn, int times) {
    clock_t tStart = clock(); // 50~80 nano seconds
    for (int i = 0; i < times; i++) {
        fn();
    }
    printf("Time taken: %.3fms\n", (double)(clock() - tStart)/CLOCKS_PER_SEC * 1000);
}


//int main(){
//    Timer(TestVector, 10000);
//    return 0;
//}