#pragma once
#ifndef FLVECTOR_H
#define FLVECTOR_H

template <typename T>
class FLVector {
public:
	//constructor
	FLVector(int size, T default) {
		_size = size;
		_arr = new T[size];
		for (int i = 0; i < size; i++) {
			_arr[i] = default;
		}
	}

	//destructor
	~FLVector() {
		delete[] _arr;
	}

	//return the size of the array
	int length() {
		return _size;
	}

	//return element at index i
	T get(int i) {
		return _arr[i];
	}

	//set element at index i
	void add(int i, T data) {
		_arr[i] = data;
	}

private:
	T* _arr;
	int _size;
};

#endif
