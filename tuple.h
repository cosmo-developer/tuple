#ifndef TUPLE_H
#define TUPLE_H
#include "utility.h"
template<typename... Args>
class tuple;

template<>
class tuple<>{};

template<typename T,typename... Args>
class tuple<T,Args...>{
	using ThisType=T;
	using RestType=tuple<Args...>;
	public:
		ThisType value;
		RestType other;
};

template<typename T>
tuple<T> make_tuple(T self){
	tuple<T> tup=tuple<T>();
	tup.value=self;
	tup.other=tuple<>();
	return tup;
}

template<typename T,typename... Args>
tuple<T,Args...> make_tuple(T value,Args... types){
	tuple<T,Args...> tup=tuple<T,Args...>();
	tup.value=value;
	tup.other=make_tuple(types...);
	return tup;
}

template<int Idx,typename... Types>
struct element_type_at;

template<typename This,typename... Types>
struct element_type_at<0,tuple<This,Types...>>{
	using MyType=This;
	using RestType=tuple<Types...>;
};

template<int Idx,typename This,typename... Types>
struct element_type_at<Idx,tuple<This,Types...>>{
	using MyType=typename element_type_at<Idx-1,tuple<Types...>>::MyType;
};
template<int id>
class zero;

template<int id>
class normal;

template<int e>
class empty;

template<int Idx>
struct element_caller{using getter=normal<Idx>;};

template<>
struct element_caller<0>{
	using getter=zero<0>;
};

template<int id>
class zero{
	public:
	template<int idx=id,typename... Args>
	static typename element_type_at<idx,tuple<Args...>>::MyType get(tuple<Args...> tup){
		return tup.value;
	}
};

template<int id>
class normal{
	public:
		template<int idx=id,typename... Args>
		static typename element_type_at<idx,tuple<Args...>>::MyType get(tuple<Args...> tup){
			return element_caller<idx-1>::getter::get(tup.other);
		}
};

template<int Idx,typename... Args>
typename element_type_at<Idx,tuple<Args...>>::MyType get(tuple<Args...> tup){
	return element_caller<Idx>::getter::get(tup);
}

template<typename T>
tuple<T> forward_as_tuple(T val){
	tuple<T> tup= make_tuple(val);
	return tup;
}

template<typename This,typename... Args>
tuple<This,Args...> forward_as_tuple(This type,Args... types){
	tuple<This,Args...> tup;
	tup.value=type;
	tup.other=forward_as_tuple(types...);
	return tup;
}

#endif
