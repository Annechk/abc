#include <iostream>
using namespace

class Base{
private:
    int value;
public:
    Base(int v) {
        value = v;
        cout << "Конструктор Base, значение = " << value << endl;
    }
    ~Base() {
        cout << "Деструктор Base" << endl;
    }
};

class Derived : public Base {
private:
    int extra;
public:
    Derived(int v, int e) : Base(v) {
        extra = e;
        cout << "Конструктор Derived, extra = " << extra << endl;
    }
    void greet(){
        cout << "Derived" << endl;
    }

    ~Derived() {
        cout << "Деструктор Derived" << endl;
        a ->greet();
        delete a;
    }
};

int main()
{
    Base* a - new Derived(10,20)
}
