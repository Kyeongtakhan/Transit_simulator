/**
 * @file bus.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */

#include "src/bus.h"

Bus::Bus(std::string name, Route * out, Route * in
  , int capacity, double speed) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  distance_remaining_ = 0;
  is_route_change_ = false;
  bus_inroute_counter_ = 0;
  bus_outroute_counter_ = 0;
  finish_tag_ = false;
  current_stop_ = NULL;
  got_stop_ = false;
  next_stop_ = NULL;
}

/*
  pre_condition: if the current number of passenger can't take passenger any more, it will return false.
  This is the actual function that will put the passenger on the Passenger list in the Bus.
  Before loading the passenger, it will check out the accomodation of bus. If capacity is over, it will return false, other wise true
*/
bool Bus::LoadPassenger(Passenger * new_passenger) {
  int size = passengers_.size();
  // check out the capacity is not over
  if (passenger_max_capacity_ >= size + 1) {
      passengers_.push_back(new_passenger);
      return true;
  }
  return false;
}
/*
  This is the function that returns true when the bus finishes up both routes, which are outgoing_route and incoming_route_.
  The variable finish_tag_ is the member variable in Bus class and it will be changed only when the bus finishes up all routes.
*/

bool Bus::IsTripComplete() {
  if (finish_tag_) {
    return true;
  }
  return false;
}

/*
  Move is the function that will move the Bus with its speed. If the distance_remaining_ - Bus' speed is zero or negative value,
  the bus will arrive at the station in next round and then updating the new distance_remianing to have new distance to next stop.
  It also will return false to do loading and unloading the passengers.
  Other than above case, Bus should be move to next stop with the bus speed then return true.
*/

bool Bus::Move() {
  // This will check out bus is arriving at stop.
  if (distance_remaining_ - speed_ <= 0.0) {
    if (!is_route_change_) {  // outgoing route
      got_stop_ = true;
      distance_remaining_ = outgoing_route_->GetNextStopDistance();
      if (bus_outroute_counter_ != 0) {
        pre_stop_ = outgoing_route_->GetPreStop();
      } else {
        pre_stop_ = current_stop_;
      }
      outgoing_route_->NextStop();
      next_stop_ = outgoing_route_->GetTargetStop();
      bus_outroute_counter_++;
      return false;
    } else {  // incoming route
      got_stop_ = true;
      distance_remaining_ = incoming_route_->GetNextStopDistance();
      if (bus_inroute_counter_ != 0) {
        pre_stop_ = incoming_route_->GetPreStop();
      }
      incoming_route_->NextStop();
      next_stop_ = incoming_route_->GetTargetStop();
      bus_inroute_counter_++;
      return false;
    }
  } else {  // bus is not arriving stop
      got_stop_ = false;
      distance_remaining_ -= speed_;
      pre_stop_ = current_stop_;
      return true;
  }
}

/*
  UnloadPassenger is the actual function that will unload the passenger to the corresponding stop.
  This function will check out every passenger's the destination_stop id in the Bus with the current_stop, at which the bus is current.
  If ids are same, the passenger will unload form the stop. Otherwise the passenger will stay in the Bus.
*/

void Bus::UnloadPassenger(int stop_id) {
  int num = passengers_.size();
  if (num != 0) {
    for (int i =0; i < num; i++) {
      Passenger * pass1 = passengers_.front();
      passengers_.pop_front();
      if (pass1->GetDestination() == stop_id) {
        continue;
      } else {
        pass1->Update();
        passengers_.push_back(pass1);
      }
    }
  }
}
//  bool Refuel() {
//  This may become more complex in the future
//  fuel_ = max_fuel_;
//  }

/*
  * Pre-condtion : nothing.
  *  The Update is the function that is the most crucial part in Bus. The Update function will check out the possibility of moving the Bus.
  *  If the move function returns false, it indicates that the Bus is currently arriving at the station. The Update function will implement loading and unloading behavior for the passengers who are on Bus and from Stop.
  * <br> -Conditions- <br>
  * If (Move == false) <br>
  *             A -1) If the bus at the last stop in the outgoing_route_ or incoming_route_, it will unload the passengers who have destination stop for last stop of routes.<br>
  *             A -2) Otherwise, the bus in the somewhere station in outgoing_route_. The Bus will load/unload passengers from Bus passenger list and Stop. <br>
  *             A -3  If the bus has more bus_outroute_counter than a fixed number of outgoing_route_, it will be a signal for switching the distance to incoming_route's first distance and update the next Stop to incoming route first stop.
  *             After checking condition 1 and 2, it will set is_route_change variable to true not to get back to the outgoing_route again. Then updates the current_stop to destination_stop. <br>
  *             C-1) If the current_stop is the last stop of the incoming_route, it will do unloading the passenger to last stop then change the finish_flag to true.<br>
  *             C-2) if not, do just loading and unloading passengers in current stop.<br>
  * else (Move == true) -> just update the passengers who are in the Bus.
  */

void Bus::Update() {  //  using common Update form{-1,-1}at
  int pass_at_stop;
  Passenger* pass;
  if (!Move()) {  // arriving at station.
    current_stop_ = outgoing_route_->GetCurrentStop();
    Stop* last_stop = outgoing_route_->GetLastStop();
    if (IsAtLastStop(current_stop_->GetId(),
     last_stop->GetId()) || is_route_change_) {
      // drop off the passenger in the last stop
      if (bus_outroute_counter_ >= outgoing_route_->GetNumStops()) {
        UnloadPassenger(last_stop->GetId());
        bus_outroute_counter_ = 0;
        pre_stop_ = NULL;
        incoming_route_->NextStop();
        distance_remaining_ = incoming_route_->GetNextStopDistance();
      }
      is_route_change_ = true;  // now in incoming route
      current_stop_ = incoming_route_->GetCurrentStop();
      last_stop = incoming_route_->GetLastStop();
      // new
      if (pre_stop_ == NULL) {
        pre_stop_ = current_stop_;
        next_stop_ = incoming_route_->GetTargetStop();
      }
     //  check if the bus arrive at last station.
      if (IsAtLastStop(pre_stop_->GetId(), last_stop->GetId())) {
        UnloadPassenger(last_stop->GetId());  // unload passegner in last stop.
        finish_tag_ = true;  // bus finish its trip
        distance_remaining_ = 0;
        next_stop_ = current_stop_;
        pre_stop_ = current_stop_;
      } else {
        if ( passengers_.empty() ) {  // add checker capacity of bus
          // just pick up
          pass_at_stop = current_stop_->GetPassengersPresent();
          for (int i =0; i < pass_at_stop; i++) {
            pass = current_stop_->GetWaitingPassengers();
            if (LoadPassenger(pass)) {
              pass->GetOnBus();
            } else {
              current_stop_->AddPassengers(pass);
            }
          }
        } else {
          // drop off passenger and getting on passenger.
          UnloadPassenger(current_stop_->GetId());
          pass_at_stop = current_stop_->GetPassengersPresent();
          for (int i =0; i < pass_at_stop; i++) {
            pass = current_stop_->GetWaitingPassengers();
            if (LoadPassenger(pass)) {
              pass->GetOnBus();
            } else {
              current_stop_->AddPassengers(pass);
            }
          }
        }
      }
    } else {  // bus in the outgoing route.
        finish_tag_ = false;
        current_stop_ = outgoing_route_->GetCurrentStop();
        last_stop = outgoing_route_->GetLastStop();
         if (pre_stop_ == NULL) {
           pre_stop_ = current_stop_;
           next_stop_ = outgoing_route_->GetTargetStop();
         }
        if (passengers_.empty()) {  // add checker capacity of bus
          // just pick up
          pass_at_stop = current_stop_->GetPassengersPresent();
          for (int i =0; i < pass_at_stop; i++) {
            pass = current_stop_->GetWaitingPassengers();
            if (LoadPassenger(pass)) {
              pass->GetOnBus();
            } else {
              current_stop_->AddPassengers(pass);
            }
          }
        } else {
          // drop off passenger and getting on passenger.
          UnloadPassenger(current_stop_->GetId());
          pass_at_stop = current_stop_->GetPassengersPresent();
          for (int i =0; i < pass_at_stop; i++) {
            pass = current_stop_->GetWaitingPassengers();
            if (LoadPassenger(pass)) {
              pass->GetOnBus();
            } else {
              current_stop_->AddPassengers(pass);
            }
          }
        }
    }
  } else {  // bus is not arriving stop yet
    int size = passengers_.size();
    for (int i =0; i < size; i++) {  // updating all pasenger on bus
      Passenger * pass1 = passengers_.front();
      pass1->Update();
      passengers_.pop_front();
      passengers_.push_back(pass1);
    }
  }
  UpdateBusData();
}


void Bus::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
    it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}
/*
  UpdateBusData is the function that updates the BusData to contain new data for the visualization.
  Busdata will update the name of the bus, number of people who are on the bus and the max capacity of the Bus.
  Also, this function will update the position of the Bus.
  First case of position is that when the bus is generated, then UpdateBusData called, the bus automatically set to first stop.
  When the bus is at stop, the position of bus will be same as the current stop location (longitude, latitude)
  Other case is only the bus is moving. When the bus is heading to next stop, it will always have average of longitude and latitude of the previous and next stop.
*/
void Bus::UpdateBusData() {
  bus_data_.id = name_;
  bus_data_.num_passengers = passengers_.size();
  bus_data_.capacity = GetCapacity();
  Position bus_position;
  // When the bus started, the bus position will be at first station.
  if (current_stop_ == NULL && !is_route_change_) {
      bus_position.x = outgoing_route_->GetFirstNextStop()->GetLongitude();
      bus_position.y = outgoing_route_->GetFirstNextStop()->GetLatitude();;
  } else if (got_stop_) {  // whenever the bus arrives, bus will be at station.
      bus_position.x = current_stop_->GetLongitude();
      bus_position.y = current_stop_->GetLatitude();
  } else {  // otherwise bus is now on the way
    float next_x_position = next_stop_->GetLongitude();
    float next_y_position = next_stop_->GetLatitude();
    float pre_x_position = pre_stop_->GetLongitude();
    float pre_y_position = pre_stop_->GetLatitude();
    float ave_x = (next_x_position + pre_x_position) / 2;
    float ave_y = (next_y_position + pre_y_position) / 2;
    bus_position.x = ave_x;
    bus_position.y = ave_y;
  }
  bus_data_.position = bus_position;
}
/*
  GetBusData is the function that will return bus_data_ that contains current bus data (id, number of passengers on bus, current position of the bus )
*/
BusData Bus::GetBusData() {
  return bus_data_;
}
/*
  GetName is the function that returns the name of bus.
  This function will be used in the visualization.
*/
std::string Bus::GetName() const {
  return name_;
}
/*
  GetNextStop is the function that returns the next stop where the bus will head to.
  This function will be used in the visualization.
*/
Stop* Bus::GetNextStop() {
  if (next_stop_ == NULL) {
    next_stop_ = outgoing_route_->GetFirstNextStop();
  }
  return next_stop_;
}
/*
  GetNumPassengers is the function that returns how many people on the bus now.
  This function will be used in the visualization..
*/
size_t Bus::GetNumPassengers() {
  return passengers_.size();
}
/*
  GetCapacity is the function that returns the maximum number of people can be loaded on bus.
  This function will be used in the visualization and in bus class.
*/
int Bus::GetCapacity() {
  return passenger_max_capacity_ - passengers_.size();
}
/*
 This is function that checks whether or not the bus is arriving at the last stations
*/
bool Bus::IsAtLastStop(int current_stop_id, int last_stop_id) {
  return current_stop_id == last_stop_id;
}
