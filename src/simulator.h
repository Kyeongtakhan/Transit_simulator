/**
* @file simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_SIMULATOR_H_
#define SRC_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <list>
#include <vector>

#include "src/bus.h"
#include "src/stop.h"
#include "src/route.h"
#include "src/passenger_generator.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for Simulator.
  *
  * The Simulator class is the abstract class and super class of the local simulator.
  *
  */

class Simulator {
 public:
   /**
   * @brief Pure virtual function of Start.
   *
   *
   */
  virtual bool Start() = 0;
  /**
  * @brief Pure virtual function of Update.
  *
  */
  virtual bool Update() = 0;

 protected:
  /**
  * @brief set of buses in the simulator
  */
  std::list<Bus *> active_buses_;
  /**
  * @brief set of stops in the simulator
  */
  std::list<Stop *> all_stops_;
  /**
  * @brief set of prototye routes used in generating bus with cloning method
  */
  std::vector<Route *> prototype_routes_;
  /**
  * @brief set of distances between stops
  */
  std::vector<double *> distance_between_sets_;
  /**
  * @brief set of passenger generator 
  */
  std::vector<PassengerGenerator *> passenger_generators_;
  // std::vector<std:list<double>> passenger_generation_probability_lists;
};

#endif  // SRC_SIMULATOR_H_
