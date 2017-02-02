#pragma once
#ifndef VECTORBASED_H
#define VECTORBASED_H

#include <vector>
using std::vector;

template <typename T>
class VStack {
public:
	//Constructor
	VStack() {}
	~VStack() { list.clear(); }

	//Return the top element in the list without removing it
	T peek(){
		return list.back();
	}

	//Return the top element and remove it from the stack
	void pop(){
		list.pop_back();
	}

	//Add an element to the top of the stack
	void push(T data){
		list.push_back(data);
	}

	int length() {
		return list.size();
	}

	bool isEmpty() {
		return list.empty();
	}

	void clear() {
		list.clear();
	}

private:
	int _top;	//point at the top element of the stack
	vector<T> list;

};

#endif