/**
* @file passenger_generator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_GENERATOR_H_
#define SRC_PASSENGER_GENERATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <list>

#include "src/passenger_factory.h"
#include "src/stop.h"

class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for passenger_generator.
  *
  * This passenger_generator class is the abstract class and super class of the random_passenger_generator.
  *
  */
class PassengerGenerator {
 public:
   /**
   * @brief Constructs a PassengerGenerator with a list of probabilities , list of Stops.
   *
   *
   * @param[in] probs list<double>
   * @param[in] stops list<Stop*>
   *
   */
  PassengerGenerator(std::list<double>, std::list<Stop *>);
  /**
  * @brief Pure virtual function of GeneratePassengers .
  * Makes the class abstract, cannot instantiate and forces subclass override
  *
  */

  virtual int GeneratePassengers() = 0;  // pure virtual

 protected:
   /**
   * @brief Set of probability that how the passenger likely shows up the stops
   */
  std::list<double> generation_probabilities_;
  /**
  * @brief Set of stops in route
  */
  std::list<Stop *> stops_;

  // should we be using a singleton here somehow?
  // PassengerFactory * pass_factory;
};
#endif  // SRC_PASSENGER_GENERATOR_H_
