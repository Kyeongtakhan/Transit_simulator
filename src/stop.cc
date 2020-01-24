/**
* @file stop.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */
#include <iostream>
#include <vector>

#include "src/stop.h"
/*
  Constructor for Stop. Stop class will include the id, and locations (longitude, latitude)
*/
Stop::Stop(int id, double longitude, double latitude)
: id_(id), longitude_(longitude), latitude_(latitude) {
  // Defaults to Westbound Coffman Union stop
  // no initialization of list of passengers necessary
}
/*
  This is the function that will add the passenger in the list of passengers in the station.
*/
int Stop::AddPassengers(Passenger * pass) {
  passengers_.push_back(pass);
  return 0;
}
/*
  This the function that will update the passenger information in station.
*/
void Stop::Update() {
  for (std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Update();
  }
}

int Stop::GetId() const {
  return id_;
}

void Stop::Report(std::ostream &out) const {
  out << "ID: " << id_ << std::endl;
  out << "Passengers waiting: " << passengers_.size() << std::endl;
  for (std::list<Passenger *>::const_iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}

/*
  GetPassengers_present is the function that return the size of passenger list.
  Purpose of this function is that when the bus load the passenger on bus from stop, to check out how many passenger in the stop.
  Then with GetWaitingPassengers function, passenger will get on the bus .
*/

int Stop::GetPassengersPresent() const {
  return passengers_.size();
}
Passenger* Stop::GetWaitingPassengers() {
  Passenger* passenger = passengers_.front();
  passengers_.pop_front();
  return passenger;
}
/*
  GetLongtitude and GetLatitude are the function that will return longitude and latitude.
*/
double Stop::GetLongitude() const {
  return longitude_;
}
double Stop::GetLatitude() const {
  return latitude_;
}
