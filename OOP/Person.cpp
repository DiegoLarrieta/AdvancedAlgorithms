#include <iostream>
#include <string>

using namespace std;

class Person {
  private:
    string first;
    string last;
  public:

  //Constructor
  Person(string first , string last){
    this -> first = first;
    this -> last = last;
  }

  Person() = default;

    void setFirstName(string first){
      this -> first = first;
    }

    void setLastName(string last){
      this -> last = last;
    }

    string getName(){
      return first + " " + last;
    }



    void printFullName(){
      cout<< first << " " << last << endl;
    };
};

class Employee : public Person{

};

int main(){
  Person p("Diego","Larrieta");

  p.printFullName();
  cout<<p.getName()<<endl;

  Person p2("Paulina" , "Mora");
  p2.printFullName();

  Employee e;
  e.setFirstName("Olivia");
  e.setLastName("Carlsetad");

  e.printFullName();

  // class -> describres the estructure

  // object -> a specific example of that structure (instance)

  // instace -> creating an object from a class

  // data members -> variables 

  // methods -> functions 

  //Parent class (base class) -> inherithed from

  //child class(derived class) -> does the inherited 

  //Abstraction -> A concept where you make something easy by hiding the complicated stuff

  // Encapsulation -> Granting acces to private data only throught controlled public interfaces

  //Inheritance -> We can create derived classes that inherit properties from their parent classes;

  //Polymorphims -> We can treat multiple different objects as their base
    return 0;
}