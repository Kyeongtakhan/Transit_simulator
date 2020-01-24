/**
* @file route.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>
#include <string>
#include <vector>

#include "src/stop.h"
#include "./passenger_generator.h"
#include "src/data_structs.h"


class PassengerGenerator;
class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for Route.
  *
  * The Route class includes the implementations of cloning the Route, updaing the sets of Stops in Route, reporting all Stops in Route, setting the destination Stop to target Stops,
  * returning the destination (target) Stop, the distance from current Stop to destination (target) Stop, a number of stops in Route.
  *
  */
class Route {
 public:
   /**
   * @brief Constructs a Route with a standard name of Route, set of Stops, set of distances, the number of stops, and Passenger generation class.
   *
   *
   * @param[in] name string
   * @param[in] stops Stop**
   * @param[in] distances double*
   * @param[in] num_stops int
   * @param[in] pgptr PassengerGenerator*
   *
   */
  explicit Route(std::string name, Stop ** stops, double * distances
    , int num_stops, PassengerGenerator *);
    /**
    * @brief Clones the Prototype Route.
    * @details This function will copy the Prototype Route or route itself. Stops list and Distances list dynamically allocated in the memory to share the set of Stops, distances.
    * After copying the Route, it will return the new Route object.
    *
    * @return Route*
    *
    *
    */
  Route * Clone();

  /**
  * @brief Updates every Stop in the Route.
  */

  void Update();
  /**
  * @brief Reports the name of Route and number of Stops and every set of Stops.
  * @param[in] out ostream&
  */
  void Report(std::ostream &);
  /**
  * @brief Updates the destination Stop (target) to Next stop
  * @details Whenever NextStop function is called in Bus class, it will assign the next target Stop to destination Stop
  *
  * @return void
  *
  */
  void NextStop();
  /**
  * @brief Shows the Current Stops to Bus
  * @details if the destination Stop is NULL, it will automatically call NextStop function to assign the first Stop into current Stop.
  * Otherwise,it returns the destination Stop.
  * @return Stop*
  *
  */
  Stop * GetCurrentStop();
  /**
  * @brief Shows the distance between current Stop and destination Stops.
  * @details This function is used in the Bus class to update the remaining distance variable in Bus when the Bus arrving at destination Stop.
  *
  * @return double
  *
  */
  double GetNextStopDistance();
  /**
  * @brief Shows the fixed last Stop in the Route.
  * @details This function is used in the Bus class to check out whether or not the Bus arrives at the last Stop.
  *
  * @return Stop*
  *
  */
  Stop* GetLastStop() const;
  /**
  * @brief Shows a fixed number Stops in the Route.
  * @details   The purpose of this function is to switching the routes. It will be used with the Bus class member variable (Bus_outroute_counter) to check out the bus is at last station
  *
  * @return int
  *
  */
  int GetNumStops() const;
  /**
  * @brief returns previous Stop* of the bus.
  * @details The purpose of this function is to calculate the position of the bus. So, this function will be called by Bus classes for BusData position.
  *          When the bus is on the way to target stop, previous stop will be pointing to previous stop. Ex) 4(Pre) --- Bus ---- 5(Target)
  *                                                                                                          4 (Bus)   prev and current should be same.
  *
  *
  * @return Stop*
  *
  */
  Stop * GetPreStop();
  /**
  * @brief returns Next Stop* of the bus.
  * @details The purpose of this function is to calculate the position of the bus. So, this function will be called by Bus classes for BusData position.
  *
  * @return Stop*
  *
  */
  Stop * GetTargetStop();
  /**
  * @brief returns the first stop of the Bus.
  * @details The purpose of this function is that when visulizer request the NextStop point when the bus is not updated or started, this function will be used in Bus's GetNextStop function.
  * @return Stop*
  *
  */
  Stop * GetFirstNextStop() const;
  /**
  * @brief returns the name of the Route.
  * @details The purpose of this function is to store the data into RouteData.
  * @return string
  *
  */
  std::string GetName();
  /**
  * @brief return list of Stop*.
  * @details The purpose of this function is to store the set of StopData into RouteData.
  * @return list<Stop*>
  *
  */
  std::list<Stop*> GetStops();
  /**
  * @brief Update RouteData to include new information for visualzation.
  * @details The purpose of this function is to store the set of StopData into RouteData.
  * To be specific, stores name of route and StopData vector, containing set of StopData (id, position. number of People waiting for bus).
  * @return list<Stop*>
  *
  */
  void UpdateRouteData();
  /**
  * @brief return RouteData struct for visualization.
  * @details The purpose of this function is to provide the updated situation to visualizer to visualize.
  * @return list<Stop*>
  *
  */
  RouteData GetRouteData();

 private:
  int GenerateNewPassengers();       // generates passengers on its route
  PassengerGenerator * generator_;
  std::list<Stop *> stops_;
  std::list<double> distances_between_;  // length = num_stops_ - 1
  std::string name_;
  int num_stops_;
  Stop * destination_stop_;  // contain next stop for bus.
  Stop * final_destination_stop_;  // shows the final destination
  // double trip_time_; // derived data - total distance travelled on route
  RouteData route_data_;  // container that contains the data about the route
  Stop* first_next_stop_;  // being used in Bus class.
};
#endif  // SRC_ROUTE_H_
