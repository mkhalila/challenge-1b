#ifndef ITEM_H
#define ITEM_H
#define _USE_MATH_DEFINES

#include <string>
#include <iostream>
#include <ostream>
#include <math.h>
using std::string;
using std::cout;
using std::endl;
using std::ostream;


// TODO: your code goes here
class Item {
private:
	double latitude;
	double longitude;
	string id;
	int time;

	double degToRad(const double degIn) {
		return degIn * (M_PI/180);
	} 

public: 
	Item(const double latIn, const double longIn, const string idIn, const int timeIn) 
	: latitude(latIn), longitude(longIn), id(idIn), time(timeIn) {}

	double getLat() const { return latitude; }

	double getLong() const { return longitude; }

	string getID() const { return id; }

	int getTime() const { return time; }
};

ostream & operator<<(ostream & o, const Item & rhs) {
	o << "{" << rhs.getLat() << ", ";
	o << rhs.getLong() << ", ";
	o << "\"" << rhs.getID() << "\"" << ", ";
	o << rhs.getTime();
	o << "}";
	return o;
}

// don't write any code below this line

#endif

