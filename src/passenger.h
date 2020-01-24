/**
* @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for Passenger.
  *
  * This includes the base implementations and information of Passerger.
  * This is required to generate the Passengers.
  */
class Passenger {  // : public Reporter {
 public:
  /**
  * @brief Constructs a passenger with a standard name and id.
  *
  *
  * @param[in] destination_stop_id int
  * @param[in] name string
  *
  */
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
   * @brief Updates the time of the passenger waiting.
   *
   * @details This function will update passenger's time on the bus or either time at Stop.
   * If Pasenger is on the bus, it will increase the time on the bus.
   * Otherwise, increases the waiting time at station.
   *
   *
   */
  void Update();
  /**
   * @brief Sets passenger's time on bus to 1.
   *
   * @details This function will change passenger's time on the bus to 1. The time on bus == 1 meaning is that the passenger is on the Bus now.
   *
   *
   */
  void GetOnBus();
    /**
   * @brief Returns the total passenger waiting time in Stop and Bus.
   *
   * @details This function will return integer value that shows the total time of passenger wating for Bus at Stop and the time on Bus.
   * @return int
   *
   *
   */
  int GetTotalWait() const;
  /**
   * @brief Returns Boolean value if passenger is on bus.
   *
   * @details This function will check out the time on bus. If the time_on_bus is greater than 0.
   * Then return true. Ohterwise false.
   * @return bool
   *
   */
  bool IsOnBus() const;
  /**
   * @brief Returns passenger's target destination id.
   *
   * @details It will will return the passenger's destination id.
   * @return int
   *
   */
  int GetDestination() const;
  /**
   * @brief Reports the information of passenger.
   *
   * @details This function will report passenger's information.
   *
   */
  void Report(std::ostream &) const;

 private:
   /**
    * @brief name of passenger
    */
  std::string name_;
  /**
   * @brief stop id that passenger wants to go
   */
  int destination_stop_id_;
  /**
   * @brief time that the passenger waits for bus
   */
  int wait_at_stop_;
  /**
   * @brief time that the passenger is on the bus
   */
  int time_on_bus_;
  /**
   * @brief unique identificator
   */
  int id_;
  /**
   * @brief global count, used to set ID for new instances
   */
  static int count_;
};
#endif  // SRC_PASSENGER_H_
