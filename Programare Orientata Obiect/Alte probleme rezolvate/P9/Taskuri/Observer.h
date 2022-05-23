#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Observer
{
public:
	virtual void update() = 0;
};

class Observable
{
private:
	vector<Observer*> observers;
protected:

public:
	void notify()
	{
		for (auto obs : this->observers)
			obs->update();
	}
	void addObserver(Observer* o)
	{
		this->observers.push_back(o);
	}
	void removeObserver(Observer* o)
	{
		this->observers.erase(remove(this->observers.begin(), this->observers.end(), o), this->observers.end());
	}
};