#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
using std::string;

using std::cout;
using std::endl;

// TODO: your code goes here
class Item {
private:
	double latitude;
	double longitude;
	string id;
	int time;

public: 
	Item(const double latIn, const double longIn, const string idIn, const int timeIn) 
	: latitude(latIn), longitude(longIn), id(idIn), time(timeIn) {}

	double getLat() const { return latitude; }

	double getLong() const { return longitude; }

	string getID() const { return id; }

	int getTime() const { return time; }
};




// don't write any code below this line

#endif

