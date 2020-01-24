/**
* @file passenger.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */

#include "src/passenger.h"

#include <iostream>
#include <string>


int Passenger::count_ = 0;

//  Passenger::Passenger(Stop * dest = NULL, std::string name = "Nobody") {
Passenger::Passenger(int destination_stop_id, std::string name)
: name_(name)
, destination_stop_id_(destination_stop_id)
, wait_at_stop_(0)
, time_on_bus_(0)
, id_(count_) {
  count_++;
}
/*
  This is the function that will update the times for passenger in bus or waiting for bus at stop.
*/
void Passenger::Update() {
  if (!IsOnBus()) {  // wating bus at stop
    wait_at_stop_++;
  } else {  // In the Bus
    time_on_bus_++;
  }
}
/*
  This is the function that will set the times to time_on_bus, since passenger gets on the bus.
*/
void Passenger::GetOnBus() {
  if (time_on_bus_ == 0) {
    time_on_bus_ = 1;
  }
}

/*
  This is the function that return the total waiting time.
*/
int Passenger::GetTotalWait() const {
  return wait_at_stop_ + time_on_bus_;
}

/*
  This is the function that checks the passenger is on bus or not.
*/
bool Passenger::IsOnBus() const {
  if (time_on_bus_ > 0) {
    return true;
  }
  return false;
}

/*
  This is the function that returns the passenger's destination stop id.
*/
int Passenger::GetDestination() const {
  return destination_stop_id_;
}

void Passenger::Report(std::ostream &out) const {
  out << "Name: " << name_ << std::endl;
  out << "Destination: " << destination_stop_id_ << std::endl;
  out << "Total Wait: " << GetTotalWait() << std::endl;
  out << "\tWait at Stop: " << wait_at_stop_ << std::endl;
  out << "\tTime on bus: " << time_on_bus_ << std::endl;
}
