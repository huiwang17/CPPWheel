#include <iostream>

namespace Mylib {

    class Point {
    private:
        int x;
        int y;

    public:
        // default
        Point();

        // constructor with 2 arguments
        Point(int, int);

        // copy constructor
        Point(const Point &source);

        // move constructor
        Point(Point &&source);

        // overloading operate
        friend std::ostream &operator<<(std::ostream &out, const Point &p) {
            char buff[50];
            std::sprintf(buff, "(%d, %d)", p.x, p.y);
            out << buff;
            return out;
        }

        // overloading operator =
        Point &operator=(const Point &source);

        // overloading operator +
        Point &operator+(const Point &rhs);

        // overloading operator -

        friend Point operator-(const Point &lhs, const Point &rhs);
        // a -= b

//        Point& operator-(const Point& rhs);
    };

    Point::Point() : x(0), y(0) {}

    Point::Point(int a, int b) : x(a), y(b) {}

    Point::Point(const Point &source) : x(source.x), y(source.y) {}

    Point::Point(Point &&source) : x(source.x), y(source.y) {
        source.x = 0;
        source.y = 0;
    }

    Point &Point::operator=(const Point &source) {
        if (this == &source)
            return *this;
        x = source.x;
        y = source.y;
        return *this;
    }

    Point &Point::operator+(const Point &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    // Point
    // Point&
    // Point&, Point -> ignore memory, error -> new
    // Point* -> &
    Point operator-(const Point &lhs, const Point &rhs) {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    class Shape {
    private:
        unsigned id;
        double area;
    public:
        virtual double CalcArea() {
            return area;
        }
    };

    // minimum access right from shape and access right from inheritance method?
    class Circle : public Shape {
    public:
        double CalcArea() override {
            return 0.1f;
        }
    };


}

void TestPoint() {
    auto p1 = Mylib::Point();
    std::cout << p1 << std::endl;
    auto p2 = Mylib::Point(1, 1);
    auto p3 = Mylib::Point(2, 3);
    auto p4(std::move(p3));
    std::cout << "p3: " << p3 << std::endl;
    std::cout << p2 - p4 << std::endl;
}

//int main() {
//    TestPoint();
//    return 0;
//}