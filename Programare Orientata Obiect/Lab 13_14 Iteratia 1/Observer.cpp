#include "Observer.h"

void Observable::notify()
{
	for (auto obs : this->observers)
	{
		obs->update();
	}
}

void Observable::addObserver(Observer* o)
{
	this->observers.push_back(o);
}

void Observable::removeObserver(Observer* o)
{
	this->observers.erase(remove(this->observers.begin(), this->observers.end(), o), this->observers.end());
}