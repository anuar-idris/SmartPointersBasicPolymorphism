// SmartPointersBasicPolymorphism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <vector>

//Animal class is an interface
class Animal
{
public:

    virtual void SayHello() = 0;

    virtual ~Animal()
    {
        std::cout << "Destructor from Animal.\n";
    }
};

class Rabbit : public Animal
{
public:
    void SayHello() override
    {
        std::cout << "Hello from Rabbit.\n";
    }

    virtual ~Rabbit()
    {
        std::cout << "Destructor from Rabbit.\n";
    }
};

class Cat : public Animal
{
public:
    void SayHello() override
    {
        std::cout << "Hello from Cat.\n";
    }

    virtual ~Cat()
    {
        std::cout << "Destructor from Cat.\n";
    }
};

//Class to hold container
class MyCompositeClass {

private:
    //This vector accepts pointer type of Animal class
    std::vector < std::shared_ptr<Animal>> m_Vec;
    int m_size;

public:
    MyCompositeClass() = default;
    MyCompositeClass(const MyCompositeClass&) = delete;
    MyCompositeClass(MyCompositeClass&&) = delete;
    MyCompositeClass& operator=(const MyCompositeClass&) = delete;
    MyCompositeClass& operator=(MyCompositeClass&&) = delete;

    virtual ~MyCompositeClass()
    {
        DeleteVector();
    }

    void DeleteVector()
    {
        //iterate all item inside vector and delete the pointer
        std::cout << "DeleteVector.\n";
        m_Vec.clear();
    }

    void SayHello()
    {
        for (auto& itm : m_Vec) {
            itm->SayHello();
        }
    }

    void AnotherSharedPointer()
    {
        //declared a shared pointer
        std::shared_ptr<Animal> ptrDerive(new Rabbit());

        //create a vector to hold the shared pointer
        std::vector<std::shared_ptr<Animal> > test;

        //move/cut and paste shared pointer to the vector
        //using std::move will take out pointer from source but retain and destination
        test.push_back(std::move(ptrDerive));

        //handle the shared pointer
        for (auto& itm : test) {
            itm->SayHello();
        }

        //delete the vector, will delete the pointer a well
        test.clear();
    }

    void run()
    {
        //create smart pointers Animald on derive class
        auto pRabbit = std::make_shared<Rabbit>();
        auto pCat = std::make_shared<Cat>();

        //Store those smart pointers in the vector of shared pointers
        //the same like copy pointers, not cut and paste
        m_Vec.push_back(pRabbit);
        m_Vec.push_back(pCat);

        // All pointers to Rabbit share ownership
        std::cout << "Pointers to underlying Rabbit: "
            << pRabbit.use_count()
            << "\n";

        SayHello();
    }
};

int main()
{
    std::cout << "Hello World!\n";

    MyCompositeClass mc;
    mc.run();
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
