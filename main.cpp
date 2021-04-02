#include <string>
#include <iostream>
#include <chrono>
#include "invoke.h"
#include "tuple.h"
#include "any.h"
#include "variant.h"

struct Some{
	int x;
	int z;
	int w;
}d[5];
int yes(int x){
	std::cout<<"Somethig happening"<<std::endl;
	return 99;
}
void something(tuple<int,float> dec){
	std::cout<<get<0>(dec)<<std::endl;
	std::cout<<get<1>(dec)<<std::endl;
}
template<typename T>
typename enable_if<is_same<T,int>::value,T>::type sum(T val);

template<typename T,typename... Types>
typename enable_if<is_same<T,int>::value,T>::type sum(T val,Types... vals);

template<typename T>
typename enable_if<is_same<T,double>::value,T>::type sum(T val);

template<typename T,typename... Types>
typename enable_if<is_same<T,double>::value,T>::type sum(T val,Types... vals);

template<typename T>
typename enable_if<is_same<T,int>::value,T>::type sum(T val){
	return val;
}

template<typename T,typename... Types>
typename enable_if<is_same<T,int>::value,T>::type sum(T val,Types... vals){
	return val+sum(vals...);
}

template<typename T>
typename enable_if<is_same<T,double>::value,T>::type sum(T val){
	return val;
}

template<typename T,typename... Types>
typename enable_if<is_same<T,double>::value,T>::type sum(T val,Types... vals){
	return val+sum(vals...);
}

template<typename T,typename... Types>
typename enable_if<is_same<T,double>::value,T>::type average(T val,Types... vals){
	return (T)(sum(val,vals...))/(sizeof...(Types)+1);
}

template<int Idx=0,typename... Types>
typename type_at<Idx,Types...>::type get_something(int arg){
	using CastType=typename type_at<Idx,Types...>::type;
	return (CastType)arg;
}

template<typename T>
Some operator+(Some& left,T& right){
	return Some{left.x,right.z,left.w};
}

int callme(int x,int y){
	std::cout<<x<<"+"<<y<<"="<<x+y<<std::endl;
	return x+y;
}

ulli su(ulli val){
	if (val==0){return 0;}
	return val+su(val-1);
}
//use -ftemplate-depth=3000 compiler argument

struct Visitor{
	const char* operator ()(int x){
		std::cout<<x<<" ";
		return "Visited type is int";
	}
	const char* operator ()(float x){
		std::cout<<x<<" ";
		return "Visited type is float";
	}
	const char* operator ()(long x){
		std::cout<<x<<" ";
		return "Visited type is long";
	}
};
class D{
	public:
		D(){
		}
		int detail(int y,int z){
			return y+z;
		}
		static void some(){
			std::cout<<"Caughted"<<std::endl;
		}
};
template<typename T>
T take_any(T value,any_t some){
	return value*any_cast<T>(some);	
}
std::ostream& operator<<(std::ostream& in,const Some& s){
	std::cout<<"["<<s.w<<","<<s.x<<","<<s.z<<"]";
	return in;
}
int main(int argc, char** argv) {
	Some left{5,8,7};
	Some right{8,9,0};
	Some newSome=left+right;
	
	int i=index_of_type<long,int,float,char,long>::I;
	auto start=std::chrono::steady_clock::now();
	std::cout<<su(2100)<<std::endl;
	auto end=std::chrono::steady_clock::now();
	std::cout<<"ellapsed time:"<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()<<std::endl;
	start=std::chrono::steady_clock::now();
	std::cout<<sum_of_n<2100>::result<<std::endl;
	end=std::chrono::steady_clock::now();
	std::cout<<"ellapsed time:"<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()<<std::endl;
	std::cout<<visit(0xFFFFFFFl,Visitor{})<<std::endl;
	std::cout<<invoke_class_method(new D(),&D::detail,3,4)<<std::endl;
	any_t x=3;
	std::cout<<take_any(44,x)<<std::endl;
	std::cout<<any_cast<char>(x)<<std::endl;
	std::cout<<contain_t<float,float,char>::found<<std::endl;
	
	variant_t<int,float,double,Some> ydelta=44;
	try{
		std::cout<<get_if<Some>(ydelta)<<std::endl;
	}catch(invalid_get_type& e){
		std::cerr<<e.what<<std::endl;
		try{
		  std::cout<<get_if<double>(ydelta)<<std::endl;
		}catch(invalid_get_type& e2){
			std::cerr<<e2.what<<std::endl;
			try{
		  		std::cout<<get_if<float>(ydelta)<<std::endl;
			}catch(invalid_get_type& e3){
				std::cerr<<e3.what<<std::endl;
				try{
		  			std::cout<<get_if<int>(ydelta)<<std::endl;
				}catch(invalid_get_type& e2){
					
				}
			}
		}
	}
	return 0;
}
