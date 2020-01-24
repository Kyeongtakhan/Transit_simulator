/**
 * @file capture_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */
#ifndef SRC_CAPTURE_SIMULATOR_H_
#define SRC_CAPTURE_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include <fstream>
#include "src/simulator.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for Capture Local Simulator. This simulator will capture every output of classes except passenger generator.
  *
  * This class is inherited from the Simulator.
  *
  */
class CaptureLocalSimulator : public Simulator {
 public:
   /**
   * @brief CaptureLocalSimulator constructor that constructs with the ofstream as parameter to capture the output of the simulator.
   *
   *
   */
  explicit CaptureLocalSimulator(std::ofstream& fd): out_(fd) {}
  /**
  * @brief Sets up the member variable of CaptureSimulator class that will be used in Capture Local simulator such as Stops, Routes, Generator.
  *
  * @return bool
  *
  */
  bool Start() override;
  /**
  * @brief Iterates fixed set of rounds with the simulation_time_elapsed_.
  * Also, this function will clone the route for the new Bus and Update every information of the Stop, Passenger in Stop, Bus.
  * Bus's location. Also, the output of the update function will be captured in the given name of file or default file if the user doesn't give file name.
  * @return bool
  *
  */
  bool Update() override;

 private:
  std::vector<int> bus_counters_;
  // timer to generate bus
  std::vector<int> bus_start_timings_;
  // checker for bus generating
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
  std::ofstream& out_;
};

#endif  // SRC_CAPTURE_SIMULATOR_H_
