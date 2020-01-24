/**
* @file deterministic_passenger_factory.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_DETERMINISTIC_PASSENGER_FACTORY_H_
#define SRC_DETERMINISTIC_PASSENGER_FACTORY_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/passenger.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the deterministic passenger factory.
 *
 * This class is only used for regression test to generate same passenger into stop everytime
 */
class DeterministicPassengerFactory {
 public:
 /**
  * @brief Generation of a passenger with fixed name evertime.
  *
  * This function will be used for regression test purpose.
  *
  * @param[in] curr_stop Current stop, left bound (not-inclusive)
  * @param[in] last_stop Last stop, right bound (inclusive)
  *
  * @return Passenger object with name and destination.
  */
  static Passenger * Generate(int, int);
 private:
 /**
  * @brief Generation of fixed passenger name from prefix, stems and suffixes.
  *
  * @return fixed passenger name.
  */
  static std::string NameGeneration();
};
#endif  // SRC_DETERMINISTIC_PASSENGER_FACTORY_H_
