#include <iostream>
#include <vector>

using namespace std;
//before liskkov Substitution principle
// class Rectangle {
// protected:
//     int width, height;

// public:
//     Rectangle(int width, int heigth)
//         : width(width)
//         , height(heigth)
//     {
//     }
//     virtual void setWidth(int width)
//     {
//         this->width = width;
//     }
//     int getWidth() const
//     {
//         return width;
//     }
//     virtual void setHeigth(int height)
//     {
//         this->height = height;
//     }
//     int getHeigth() const
//     {
//         return height;
//     }

//     int area() const
//     {
//         return width * height;
//     }
// };

// class Square : public Rectangle {
// public:
//     Square(int size)
//         : Rectangle(size, size)
//     {
//     }

//     void setHeigth(int size) override
//     {
//         this->height= this->width = size;
//     }

//     void setWidth(int size) override
//     {
//         setHeigth(size);
//     }
// };

// void process(Rectangle& r)
// {
//     int w = r.getWidth();
//     r.setHeigth(10);
//     cout << "expected area  = " << 10 * w << ", got = " << r.area() << "\n";
// }

// int main()
// {
//     Rectangle rectangle { 50, 10 };
//     Square square { 30 };
//     process(rectangle);
//     process(square);
// }

//After Linkov Substitution princible

class Rectangle {
protected:
    int width, height;
    bool isSquarFlag = false;

public:
    Rectangle(int width, int heigth)
        : width(width)
        , height(heigth)
    {
    }
    virtual void setWidth(int width)
    {
        this->width = width;
    }
    int getWidth() const
    {
        return width;
    }
    virtual void setHeigth(int height)
    {
        this->height = height;
    }
    int getHeigth() const
    {
        return height;
    }

    int area() const
    {
        return width * height;
    }
    bool isSquar() const { return isSquarFlag; }
};

class Square : public Rectangle {
public:
    Square(int size)
        : Rectangle(size, size)
    {
        isSquarFlag = true;
    }

    void setHeigth(int size) override
    {
        this->height = this->width = size;
    }

    void setWidth(int size) override
    {
        setHeigth(size);
    }
};

void process(Rectangle& r)
{
    if (r.isSquar())
        return;

    int w = r.getWidth();
    r.setHeigth(10);
    cout << "expected area  = " << 10 * w << ", got = " << r.area() << "\n";
}

int main()
{
    Rectangle rectangle { 50, 10 };
    Square square { 30 };
    process(rectangle);
    process(square);
}
