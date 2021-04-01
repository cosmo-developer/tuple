#ifndef INVOKE_H
#define INVOKE_H
#include "utility.h"


template<typename RetType=void,typename FuncType,typename... Args>
typename enable_if<is_same<void,RetType>::value,void>::type invoke_result(FuncType func,Args... tup){
	func(tup...);
}
template<typename RetType,typename FuncType,typename... Args>
typename enable_if<not_same<void,RetType>::value,RetType>::type invoke_result(FuncType func,Args... tup){
	return (RetType)func(tup...);
}

template<typename RetType=void,typename... Args>
typename enable_if<is_same<void,RetType>::value,void>::type invoke(RetType(*Fptr)(Args...),Args... args){
	Fptr(args...);
}
template<typename RetType,typename... Args>
typename enable_if<not_same<RetType,void>::value,RetType>::type invoke(RetType(*Fptr)(Args...),Args... args){
	return Fptr(args...);
}
#endif
