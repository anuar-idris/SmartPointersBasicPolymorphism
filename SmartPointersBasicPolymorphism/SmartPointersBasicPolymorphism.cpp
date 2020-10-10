// SmartPointersBasicPolymorphism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <vector>

class Base
{
public:

    virtual void SayHello()
    {
        std::cout << "Hello from Base.\n";
    }

};

class Derived : public Base
{
public:
    void SayHello() override
    {
        std::cout << "Hello from Derived.\n";
    }
};

//Class to hold container
class MyCompositeClass {

public:
    MyCompositeClass(std::initializer_list<int> init_list) :
        m_Vec(init_list.begin(), init_list.end()),
        m_size(m_Vec.size()) 
    { 
    
    }

    void Movement()
    {
        for (auto itm : m_Vec) {
            std::cout << "Got item: " << itm << "\n";
        }    
    }

    void DeleteVector()
    {
        m_Vec.clear();
    }

private:
    std::vector<int> m_Vec;
    int m_size;
};

int main()
{
    std::cout << "Hello World!\n";

    auto pBase = std::make_shared<Base>();
    pBase->SayHello();

    auto pDerived = std::make_shared<Derived>();
    pDerived->SayHello();



    // static_pointer_cast to go up class hierarchy
    pBase = std::static_pointer_cast<Base>(pDerived);
    pBase->SayHello();

    // dynamic_pointer_cast to go down/across class hierarchy
    auto newdowncastedPtr = std::dynamic_pointer_cast<Derived>(pBase);
    if (newdowncastedPtr)
    {
        std::cout << "Downcasted pointer says: ";
        newdowncastedPtr->SayHello();
    }

    // All pointers to derived share ownership
    std::cout << "Pointers to underlying derived: "
        << pDerived.use_count()
        << "\n";

    MyCompositeClass m = { 1,2,3,4 };
    m.Movement();
    m.DeleteVector();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
