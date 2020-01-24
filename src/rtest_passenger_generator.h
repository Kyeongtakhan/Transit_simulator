/**
 * @file rtest_passenger_generator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_RTEST_PASSENGER_GENERATOR_H_
#define SRC_RTEST_PASSENGER_GENERATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <random>
#include <ctime>

#include "src/passenger_generator.h"
#include "src/stop.h"

class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for regresion test passenger_generator.
  *
  * This class is inherited from the passenger_generator.
  *
  */
class RtestPassengerGenerator : public PassengerGenerator{
 public:
   /**
   * @brief Constructs a RandomPassengerGenerator with a list of probabilities and list of Stops.
   *
   *
   * @param[in] probs list<double>
   * @param[in] stops list<Stop*>
   *
   */
  RtestPassengerGenerator(std::list<double>, std::list<Stop *>);
  /**
  * @brief Generate the passengers based on the probabilty that passenger shows up at Stop and random generatoion value.
  * This function would try to generate passenger randomly but the generated passengers are all the same.
  * @return bool
  *
  */
  int GeneratePassengers() override;

 private:
  static std:: minstd_rand0 my_rand;
};

#endif  // SRC_RTEST_PASSENGER_GENERATOR_H_
