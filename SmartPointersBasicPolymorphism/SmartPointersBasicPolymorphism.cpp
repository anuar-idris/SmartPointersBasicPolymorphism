// SmartPointersBasicPolymorphism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
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
    //declare member variable for these pointers
    std::shared_ptr<Animal> pRabbit;
    std::shared_ptr<Animal> pCat;

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

    void CreateSmartPointer()
    {
        //create smart pointers
        pRabbit = std::make_shared<Rabbit>();
        pCat = std::make_shared<Cat>();
    }

    void StoreSmartPointer()
    {
        //Store those smart pointers in the vector of shared pointers
        //the same like copy pointers, not cut and paste
        m_Vec.push_back(pRabbit);
        m_Vec.push_back(pCat);
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
        std::cout << "Pointers to underlying Rabbit: "
            << pRabbit.use_count() << " Address: " << &pRabbit 
            << " Pointers to underlying Cat: "
            << pCat.use_count() << " Address: " << &pCat
            << "\n";

        CreateSmartPointer();

        std::cout << "Pointers to underlying Rabbit: "
            << pRabbit.use_count() << " Address: " << &pRabbit
            << " Pointers to underlying Cat: "
            << pCat.use_count() << " Address: " << &pCat
            << "\n";

        StoreSmartPointer();

        // All pointers to Rabbit share ownership
        std::cout << "Pointers to underlying Rabbit: "
            << pRabbit.use_count() << " Address: " << &pRabbit
            << " Pointers to underlying Cat: "
            << pCat.use_count() << " Address: " << &pCat
            << "\n";
    }
};

int main()
{
    //method to detect memory leaks. If we are not sure which is the exit
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::cout << "Hello World!\n";

    MyCompositeClass mc;
    mc.run();
    mc.SayHello();
    
    //method to detect memory leaks. Only if we certain only one exit
    //_CrtDumpMemoryLeaks();
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
