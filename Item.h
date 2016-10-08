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

	Item determineNextVisit(const Item & lastVisited, const vector<Item> & notVisited, double & tourTime, const double walkingSpeed) const {
		int lowestVTime = 3600;
		Item lowestVTItem = lastVisited;

		//For each item that hasn't been visited yet
		for (int i = 0; i < notVisited.size(); ++i) {
			int distance = lastVisited.distanceTo(notVisited[i]); //Distance from last visit to this item
			int walkTime = distance/walkingSpeed; //Time from last visit to this item
			int visitTime = walkTime + tourTime; //Time this item would be visited if tour went to it
			if (visitTime > notVisited[i].getTime() + 900) { //If visitTime is more than 15 minutes late
				continue; //Don't visit this item, go to next item
			}
			if (visitTime < notVisited[i].getTime()) { //If visitTime is earlier than item is available	
				visitTime = notVisited[i].getTime(); //Wait till item is available 
			}
			if (visitTime < lowestVTime) { //If this item is closest	
				lowestVTime = visitTime; //Track its time as shortest
				lowestVTItem = notVisited[i]; //Set it as the item with shortest visit time
			}
		}
		tourTime = lowestVTime;
		return lowestVTItem;
	}

	int getIndex(const vector<Item> & notVisited, const Item & item) const {
		int index;
		for (int i = 0; i < notVisited.size(); ++i) {
			if (item.getID() == notVisited[i].getID()) {
				return index = i;
			}
		}
	}

	bool isVisited(const vector<Item> & tour, const Item & item) const {
		for (int i = 0; i < tour.size(); ++i) {
			if (item.getID() == tour[i].getID()) {
				return true;
			}
		}
		return false;
	}

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

		for (int i = 1; i < items.size() && tourTime < 3600; ++i) {
			lastVisited = determineNextVisit(lastVisited, notVisited, tourTime, walkingSpeed); 
			if (!isVisited(tour, lastVisited)) { //If Item hasn't been visited yet
				tour.push_back(lastVisited); //Visit item
			}
			notVisited.erase(notVisited.begin() + (getIndex(notVisited, lastVisited))); //Remove visited item
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

