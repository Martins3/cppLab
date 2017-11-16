//
// Created by martin on 17-11-4.
//

#ifndef CPPLAB_PRIMER_H
#define CPPLAB_PRIMER_H

#include <iostream>
using namespace std;
class Creature{
public:
    Creature(){
        cout << "creature\n";
    }
public:
    virtual void eat() = 0;
};

class Animal: Creature{
public:
    Animal(){
        cout << "animal\n";
    }
    virtual void eat(){
        cout << "food\n";
    }
    virtual void paly();
    static int s;

protected:
    int p = 12;
};
int Animal::s = 123;
void Animal::paly() {

}

class Cat: public Animal{
public:
    Cat(){
        cout << "cat\n";
    }

    explicit Cat(int a){
        cout << "cat + " << a << " ";
    }

    void eat() override {
        cout << "fish\n";
    }

    void eat(int n){
        for (int i = 0; i < n ; ++i) {
            cout << "fish";
        }
    }

    void getP(){
        cout << p;
    }

protected:
    int fish_num = 123;
    int a = 123;
private:

    int p_num = 1231231;
    void fuck(){
        cout << "no fuck, no life";
    }
};


class FatCat: public Cat{
public:
    using Cat::Cat;
    FatCat():Cat(){
        cout << "fat_cat\n";
    }


    explicit FatCat(int a): Cat(a) {
        cout << "cat >> fat_cat";
    }

    using Cat::fish_num;
    using Cat::eat;
    int a = 123;
    void eat() override {
        cout << "eat real a lot of fish";
        cout << Cat::fish_num;
    }
};


void do_eat(Animal* animal){
    animal -> eat();
}

// ---------------------------------- 多继承 -------------------------------

class Base1{
private:
    void fun(){
        cout << "Base1";
    }
};

class Base2{
private:
    void fun(){
        cout << "base2";
    }
};

class D1: public Base1, public Base2{
public:


};


// ------------------------------------- base -------------------------------

class A{
public:
    int a;
    explicit A(int a):a(a){
       cout << "A";
    }
};
class B:public A{
public:
    int b;
    B(int b):b(b), A(b){
        cout << "B";
    }
};

class C: public B{
public:
    int c;
    C(int c):c(c),B(c){
        cout << "C";
    }
};

// ---------------------- basic -------------------------------------------
class F{
public:
    static int make(){
        cout << "nothing";
    }

    int nothing(){
    }
};


#endif //CPPLAB_PRIMER_H
