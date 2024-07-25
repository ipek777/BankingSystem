#pragma once
#include <iostream>

template <typename T>
class ArrayOfPointers
{
	T** _data = nullptr;
	size_t _capacity = 0;
	size_t _count = 0;

	void free();
	void copyFrom(const ArrayOfPointers& other);
	void resize(size_t newCap);
	void moveFrom(ArrayOfPointers&& other);
	int getFirstFreeIndex() const;

public:

	ArrayOfPointers();
	ArrayOfPointers(size_t size);
	ArrayOfPointers(const ArrayOfPointers& other);
	ArrayOfPointers& operator=(const ArrayOfPointers& other);
	~ArrayOfPointers();

	ArrayOfPointers(ArrayOfPointers&& other) noexcept;
	ArrayOfPointers& operator=(ArrayOfPointers&& other) noexcept;

	void push_back(const T& current);
	void push_back(T&& obj);
	void push_back(T* obj);

	bool containsAt(unsigned ind) const;
	int find(const T& data) const;
	int find(T&& data) const;
	void pop_back();
	void erase(size_t index);

	void insert(const T& obj, size_t index);
	void insert(T&& obj, size_t index);


	size_t size() const;
	size_t capacity() const;
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
};

template <typename T>
void ArrayOfPointers<T>::free()
{
	if (_count == 0)
	{
		return;
	}

	for (int i = 0; i < _capacity; i++)
	{
		delete _data[i];
	}
	delete[] _data;
}

template <typename T>
void ArrayOfPointers<T>::copyFrom(const ArrayOfPointers& other)
{
	_count = other._count;
	_capacity = other._capacity;

	_data = new T * [_capacity];
	for (int i = 0; i < _capacity; i++)
	{
		if (other._data[i] == nullptr)
			_data[i] = nullptr;
		else
			_data[i] = new T(*other._data[i]);
	}
}

template <typename T>
void ArrayOfPointers<T>::resize(size_t newCap)
{
	T** newDataPtr = new T * [newCap] {nullptr};

	for (int i = 0; i < _capacity; i++)
		newDataPtr[i] = _data[i];

	delete[] _data;
	_data = newDataPtr;

	_capacity = newCap;
}

template <typename T>
void ArrayOfPointers<T>::moveFrom(ArrayOfPointers&& other)
{
	_data = other._data;
	other._data = nullptr;

	_capacity = other._capacity;
	_count = other._count;

	other._count = 0;
}

template <typename T>
int ArrayOfPointers<T>::getFirstFreeIndex() const
{
	for (int i = 0; i < _capacity; i++)
		if (_data[i] == nullptr)
			return i;
	return -1;
}

template <typename T>
ArrayOfPointers<T>::ArrayOfPointers()
{
	_capacity = 8;
	_data = new T * [_capacity] {nullptr};
}

template<typename T>
inline ArrayOfPointers<T>::ArrayOfPointers(size_t size)
{
	_count = _capacity = size;
	_data = new T * [_capacity] {nullptr};
}

template <typename T>
ArrayOfPointers<T>::ArrayOfPointers(const ArrayOfPointers& other)
{
	copyFrom(other);
}

template <typename T>
ArrayOfPointers<T>& ArrayOfPointers<T>::operator=(const ArrayOfPointers& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
ArrayOfPointers<T>::~ArrayOfPointers()
{
	free();
}

template <typename T>
ArrayOfPointers<T>::ArrayOfPointers(ArrayOfPointers&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
ArrayOfPointers<T>& ArrayOfPointers<T>::operator=(ArrayOfPointers<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
void ArrayOfPointers<T>::push_back(const T& current)
{
	if (_count >= _capacity)
		resize(_capacity * 2);

	int ind = getFirstFreeIndex();
	if (ind == -1)
		return;

	_data[ind] = new T(current);
	_count++;
}

template <typename T>
void ArrayOfPointers<T>::push_back(T&& obj)
{
	if (_count >= _capacity)
		resize(_capacity * 2);

	int ind = getFirstFreeIndex();
	if (ind == -1)
		return;

	_data[ind] = new T(std::move(obj));
	_count++;
}

template <typename T>
void ArrayOfPointers<T>::push_back(T* obj)
{
	if (_count >= _capacity)
		resize(_capacity * 2);

	int ind = getFirstFreeIndex();
	if (ind == -1)
		return;

	_data[ind] = obj;
	_count++;
}

template <typename T>
bool ArrayOfPointers<T>::containsAt(unsigned ind) const
{
	return ind < _capacity && _data[ind] != nullptr;
}

template<typename T>
int ArrayOfPointers<T>::find(const T& data) const
{
	for (size_t i = 0; i < _count; i++)
	{
		if (*(_data[i]) == data)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
int ArrayOfPointers<T>::find(T&& data) const
{
	for (size_t i = 0; i < _count; i++)
	{
		if (*(_data[i]) == data)
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
void ArrayOfPointers<T>::pop_back()
{
	if (size() == 0)
		return;

	delete _data[_count - 1];
	_count--;
}

template <typename T>
void ArrayOfPointers<T>::erase(size_t index)
{
	if (index >= _capacity)
		return;

	delete _data[index];
	_data[index] = nullptr;
	_count--;
}

template <typename T>
void ArrayOfPointers<T>::insert(const T& obj, size_t index)
{
	if (index >= _capacity)
		resize(_capacity * 2);

	if (_data[index] != nullptr)
		_data[index]->operator=(obj);
	else
	{
		_data[index] = new T(obj);
		_count++;
	}
}

template <typename T>
void ArrayOfPointers<T>::insert(T&& obj, size_t index)
{
	if (_data[index] != nullptr)
		*_data[index] = obj;
	else
	{
		_data[index] = new T(std::move(obj));
		_count++;
	}
}

template <typename T>
size_t ArrayOfPointers<T>::size() const
{
	return _count;
}

template<typename T>
inline size_t ArrayOfPointers<T>::capacity() const
{
	return _capacity;
}

template <typename T>
const T& ArrayOfPointers<T>::operator[](size_t index) const
{
	if (_data[index] == nullptr)
	{
		throw std::exception("No data at current spot!");
	}
	return *_data[index];
}

template <typename T>
T& ArrayOfPointers<T>::operator[](size_t index)
{
	if (_data[index] == nullptr)
	{
		throw std::exception("No data at current spot!");
	}
	return *_data[index];
}
