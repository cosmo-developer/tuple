#ifndef ANY_H
#define ANY_H
#include <iostream>
struct any_t{
	private:
		struct storage_t;
		template<typename T>
		struct impl_t;
		struct storage_t{
			void* pointer;
			storage_t(){
				pointer=(void*)get();
			}
			virtual void* get(){
				return NULL;
			};
			~storage_t(){
//				free(pointer);
			}
		};
		template<typename T>
		struct impl_t:storage_t{
			impl_t(const T& val){
				this->val=val;
			}
			void* get(){
				T* mem=(T*)malloc(sizeof(T));
				mem[0]=val;
				return mem;
			}
			T val;
		};
	storage_t* storage;
	public:
		template<typename T>
		any_t(T value):storage(new impl_t<T>(value)){}
		template<typename CTp>
		CTp cast_any(){return ((CTp*)storage->get())[0];}
//		~any_t(){delete storage;}
};
template<typename T>
T any_cast(any_t any){
	return any.cast_any<T>();
}
#endif
