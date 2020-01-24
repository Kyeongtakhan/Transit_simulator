/**
 * @file r_local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_R_LOCAL_SIMULATOR_H_
#define SRC_R_LOCAL_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <string>
#include "src/simulator.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for Regression Local Simulator.
  *
  * This class is inherited from the Simulator. This class is only used for regression test
  *
  */
class RLocalSimulator : public Simulator {
 public:
   /**
   * @brief Sets up the member variable of Simulator class that will be used in simulator such as Stops, Routes, Generator.
   *
   * @return bool
   *
   */
  bool Start() override;
  /**
  * @brief Iterates fixed set of rounds with the simulation_time_elapsed_.
  * Also, this function will clone the route for the new Bus and Update every information of the Stop, Passenger in Stop, Bus.
  * Bus's location.
  *
  * @return bool
  *
  */
  bool Update() override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_R_LOCAL_SIMULATOR_H_
