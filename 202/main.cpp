/*
lab 14
Chaweinta Hale
CS202 Fall 2018

Write a class template called "Wrapper" that can contain an
object of any type. You will need a constructor that takes an
object of the given type.
Your class should contain an overloaded operator<<
which will insert the wrapped object into the ostream.
Use the following code to demonstrate the use of your class:
Wrapper<int> w{2};
Wrapper<string> s{"Hello world!"};
cout << w << " " << s << endl;

*/
#include <iostream>
using namespace std;

template<class T>
class Wrapper{ //class template that can contain an object of any type
    friend ostream& operator<<(ostream& os, Wrapper x){ //overloaded operator<< which will insert the wrapped object into the ostream
    os << x._storage;
    return os;
    };
    private:
        T _storage;
    public:
        Wrapper(T);
};

template<typename T>
Wrapper<T>::Wrapper(T var): _storage(var){}; //constructor that takes an object of the given type

int main()
{
    Wrapper<int> w{2};
    Wrapper<string> s{"Hello world!"};
    cout << w << " " << s << endl;
    return 0;
}
