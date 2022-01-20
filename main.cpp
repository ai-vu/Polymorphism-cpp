#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// class Point
class Point {
public:
    //constructor
    Point(double xcoord = 0.0, double ycoord = 0.0);
    // destructor
    virtual ~Point() = default;
    virtual void input(const char* prompt);
    virtual void output() const;
    float getx() const;
    float gety() const;
    virtual double area() const;
    void move(double deltax, double deltay);
private:
    double x;
    double y;
};

Point::Point(double xcoord, double ycoord) {
    x = xcoord;
    y = ycoord;
}

void Point::input(const char *prompt) {
    cout << prompt << endl;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
}

void Point::output() const {
    cout << "Coordinate: (" << x << "," << y << ")";
}

double Point::area() const {
    return 0.0;
}

void Point::move(double deltax, double deltay) {
    x += deltax;
    y += deltay;
}

float Point::getx() const {
    return x;
}

float Point::gety() const {
    return y;
}

/*
 * class Circle derived from class Point
 * add radius
 * virtual functions and define constructors
 * take 2 – 4 values as parameter
 * all parameters must have a default value
 */
class Circle: public Point {
public:
    Circle(float cx = 0.0, float cy = 0.0, float r = 1.0);
    virtual void input(const char* prompt) override;
    virtual void output() const override;
    virtual double area() const override;
    float radius() const;
private:
    float rad;
};

Circle::Circle(float cx, float cy, float r): Point(cx, cy), rad(r){ }

void Circle::input(const char *prompt) {
    cout << prompt;
    Point::input("\nEnter the center point");
    cout << "Enter radius: ";
    cin >> rad;
}

void Circle::output() const {
    Point::output();
    cout << "\nRadius r = " << rad;
}

double Circle::area() const {
    double c_a;
    const float pi = 3.14159f;
    c_a = rad * rad * pi;
    return c_a;
}

float Circle::radius() const {
    return rad;
}

/*
 * class Square derived from class Point
 * add width and height
 * virtual functions and define constructors
 * take 2 – 4 values as parameter
 * all parameters must have a default value
 */
class Square: public Point {
public:
    Square(float sx = 0.0, float sy = 0.0, float h_w = 1.0);
    virtual void input(const char* prompt) override;
    virtual void output() const override;
    virtual double area() const override;
    float height_width() const;
private:
    float het_wid;
};

Square::Square(float sx, float sy, float h_w): Point(sx, sy), het_wid(h_w) { }

void Square::input(const char *prompt) {
    cout << prompt;
    Point::input("\nEnter coordinate for the square");
    cout << "Enter height (width): ";
    cin >> het_wid;
}

void Square::output() const {
    Point::output();
    cout << "\nHeight and Width hw = " << het_wid;
}

double Square::area() const {
    double s_a;
    s_a = het_wid * het_wid;
    return s_a;
}

float Square::height_width() const {
    return het_wid;
}

/*
 * defines a vector of shared pointers to the base class
 * objects put into the vector:
 * Point with coordinates (1.0, 1.0)
 * Circle at (2.0, 2.0) with radius 2.0
 * Square at (5.0, 5.0) with width and height of 2.0
 * Square, Circle & Point data are asked from user
 * print object data
 * sort vector by area
 * print object data
 */

int main() {
    cout << "Basic Maths time!" << endl;
    Point p1, p2(1.0, 1.0);
    Circle c1, c2(2.0, 2.0, 2.0);
    Square s1,s2(5.0, 5.0, 2.0);
    vector<shared_ptr<Point>> v;

    p1.input("\nPoint");
    p1.output();
    c1.input("\n\nCircle");
    c1.output();
    s1.input("\n\nSquare");
    s1.output();

    v.push_back(make_shared<Point>(p1.getx(), p1.gety()));
    v.push_back(make_shared<Point>(p2.getx(), p2.gety()));
    v.push_back(make_shared<Circle>(c1.getx(), c1.gety(), c1.radius()));
    v.push_back(make_shared<Circle>(c2.getx(), c2.gety(), c2.radius()));
    v.push_back(make_shared<Square>(s1.getx(),s1.gety(), s1.height_width()));
    v.push_back(make_shared<Square>(s2.getx(),s2.gety(), s2.height_width()));

    cout << "\n\nPoint 1 (" << v[0]->getx() << "," << v[0]->gety() << ")";
    cout << "\nPoint 2 (" << v[1]->getx() << "," << v[1]->gety() << ")";
    cout << "\nCircle 1 has center point ("
         << v[2]->getx() << "," << v[2]->gety() << ") and area = " << v[2]->area();
    cout << "\nCircle 2 has center point ("
    << v[3]->getx() << "," << v[3]->gety() << ") and area = " << v[3]->area();
    cout << "\nSquare 1 has point ("
         << v[4]->getx() << "," << v[4]->gety() << ") and area = " << v[4]->area();
    cout << "\nSquare 2 has point ("
         << v[5]->getx() << "," << v[5]->gety() << ") and area = " << v[5]->area();

    // sort from smaller to bigger
    auto sortingLambda =  [](shared_ptr<Point>& a, shared_ptr<Point>& b)
    {
        return a->area() < b->area();
    };
    sort(begin(v), end(v), sortingLambda);
    cout << "\n\nArea from small to big\n";
    for (int i = 0; i < 6; ++i)
        cout << v[i] -> area() << " ";

    return 0;
}
