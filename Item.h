#ifndef ITEM_H
#define ITEM_H
#define _USE_MATH_DEFINES

#include <string>
#include <iostream>
#include <ostream>
#include <math.h>
#include <vector>
using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::vector;


// TODO: your code goes here
class Item {
private:
	double latitude;
	double longitude;
	string id;
	int time;

	double degToRad(const double degIn) const {
		return degIn * (M_PI/180);
	} 

public: 
	Item(const double latIn, const double longIn, const string idIn, const int timeIn) 
	: latitude(latIn), longitude(longIn), id(idIn), time(timeIn) {}

	double getLat() const { return latitude; }

	double getLong() const { return longitude; }

	string getID() const { return id; }

	int getTime() const { return time; }

	double distanceTo(const Item other) const {
		double lat1 = degToRad( getLat() );
		double lat2 = degToRad( other.getLat() );

		double distLat = lat1 - lat2;
		double distLong = degToRad(getLong()) - degToRad( other.getLong() );

		const int R = 6373000;

		double a = pow((sin(distLat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(distLong/2)), 2);
		double b = 2 * atan2( sqrt(a), sqrt(1-a) );

		return R * b;
	}
};

class MapOfItems {
private:
	vector<Item> items;

public:
	void addItem(const Item & toAdd) {
		items.push_back(toAdd);
	}

	int size() const {
		return items.size();
	}

	vector<Item> getTour(const double & walkingSpeed) const {
		vector<Item> tour; //Store tour items
		vector<Item> notVisited = items; //Store copy of items
		double tourTime = notVisited[0].getTime(); //Set time equal to time of first item
		tour.push_back(notVisited[0]); //Visit first item
		Item lastVisited = notVisited[0]; //Track last visited item
		notVisited.erase(notVisited.begin()); //Remove visited item from notVisited list
		int lowestVTime = 3600;
		Item lowestVTItem = lastVisited;

		//For each item that hasn't been visited yet
		for (int i = 0; i < notVisited.size() && tourTime < 3600; ++i) {
			//Distance from last visit to this item
			int distance = lastVisited.distanceTo(notVisited[i]);
			//Time from last visit to this item
			int walkTime = distance/walkingSpeed;
			//Time this item would be visited if tour went to it
			int visitTime = walkTime + tourTime; 
			//If visitTime is more than 15 minutes late
			if (visitTime > notVisited[i].getTime() + 15) {
				//Don't visit this item, go to next item
				continue;
			}
			//If visitTime is earlier than item is available
			if (visitTime < notVisited[i].getTime()) {
				//Wait till item is available 
				visitTime = notVisited[i].getTime();
			}
			//If this item is closest
			if (visitTime < lowestVTime) {
				//Track its time as shortest
				lowestVTime = visitTime;
				//Set it as the item with shortest visit time
				lowestVTItem = notVisited[i];
			}
		}

		return tour;
	}
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

