#include <cstring>
#include <iostream>

// 使用自定义namespace防止作用域污染 (namespace pollution)
namespace Mylib {

    class Mystring {

    private:
        char *str;

        // Prototype for stream insertion
        // TODO：声明友元函数，使得这个函数可以访问Mystring中所有成员变量
        friend std::ostream &operator<<(std::ostream &os, const Mystring &obj) {
            os << obj.str;
            return os;
        }

        // Prototype for stream extraction
        friend std::istream &operator>>(std::istream &is, Mystring &obj) {
            char *buff = new char[1000];
            memset(&buff[0], 0, sizeof(buff));
            is >> buff;
            obj = Mystring{buff};
            delete[] buff;
            return is;
        }

        // Prototype for '+'
        // operator overloading
        friend Mystring operator+(const Mystring &lhs, const Mystring &rhs) {
            int length = strlen(lhs.str) + strlen(rhs.str);
            char *buff = new char[length + 1];

            // Copy the strings to buff[]
            strcpy(buff, lhs.str);
            strcat(buff, rhs.str);
            buff[length] = '\0';

            // String temp
            Mystring temp = buff;

            // delete the buff[]
            delete[] buff;

            // Return the concatenated string
            return temp;
        }


    public:
        // No arguments constructor
        Mystring() : str(nullptr) {
            str = new char[1];
            str[0] = '\0';
        }

        // pop_back() function
        void pop_bk() {
            int length = strlen(str);
            char *buff = new char[length];

            // Copy character from str
            // to buff[]
            for (int i = 0; i < length - 1; i++)
                buff[i] = str[i];
            buff[length - 1] = '\0';

            // Assign the new string with
            // char a to string str
            *this = Mystring{buff};

            // delete the buff[]
            delete[] buff;
        }

        // push_back() function
        void push_bk(char a) {
            // Find length of string
            int length = strlen(str);

            char *buff = new char[length + 2];

            // Copy character from str
            // to buff[]
            for (int i = 0; i < length; i++) {
                buff[i] = str[i];
            }
            buff[length] = a;
            buff[length + 1] = '\0';

            // Assign the new string with
            // char a to string str
            *this = Mystring{buff};

            // Delete the temp buff[]
            delete[] buff;
        }

        // To get the length
        size_t size() { return strlen(str); }

        size_t length() { return size(); }

        // Function to copy the string
        // of length len from position pos
        void copy(char s[], int len, int pos) {
            for (int i = 0; i < len; i++) {
                s[i] = str[pos + i];
            }
            s[len] = '\0';
        }

        // Swap strings function
        void swap(Mystring &rhs) {
            Mystring temp{rhs};
            rhs = *this;
            *this = temp;
        }

        // char * s = "abc"
        // auto str = Mystring(s)
        // 这里是构造函数，没有必要检查str 空指针
        Mystring(char *val) {
            int len = strlen(val);
            char *buf = new char[len + 1];
            strcpy(buf, val);
            str = buf;
        }

        // Copy Constructor
        Mystring(const Mystring &source) {
            int len = strlen(source.str);
            char *buf = new char[len + 1];
            strcpy(buf, source.str);
            str = buf;
        }

        // Move Constructor
        Mystring(Mystring &&source) {
            std::swap(str, source.str);
            source.str = nullptr;
        }

        // Overloading
        Mystring &operator=(const Mystring &source) {
            if (this == &source) {
                return *this;
            }
            int len = strlen(source.str);
            char *buf = new char[len + 1];
            strcpy(buf, source.str);
            char *toDelete = str;
            str = buf;
            if (toDelete != nullptr) {
                delete[] toDelete;
            }
            return *this;
        }

        // Destructor
        ~Mystring() {
            if (str != nullptr) {
                delete[] str;
            }
        }

    };

// Driver Code
    void test_mystring() {
        // Constructor with no arguments
        Mystring a;

        std::cout << "Mystring b: " << std::endl;

        // Convert string literal to
        // char array
        char temp[] = "Hello";

        // Constructor with one argument
        Mystring b{temp};

        // Copy constructor
        Mystring c{a};

        char temp1[] = "World";

        // One arg constructor called,
        // then the move constructor
        Mystring d{Mystring{temp}};

        // Remove last character from
        // Mystring b
        b.pop_bk();

        // Print string b

        std::cout << "Mystring b: " << b << std::endl;

        // Append last character from
        // Mystring b
        b.push_bk('o');

        // Print string b
        std::cout << "Mystring b: " << b << std::endl;

        // Print length of string b
        std::cout << "Length of Mystring b: " << b << std::endl;

        char arr[80];

        // Copy string b chars from
        // length 0 to 3
        b.copy(arr, 3, 0);

        // Print string arr
        std::cout << "arr is: " << arr << std::endl;

        // Swap d and b
        d.swap(b);

        // Print d and b
        std::cout << d << " " << b << std::endl;

        // Concatenate b and b with
        // overloading '+' operator
        d = b + b;

        // Print string d
        std::cout << "string d: " << d << std::endl;

        return;
    }

} // namespace Mylib

//int main() { Mylib::test_mystring(); }