#pragma once
#include <algorithm>
#include <vector>

using namespace std;

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
	vector<Observer*> observers;
protected:
	void notify();
public:
	void addObserver(Observer* o);
	void removeObserver(Observer* o);
};