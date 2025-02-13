#include <iostream>

class Point
{
    private:
        double x_, y_;
    public:
        Point() { x_ = 0.0; y_ = 0.0; }
        Point(double x, double y) { x_ = x; y_ = y; }

        void setX(double x) { x_ = x; }
        void setY(double y) { y_ = y; }
        double getX() { return x_; }
        double getY() { return y_; }
};


int main() {
    Point obj;
    obj.setX(1.0);
    obj.setY(2.0);

    Point* pObj = new Point;
    pObj->setX(3.0);
    pObj->setY(4.0);

    Point obj1(3.0, 4.0);
    std::cout << obj1.getX() << " " << obj1.getY() << std::endl;
    return 0;
}
