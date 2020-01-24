/**
* @file rtest_configuration_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */
#include "src/rtest_configuration_simulator.h"
#include <vector>
#include <list>
#include <iostream>
#include <ostream>
#include <string>

#include "src/bus.h"
#include "src/route.h"
/*
  Regression test Configuration Simulator destructor will destruct object when object finishes its job.
*/
RtestConfigurationSimulator::~RtestConfigurationSimulator() {
}
/*
  This is function that will set the essential variables used in simulation. This function will take bus_timging vector for bus generation in routes
  Also, it will set up the prototype routes, and last time for bus generation.
*/
void RtestConfigurationSimulator::Start(std::vector<int> bus_timing) {
  // Get extra configuration value from the user
  bus_start_timings_ = bus_timing;
  prototypeRoutes_ = configptr_->GetRoutes();
  for (int i =0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
     prototypeRoutes_[i]->Report(out_);
     prototypeRoutes_[i]->UpdateRouteData();
  }
  // this routes contains sets of stops and routes from the text file.
  time_since_last_bus_.resize(bus_start_timings_ .size());
  for (int i = 0; i < static_cast<int>(time_since_last_bus_.size()); i++) {
      time_since_last_bus_[i] = 0;  // this will set up be zero.
  }
  simulationTimeElapsed_ = 0;
}
/*
  This is function that will update every domains (Bus,Routes, Stops in routes, Passenger in Bus and at stop).
  If the bus finish its trip, corresponding bus will be erased in simulation.
*/
void RtestConfigurationSimulator::Update() {
  simulationTimeElapsed_++;
  out_ << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
  out_ << "~~~~~~~~~~" << std::endl;

  out_ << "~~~~~~~~~~ Generating new busses if needed ";
  out_ << "~~~~~~~~~~" << std::endl;

  for (int i = 0; i < static_cast<int>(time_since_last_bus_.size()); i++) {
      // Check if we need to make a new bus
      if (0 >= time_since_last_bus_[i]) {
          Route * outbound = prototypeRoutes_[2 * i];
          Route * inbound = prototypeRoutes_[2 * i + 1];
          busses_.push_back(new Bus(
            std::to_string(busId), outbound->Clone(), inbound->Clone(), 60, 1));
          busId++;

          time_since_last_bus_[i] = bus_start_timings_[i];
      } else {
          time_since_last_bus_[i]--;
      }
  }
  out_ << "~~~~~~~~~ Updating busses ";
  out_ << "~~~~~~~~~" << std::endl;

  // Update busses
  for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
      busses_[i]->Update();
      if (busses_[i]->IsTripComplete()) {
          busses_.erase(busses_.begin() + i);
          continue;
      }
      busses_[i]->Report(out_);
  }

  out_ << "~~~~~~~~~ Updating routes ";
  out_ << "~~~~~~~~~" << std::endl;
  // Update routes
  for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
      prototypeRoutes_[i]->Update();
      prototypeRoutes_[i]->Report(out_);
  }
}
