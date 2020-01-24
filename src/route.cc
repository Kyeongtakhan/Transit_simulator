/**
* @file route.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */
#include "src/route.h"
/*
  Route constructor will contains the stops** and double*, final_destination_stop_ for stop* pointing to last state in corresponding route
  destination_stop_ is generated as Null at the first time.
*/

Route::Route(std::string name, Stop ** stops, double * distances
  , int num_stops, PassengerGenerator* pgptr) {
  for (int i = 0; i < num_stops; i++) {
    stops_.push_back(stops[i]);
    // new
    if (i == 1) {
      first_next_stop_ = stops[i];
    }
    // end new
  }
  for (int i = 0; i < num_stops - 1; i++) {
    distances_between_.push_back(distances[i]);
  }

  name_ = name;
  num_stops_ = num_stops;
  generator_ = pgptr;
  // This always sets to last stop.
  final_destination_stop_ = stops_.back();
  // destination stop start NUll pointer
  destination_stop_ = NULL;
}

/*
  Clone is the function that will do deep copying the prototype Route object.
*/

Route* Route::Clone() {
  // Set Deep copy for stop and distances.
  Stop ** copy_stops = new Stop *[num_stops_];
  int count = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
  it != stops_.end(); it++) {
    copy_stops[count] = (*it);
    count++;
  }

  double* copy_distances = new double[num_stops_ -1];
  for (int i = 0; i < num_stops_ -1; i++) {
    double temp = distances_between_.front();
    copy_distances[i] = temp;
    distances_between_.pop_front();
    distances_between_.push_back(temp);
  }

  Route* clone_route = new Route(name_, copy_stops
    , copy_distances, num_stops_ , generator_);
  return clone_route;
}
/*
  Update function will updates the all stops in the routes and also generates the new passengers in routes.
*/

void Route::Update() {
  for ( std::list<Stop *>::iterator it = stops_.begin();
  it != stops_.end(); it++) {
    (*it)->Update();
  }
  GenerateNewPassengers();
}

/*
  NextStop is the function that whenever NextStop function is called in Bus class, it will assign the next target stop to destination_stop_
*/
void Route::NextStop() {
    destination_stop_ = stops_.front();  // get the front stop in the list.
    stops_.pop_front();
    stops_.push_back(destination_stop_);  // push back to stop list.
}
/*
  TargetStop is the similar function with NextStop function. However, GetTargetStop always returns the next stop of the Bus.
  This returned value will be used the BusData for finding the position of the Bus.
*/
Stop* Route::GetTargetStop() {
  return stops_.front();
}

void Route::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Num stops: " << num_stops_ << std::endl;
  int stop_counter = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
  it != stops_.end(); it++) {
    (*it)->Report(out);
    stop_counter++;
  }
}
/*
  This is the function that geneates passenger into stops.
*/

int Route::GenerateNewPassengers() {
  int num_pass = generator_->GeneratePassengers();
  return num_pass;
}

/*
  GetCurrentStop is the function that check out if the destination_stop_ is NULL, it will automatically call NextStop function.
  Because in my code, it the only one case that the bus is generated. Finally return destination_stop_.
*/

Stop * Route::GetCurrentStop() {
  if (destination_stop_ == NULL) {
    NextStop();
  }
  return destination_stop_;
}
/*
  GetLastStop is the function that will return last station of the routes.
  The purpose of this function is to check out whether or not the bus is at the last stop by comparing the stop id with the current stop.
*/
Stop * Route::GetLastStop() const {
  return final_destination_stop_;
}

/*
  GetNextStopDistance is the function that will return distances between current_stop and target_stop.
  It is used in the Bus class to updated the distance_remaining_ variable in Bus.
*/
double Route::GetNextStopDistance() {
    double temp = distances_between_.front();
    distances_between_.pop_front();
    distances_between_.push_back(temp);
    return temp;
}
/*
  GetNumStops is the function that will return num_stops in the routes.
  The purpose of this function is to switching the routes. It will be used with the Bus class member variable (Bus_outroute_counter) to check out the bus is at last station
*/
int Route::GetNumStops() const {
  return num_stops_;
}
/*
  GetPreStop is the function that will return previous stop that the bus has.
  The purpose of this function is to calculate the position of the bus.
*/
Stop* Route::GetPreStop() {
  return stops_.back();
}
/*
  GetFirstNextStop is the function that will return previous stop only when the bus is generated.
  The purpose of this function is to point bus position to the first stop position.
*/
Stop* Route::GetFirstNextStop() const {
  return first_next_stop_;
}
/*
  GetName is the function that will return the route name.
  The purpose of this function is to store the RouteData for visualization.
*/
std::string Route::GetName() {
  return name_;
}
/*
  GetStops is the function that will return list of stops in the route.
  The purpose of this function is to store the RouteData for visualization.
*/
std::list<Stop*> Route::GetStops() {
  return stops_;
}
/*
  UpdateRouteData is the function that stores the updated route data to RouteData struct.
  To be specific, stores name of route and StopData vector, containing set of StopData (id, position. number of People waiting for bus).
*/
void Route::UpdateRouteData() {
  route_data_.id = name_;
  std::vector<StopData> stops_vect;
  for (std::list<Stop*>::iterator it = stops_.begin();
  it != stops_.end(); it++ ) {
    StopData stop_temp;
    stop_temp.id = std::to_string((*it)->GetId());
    Position stop_pos;
    stop_pos.x = (*it)->GetLongitude();
    stop_pos.y = (*it)->GetLatitude();
    stop_temp.position = stop_pos;
    stop_temp.num_people = (*it)->GetPassengersPresent();
    stops_vect.push_back(stop_temp);
  }
  route_data_.stops = stops_vect;
}
/*
  GetRouteData is the function that returns Routedata.
*/
RouteData Route::GetRouteData() {
  return route_data_;
}
