#ifndef __ARRAY_H
#define __ARRAY_H
#include <iostream>
using namespace std;

template<class T>
class Array
{
private:
	int _phy_size = 1;
	int _log_size = 0;
	T* _arr=nullptr;
public:
	Array();
	Array(const Array& other);
	~Array();

	//get
	const T& getVal(int i) const;
	 T* getArr() const;
	const int& getPhySize()const ;
	const int& getLogSize()const;
	// operators
	const Array& operator=(const Array& other);
	const Array& operator+=(const T& newVal);

	friend ostream& operator<<(ostream& os, const Array& array)
	{
		for (int i = 0; i < array._log_size; i++)
		{
			os << array._arr[i] << " ";
		}
		return os;
	}
};

template<class T>
Array<T> ::Array()
{
	_arr = new T;
}
template<class T>
Array<T> ::Array(const Array& other)
{
	*this = other;
}
template<class T>
Array<T>::~Array()
{
	for (int i = 0; i < _log_size; i++)
		delete _arr[i];
	delete[] _arr;
}
template<class T>
const Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this != &other)
	{
		delete[]_arr;
		_phy_size = other._phy_size;
		_log_size = other._log_size;
		_arr = new T[_phy_size];
		for (int i = 0; i < _log_size; i++)
			_arr[i] = other._arr[i];
	}
	return *this;
}

template<class T>
const Array<T>& Array<T>::operator+=(const T& other)
{
	if (_log_size == _phy_size)
	{
		_phy_size *= 2;
		T* newArr = new T[_phy_size];
		for (int i = 0; i < _log_size; i++)
		{
			newArr[i] = _arr[i];
		}
		_arr = newArr;
	}
	_arr[_log_size++] =other;
	return *this;
}
template<class T>
const T& Array<T>::getVal(int i) const
{
	return _arr[i];
}
template<class T>
 T* Array<T>::getArr() const
{
	return _arr;
}
template<class T>
const int& Array<T>::getPhySize() const
{
	return _phy_size;
}
template<class T>
const int& Array<T>::getLogSize() const
{
	return _log_size;
}
#endif 