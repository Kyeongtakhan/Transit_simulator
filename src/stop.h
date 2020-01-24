/**
* @file stop.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */
#ifndef SRC_STOP_H_
#define SRC_STOP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>

#include "src/bus.h"
#include "src/passenger.h"

class Bus;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for Stop.
  *
  * The Stop class includes the implementations of adding Passengers, updating the passengers information in Stop, reporting information about Stop.
  *
  */
class Stop {
 public:
   /**
   * @brief Constructs a Stop with a stop id, longitude, latitude.
   *
   *
   * @param[in] id int
   * @param[in] longitude double
   * @param[in] latitude double
   *
   */
  explicit Stop(int = 1, double = 44.973723, double = -93.235365);
  /**
  * @brief Return Stop id .
  *
  * @return int
  *
  */
  int GetId() const;
  /**
  * @brief Adds the passenger into the passenger list in the Stop.
  * This function is used when the passenger is generated or the bus can not load passengers on the bus due to the capacity.
  * @param[in] pass Passenger*
  * @return int
  *
  *
  */
  int AddPassengers(Passenger *);
  /**
  * @brief Updates the Passenger's information in the Stop.
  *
  *
  *
  */
  void Update();
  /**
  * @brief Report all information in the Stop.
  * @param[in] out ostream&
  *
  */
  void Report(std::ostream &) const;
  /**
  * @brief Returns size of Passenger list in the Stop.
  *
  * @return int
  */
  int GetPassengersPresent() const;
  /**
  * @brief Returns passenger* who is waiting at the stop for Bus.
  *  This function will be used in the Bus function to load the specific passenger on Bus.
  * @return Passenger*
  */
  Passenger* GetWaitingPassengers();
  /**
  * @brief Returns longitude of the stop.
  *  This function will be used in either BusData struct and RouteData to store the data.
  * @return double
  */
  double GetLongitude() const;
  /**
  * @brief Returns latitude of the stop.
  *  This function will be used in either BusData struct and RouteData to store the data.
  * @return double
  */
  double GetLatitude() const;

 private:
  int id_;
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  double longitude_;
  double latitude_;  // are we using long/lat coords?
  // derived information - not needed depending on passengers_
  // data structure implementation?
  // int passengers_present_;
};
#endif  // SRC_STOP_H_
