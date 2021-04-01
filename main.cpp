#include "tuple.h"
#include <string>
#include <iostream>
#include <chrono>
#include "invoke.h"
struct Some{
	int x;
	int z;
	int w;
};
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
	return 0;
}
