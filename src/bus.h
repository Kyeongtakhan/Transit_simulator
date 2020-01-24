/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <list>
#include <string>

#include "src/passenger.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/data_structs.h"

class Route;
class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for Bus.
  * The Bus class includes the implementations of moving, updating, information about Bus, loading / unloading of Passenger.
  */
class Bus {
 public:
   /**
   * @brief Constructs a Bus with a standard name, outgoing route, incoming route, maximum capacity of Bus, and speed.
   * @param[in] name string
   * @param[in] out Route*
   * @param[in] in Route*
   * @param[in] capacity int
   * @param[in] speed double
   *
   */
  explicit Bus(std::string name, Route * out, Route * in, int capacity = 60,
                                                 double speed = 1);
  /**
  * @brief Loads Passengers on the Passenger list in the Bus.
  * @pre The size of passenger list + one passenger is greater than or equal to the maximum capacity of Bus, return false.
  * @details Before loading the passenger, this function will check out the current available seats in Bus.
  * If capacity is over, it will return false, otherwise will load Passengers into Bus.
  *
  * @param[in] new_passenger Passenger*
  * @return bool
  *
  */
  bool LoadPassenger(Passenger *);
  /**
  * @brief Moves the Bus with its speed.
  * If the remaining distance - speed of Bus is zero or less than zero, the Bus arrives at the station and then updating the new remaining distance to be new distance to next stop.
  * It also will return false to do loading and unloading the passengers, otherwise, Bus should be move to next stop with the bus speed then return true.
  * @return bool
  */

  bool Move();
  /**
  * @brief Updates the passengers information in Bus, loads / unloads passengers from the bus or to stop, and check out whether or not the Bus switch the routes.
  * @details
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
  * @return bool
  */
  void Update();
  /**
  * @brief Reports the details information of Bus.
  *  This function is further used with outstream.
  *
  * @param[in] out ostream&
  *
  */
  void Report(std::ostream &);
  /**
  * @brief Checks that Bus finishes the trip.
  *
  * This function will return true when the bus finishes up both routes, which are outgoing route and incoming_route.
  * The variable finish_tag_ is the member variable in Bus class and it will be changed only when the bus finishes up all routes in Update function.
  * If finish_tag_ is true, the bus finishes its trip.
  * @return bool
  */
  bool IsTripComplete();
  /**
  * @brief Unloads the Passengers to the corresponding Stop.
  * @pre The size of Passenger list in the Bus is zero, This function will be skipped automatically.
  * @details Check out every Passenger's destination Stop id with the current Stop id, at which the bus is current.
  * If ids are the same, the Passenger will be unloaded to the Stop. Otherwise the passenger will stay in the Bus.
  *
  * @param[in] stop_id int
  *
  */
  void UnloadPassenger(int);
  /**
  *  UpdateBusData is the function that updates the BusData to contain new data for the visualization.
  *  Busdata will update the name of the bus, number of people who are on the bus and the max capacity of the Bus.
  *  Also, this function will update the position of the Bus.
  *  First case of position is that when the bus is generated, then UpdateBusData called, the bus automatically set to first stop.
  *  When the bus is at stop, the position of bus will be same as the current stop location (longitude, latitude)
  *  Other case is only the bus is moving. When the bus is heading to next stop, it will always have average of longitude and latitude of the previous and next stop.
  *  @return void
  */
  void UpdateBusData();
  /**
  * @brief GetBusData is the function that will return bus_data_ that contains current bus data (id, number of passengers on bus, current position of the bus).
  *
  * @return BusData
  *
  */
  BusData GetBusData();
  /**
  * @brief GetName is the function that returns the name of bus.
    This function will be used in the visualization.
  *
  * @return string
  *
  */
  std::string GetName() const;
  /**
  * @brief   GetNextStop is the function that returns the next stop where the bus will head to.
  *  This function will be used in the visualization.
  *
  * @return Stop*
  *
  */
  Stop* GetNextStop();
  /**
  * @brief     GetNumPassengers is the function that returns how many people on the bus now.
  *  This function will be used in the visualization..
  *
  * @return Stop*
  *
  */
  size_t GetNumPassengers();
  /**
  * @brief   GetCapacity is the function that returns the maximum number of people can be loaded on bus.
  *  This function will be used in the visualization.
  *
  * @return Stop*
  *
  */
  int GetCapacity();
  /**
  * @brief Checks whether or not the bus is arriving at the last stations
  *
  * @param[in] current_stop_id int
  * @param[in] last_stop_id int
  * @return bool
  *
  */
  bool IsAtLastStop(int, int);

 private:
   /**
   * @brief set of passengers on bus
   */
  std::list<Passenger *> passengers_;
  /**
  * @brief maximum capacity that bus can take
  */
  int passenger_max_capacity_;
  /**
  * @brief name of bus
  */
  std::string name_;
  /**
  * @brief speed of bus could also be called "distance travelled in one time step"
  */
  double speed_;
  /**
  * @brief bus's outbound route. First route
  */
  Route * outgoing_route_;
  /**
  * @brief bus's inbound route. second route
  */
  Route * incoming_route_;
  /**
  * @brief represents the remaining distance to next destination stop
  */
  double distance_remaining_;
  /**
  * @brief represents the bus finishes the outbound trip if true, otherwise bus is on outbound
  */
  bool is_route_change_;
  /**
  * @brief represents the bus finishes its trip if true, otherwise bus is still travelling
  */
  bool finish_tag_;
  /**
  * @brief represents the index of the inroute.
  */
  int bus_inroute_counter_;
  /**
  * @brief represents the index of the outroute.
  */
  int bus_outroute_counter_;
  /**
  * @brief  Pointing to bus's current stop
  */
  Stop* current_stop_;
  /**
  * @brief Pointing to bus's next stop
  */
  Stop* next_stop_;
  /**
  * @brief Pointing to bus's previous stop
  */
  Stop* pre_stop_;
  /**
  * @brief represents whether or not the bus is arrvining at stop
  */
  bool got_stop_;
  /**
  * @brief bus_data_ for visualization
  */
  BusData bus_data_;
};
#endif  // SRC_BUS_H_
