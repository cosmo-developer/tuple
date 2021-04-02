#ifndef VARIANT_H
#define VARIANT_H
#include "any.h"
#include "utility.h"
#include <string>
#include <typeinfo>
struct invalid_get_type{
	std::string what;
};
template<typename... Tps>
struct variant_t{
	private:
		any_t value=0;
		int index=99;
	public:
		template<typename T>
		variant_t(T val){
			value=val;
			index=index_of_type<T,Tps...>::I;
		}
		template<typename T>
		T get(){
			if (index==index_of_type<T,Tps...>::I)
			  return any_cast<T>(value);
			throw invalid_get_type{std::string("Invalid cast type '")+std::string(typeid(T).name())+
			std::string("'")};
		}
};
template<typename Tp,typename... Tps>
typename enable_if<contain_t<Tp,Tps...>::found,Tp>::type get_if(variant_t<Tps...> in){
	return in.get<Tp>();
}
#endif
