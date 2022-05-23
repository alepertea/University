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
	vector <Observer*> observers;
protected:
	void notify()
	{
		for (auto obs : observers)
			obs->update();
	}
public:
	void addObserver(Observer* o)
	{
		observers.push_back(o);
	}
};