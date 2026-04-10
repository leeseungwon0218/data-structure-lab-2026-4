#pragma once
#include <iostream>
#include <string>

using namespace std;

class Pet {
protected:
    string name;
    int age;
    string type;
public:
    //생성자
    Pet(string n, int a, string t)
        : name(n), age(a), type(t) {
    }        //생성자 초기화 리스트

//Get Name
    string getName() {
        return name;
    }
    //Get age
    int getAge() {
        return age;
    }
    //Get type
    string getType() {
        return type;                    //protected 때문에 이런 method들로 접근할 수 있게 만들어줌
    }
};

class Puppy : public Pet {
private:
    string breed; //개 견종
public:
    //생성자
    Puppy(string n, int a, string t, string b)
        : Pet(n, a, t), breed(b) {
    }            //Pet을 상속 받으면서 breed 까지 표현

//Get breed
    string getBreed() {
        return breed;
    }
};