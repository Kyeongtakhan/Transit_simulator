/**
* @file configuration_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */
#ifndef SRC_CONFIGURATION_SIMULATOR_H_
#define SRC_CONFIGURATION_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <list>
#include <string>
#include <ostream>

#include "src/config_manager.h"
class Route;
class Bus;
class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for configuration_simulator.
  *
  * The configuration_simulator will set up the necessary domains based on the configuration text files and user requests from the line argument, and update every domains.
  *
  */
class ConfigurationSimulator {
 public:
  /**
  * @brief ConfigurationSimulator constructor will take two arguements that are ConfigManager to open and read the configurations
  * , and ostream stream if user want to redirect output to textfile.
  * @param[in] cm ConfigManager*
  * @param[in] fd ostream&*
  */
  explicit ConfigurationSimulator(ConfigManager* cm,
     std::ostream& fd): out_(fd) {
    configptr_ = cm;
  }
  /**
  * @brief Destructor when the object finishes their job, object itself will be destructed
  */
  ~ConfigurationSimulator();
  /**
  * @brief Sets up the essential variables and takes vector for bus generating timing.
  * Sets up the prototye Routes to be reused in every bus.
  *
  * @param[in] bus_timing vector<int>
  *
  */
  void Start(std::vector<int>);
  /**
  * @brief Iterates set of rounds depending on either user defined rounds or default simulation rounds by updating the simulation_time_elapsed_.
  * Also Update function will update every domains (Bus,Routes, Stops in routes, Passenger in Bus and at stop). Bus will be erased only when bus finishes its trip.
  *
  *
  */
  void Update();

 private:
   /**
   * @brief configManager to get the routes from the config_text
   */
  ConfigManager* configptr_;
  /**
  * @brief controller for bus generation
  */
  std::vector<int> bus_start_timings_;
  /**
  * @brief checker for bus generation
  */
  std::vector<int> time_since_last_bus_;
  /**
  * @brief contains prototype routes from config_text.
  */
  std::vector<Route *> prototypeRoutes_;
  /**
  * @brief set of buses in simulation
  */
  std::vector<Bus *> busses_;
  /**
  * @brief output files that user wants to redirect output
  * default: cout
  * user-defined: text files
  */
  std::ostream& out_;
  /**
  * @brief simulation rounds
  */
  int simulationTimeElapsed_;
  /**
  * @brief standard bus Id
  */
  int busId = 1000;
};
#endif  // SRC_CONFIGURATION_SIMULATOR_H_
