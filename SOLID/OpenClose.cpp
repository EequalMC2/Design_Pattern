#include <boost/lexical_cast.hpp>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost;

//before open close prinsible
// enum class Color {
//     red,
//     green,
//     blue
// };
// enum class Size {
//     small,
//     medium,
//     large
// };

// class Product {
// public:
//     string name;
//     Color color;
//     Size size;
// };

// class ProductFilter {
// public:
//     vector<Product*> by_color(vector<Product*> product, Color color)
//     {
//         vector<Product*> result;
//         for (auto& i : product)
//             if (i->color == color)
//                 result.push_back(i);
//         return result;
//     }
// };

// int main()
// {
//     Product products[] = {
//     {"car", Color::blue, Size::medium},
//     {"pen", Color::blue, Size::small},
//     {"pillow",  Color::green, Size::small},
//     {"house", Color::red, Size::large}
//     };

//     vector<Product*> productVec;
//     for(auto& i : products)
//         productVec.push_back(&i);

//     ProductFilter filter;
//     auto  filteredProduct = filter.by_color(productVec, Color::blue);
//     for(const auto& i : filteredProduct)
//         std::cout << i->name << endl;

//     return 0;
// }

//after open close prinsible

enum class Color {
    red,
    green,
    blue
};
enum class Size {
    small,
    medium,
    large
};

class Product {
public:
    string name;
    Color color;
    Size size;
};

template <typename T>
class Spesification {
public:
    virtual bool isSatisfied(T* item) = 0;
};

template <typename T>
class Filter {
public:
    virtual vector<T*> filter(vector<T*> items, Spesification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
    vector<Product*> filter(vector<Product*> items, Spesification<Product>& spec) override
    {

        vector<Product*> result;
        for (const auto& i : items)
            if (spec.isSatisfied(i))
                result.push_back(i);
        return result;
    }
};

class ColorSpecification : public Spesification<Product> {
    Color color;

public:
    ColorSpecification(Color color)
        : color { color }
    {
    }
    bool isSatisfied(Product* item) override
    {
        return item->color == color;
    }
};

class SizeSpesification : public Spesification<Product> {
    Size size;

public:
    SizeSpesification(Size size)
        : size(size) {};
    bool isSatisfied(Product* item)
    {
        return item->size == size;
    }
};
template <typename T>
class AndSpesification : public Spesification<T> {
    Spesification<T>& first;
    Spesification<T>& secound;

public:
    AndSpesification(Spesification<T>& first, Spesification<T>& secound)
        : first(first)
        , secound(secound)
    {
    }
    bool isSatisfied(T* item) override
    {
        return (first.isSatisfied(item) && secound.isSatisfied(item));
    }
};

int main()
{

    Product products[] = {
        { "car", Color::blue, Size::medium },
        { "pen", Color::blue, Size::small },
        { "pillow", Color::green, Size::small },
        { "house", Color::green, Size::large }
    };

    vector<Product*> productVec;
    for (auto& i : products)
        productVec.push_back(&i);

    BetterFilter bf;
    ColorSpecification green(Color::green);
    SizeSpesification large(Size::large);
    AndSpesification<Product> greenAndLarge(green, large);

    cout << "green : " << endl;
    for (auto& i : bf.filter(productVec, green))
        cout << i->name << endl;

    cout << "large : " << endl;
    for (auto& i : bf.filter(productVec, large))
        cout << i->name << endl;

    cout << "large and green : " << endl;
    for (auto& i : bf.filter(productVec, greenAndLarge))
        cout << i->name << endl;

    return 0;
}
