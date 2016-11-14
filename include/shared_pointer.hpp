#include <iostream>

template <typename T>
class shared_pointer {
public:
	shared_pointer(); /*noexcept*/
	shared_pointer(T * pointer); /*strong*/
	shared_pointer(shared_pointer const & other_shared_pointer); /*noexcept*/
	auto operator=(shared_pointer const & other_shared_pointer) -> shared_pointer &; /*noexcept*/
	shared_pointer(shared_pointer && other_shared_pointer); /*noexcept*/
	auto operator=(shared_pointer && other_shared_pointer) -> shared_pointer &; /*noexcept*/
	~shared_pointer(); /*noexcept*/

	void swap(shared_pointer &); /*noexcept*/
	void reset(); /*noexcept*/
	auto get() const -> T *; /*noexcept*/
	auto operator->() const -> T *; /*strong*/
	auto operator*() const -> T &; /*strong*/
	auto getNReferences() const -> size_t; /*noexcept*/
private:
	T * pointer;
	size_t * counter;
};

template <typename T>
shared_pointer<T>::shared_pointer() : 
	pointer(nullptr), 
	counter(nullptr) 
{
	;
}

template <typename T>
shared_pointer<T>::shared_pointer(T* pointer) : 
	pointer(pointer),
	counter(new size_t(1)) 
{
	;
}

template <typename T>
shared_pointer<T>::shared_pointer(shared_pointer const & other_shared_pointer) : 
	pointer(other_shared_pointer.pointer), 
	counter(other_shared_pointer.counter)
{
	if (counter != nullptr) {
		++(*counter);
	}
}

template <typename T>
auto shared_pointer<T>::operator=(shared_pointer const & other_shared_pointer) -> shared_pointer &
{
	if (this != &other_shared_pointer)
	{
		(shared_pointer<T>(other_shared_pointer)).swap(*this);
	}
	return *this;
}

template <typename T>
shared_pointer<T>::shared_pointer(shared_pointer && other_shared_pointer) : 
	pointer(other_shared_pointer.pointer), 
	counter(other_shared_pointer.counter)
{
	other_shared_pointer.pointer = nullptr;
	other_shared_pointer.counter = nullptr;
}

template <typename T>
auto shared_pointer<T>::operator=(shared_pointer && other_shared_pointer) -> shared_pointer&
{
	if (this != &other_shared_pointer) {
		this->swap(other_shared_pointer);
	}
	return *this;
}

template <typename T>
shared_pointer<T>::~shared_pointer()
{
	if (counter != nullptr) {
		(*counter)--;
		if ((*counter) == 0) {
			delete pointer;
			delete counter;
		}
	}
}

template <typename T>
void shared_pointer<T>::swap(shared_pointer & other_shared_pointer)
{
	std::swap(pointer, other_shared_pointer.pointer);
	std::swap(counter, other_shared_pointer.counter);
}

template <typename T>
void shared_pointer<T>::reset()
{
	(*counter)--;
	if ((*counter) == 0) {
		delete pointer;
		delete counter;
	}
	pointer = nullptr;
	counter = nullptr;
}

template <typename T>
auto shared_pointer<T>::get() const -> T*
{
	return pointer;
}

template <typename T>
auto shared_pointer<T>::operator->() const -> T*
{
	if (pointer != nullptr) {
		return pointer;
	}
	else {
		throw ("pointer == nullptr");
	}
}

template <typename T>
auto shared_pointer<T>::operator*() const -> T &
{
	if (pointer != nullptr) {
		return *pointer;
	}
	else {
		throw ("pointer == nullptr");
	}
}

template <typename T>
auto shared_pointer<T>::getNReferences() const -> size_t
{
	if (counter != nullptr) {
		return *counter;
	}
	else {
		return 0;
	}
}
