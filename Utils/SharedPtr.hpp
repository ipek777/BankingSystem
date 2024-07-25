#pragma once
#include <iostream>
#include <exception> 


struct Counter
{
	unsigned useCount = 0;
	unsigned weakCount = 0;

	void removeSharedPtr()
	{
		useCount--;
		if (useCount == 0)
			weakCount--;
	}
	void removeWeakPtr()
	{
		weakCount--;
	}

	void addSharedPtr()
	{
		useCount++;
		if (useCount == 1)
			weakCount++;
	}

	void addWeakPtr()
	{
		weakCount++;
	}

};

template <typename T>
class SharedPtr
{
	template <typename V> friend class WeakPtr;

	T* _data;
	Counter* _counter;

	void free();
	void copyFrom(const SharedPtr<T>& other);
	void moveFrom(SharedPtr<T>&& other);

public:
	SharedPtr();
	SharedPtr(T* data);

	SharedPtr(const SharedPtr<T>& other);
	SharedPtr& operator=(const SharedPtr<T>& other);

	SharedPtr(SharedPtr<T>&& other);
	SharedPtr& operator=(SharedPtr<T>&& other);

	const T& operator*() const;
	T& operator*();
	const T* operator->() const;
	T* operator->();

	T* get() const noexcept;
	bool isInitlized() const;

	~SharedPtr();
};

template <typename T>
void SharedPtr<T>::free()
{
	if (_data == nullptr && _counter == nullptr)
		return;

	_counter->removeSharedPtr();

	if (_counter->useCount == 0)
		delete _data;

	if (_counter->weakCount == 0)
		delete _counter;
}

template <typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)
{
	_data = other._data;
	_counter = other._counter;
	if (_counter)
		_counter->addSharedPtr();
}

template <typename T>
SharedPtr<T>::SharedPtr()
{
	_data = nullptr;
	_counter = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* data)
{
	this->_data = data;
	if (this->_data)
	{
		_counter = new Counter();
		_counter->addSharedPtr();
	}
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
	copyFrom(other);
}

template <typename T>
void SharedPtr<T>::moveFrom(SharedPtr<T>&& other)
{
	_data = other._data;
	other._data = nullptr;

	_counter = other._counter;
	other._counter = nullptr;
}
template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other)
{
	moveFrom(std::move(other));
}
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
const T& SharedPtr<T>::operator*() const
{
	if (_data == nullptr)
	{
		throw std::runtime_error("Pointer not set");
	}
	return *_data;
}

template <typename T>
T& SharedPtr<T>::operator*()
{
	if (_data == nullptr)
	{
		throw std::runtime_error("Pointer not set");
	}
	return *_data;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
	free();
}


template<typename T>
T* SharedPtr<T>::operator->() {
	return _data;
}

template<typename T>
const T* SharedPtr<T>::operator->() const {
	return _data;
}

template<typename T>
 T* SharedPtr<T>::get() const noexcept
{
	return _data;
}

template<typename T>
bool SharedPtr<T>::isInitlized() const
{
	return _data != nullptr;
}
