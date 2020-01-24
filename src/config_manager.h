/**
* @file config_manager.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 * @author of modification to the file: Kyeongtak Han.
 */
#ifndef SRC_CONFIG_MANAGER_H_
#define SRC_CONFIG_MANAGER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <vector>
#include <string>


class Route;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for ConfigManager.
  *
  * This class wil read the customized configuration text file and give the generated route based on text file.
  *
  */
class ConfigManager {
 public:
  /**
   * @brief Constructor takes nothing bus it will set the routes_ meber variables to empty Route pointer vector container
   *
  */
  ConfigManager();
  /**
   * @brief Destructor will destruct the object when its job is finished
   *
  */
  ~ConfigManager();
  /**
   * @brief Reads the customized configuration text files and generated the routes and stored the new generated routes to member variables.
   *
   * @param[in] filename string
   *  @return void
   *
  */
  void ReadConfig(const std::string filename);
  /**
   * @brief Returns the new generated Route vector.
   *
  *  @return vector<Route*>
   *
  */
  std::vector<Route *> GetRoutes() const { return routes_; }

 private:
  std::vector<Route *> routes_;  // generated route container
};

#endif  // SRC_CONFIG_MANAGER_H_
