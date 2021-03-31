#ifndef UTILITY_H
#define UTILITY_H
template<bool test,typename Type>
struct enable_if{};
template<bool IfTest,bool ElseIftest,typename OnIfTrue,typename OnElseIfTrue>
struct enable_if_elseif{
};
template<typename OnIfTrue,typename OnElseIfTrue>
struct enable_if_elseif<true,false,OnIfTrue,OnElseIfTrue>{
	using type=OnIfTrue;
};
template<typename OnIfTrue,typename OnElseIfTrue>
struct enable_if_elseif<false,true,OnIfTrue,OnElseIfTrue>{
	using type=OnElseIfTrue;
};
template<typename OnIfTrue,typename OnElseIfTrue>
struct enable_if_elseif<true,true,OnIfTrue,OnElseIfTrue>{
	using type=OnIfTrue;
};

template<typename T1,typename T2>
struct is_same{};

template<typename T>
struct is_same<T,T>{static constexpr bool value=true;};

template<typename T1,typename T2>
struct not_same{static constexpr bool value=true;};
template<typename T>
struct not_same<T,T>{};

//template<int Idx,typename... Types>
//struct type_at;

template<int Idx,typename This,typename... Types>
struct type_at{
	using type=typename type_at<Idx-1,Types...>::type;
};
template<typename This,typename... Rest>
struct type_at<0,This,Rest...>{
	using type=This;
};

template<typename ToFind,typename T,typename... Types>
struct index_of_type{static constexpr typename enable_if<not_same<ToFind,T>::value,int>::type I=index_of_type<ToFind,Types...>::I+1;};

template<typename T,typename... Types>
struct index_of_type<T,T,Types...>{
	static constexpr int I=0;
};
#endif
