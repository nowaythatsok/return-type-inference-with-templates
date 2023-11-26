#include <iostream>

template <typename T>
class A {
    public:
        T a;
        A(T num){a=num;}
        template <typename U> A( const A<U>& obj ){a=static_cast<T>(obj.a);}

        A& operator+=(const A& obj){ a+=obj.a; return *this; }

        std::string type(){ return typeid(T).name(); }

};

template <typename T> A<T> operator+(const A<T>& m1, const A<T>& m2)
{
    A<T> temp(m1);
    return (temp += m2);
}

// template <typename T, typename U> auto operator+(const A<T>& m1, const A<U>& m2) -> A<decltype( static_cast<T>(0) + static_cast<U>(0))>
template <typename T, typename U> A<decltype( static_cast<T>(0) + static_cast<U>(0))> operator+(const A<T>& m1, const A<U>& m2)
{
    // figure out the optimal type of the return value
    typedef decltype( static_cast<T>(0) + static_cast<U>(0)) ret_type;
    A<ret_type> temp(m1);
    return (temp += static_cast<ret_type>(m2.a));
}


int main(){

    A<int> a(1);
    A<float> b(10);
    
    std::cout<<a.a<<" ("<<a.type()<<")"<<" "<<b.a<<" ("<<b.type()<<")"<<std::endl;
    std::cout<<a.a+b.a<<std::endl;
    std::cout<<(a+b).a<<" ("<<(a+b).type()<<")"<<std::endl;
    std::cout<<(b+a).a<<" ("<<(b+a).type()<<")"<<std::endl;

    return 0;

}