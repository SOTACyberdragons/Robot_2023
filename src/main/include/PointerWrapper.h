#include <vector>
#include <iostream>
#include <memory>

class Person {
private:
    std::string m_name;

    static inline int s_personCount = 0;
public:
    Person(std::string name) 
        : m_name(name)
    {
        s_personCount++;
        std::cout << "Person was born\n";
    }

    ~Person() {
        std::cout << "Person died\n";
    }

    void introduce() {
        std::cout << "Hello, my name is " << m_name << std::endl;
    }

    static void printPopulation() {
        std::cout << s_personCount << std::endl;
    }
};



void makeBars() {
    Person* lawyer = new Person("Saul Goodman");
    
    //do some complicated stuff

    delete lawyer;
}

void foo() {
    makeBars();
}