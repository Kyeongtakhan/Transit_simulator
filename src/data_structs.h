/**
* @file data_structs.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_DATA_STRUCTS_H_
#define SRC_DATA_STRUCTS_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
/*******************************************************************************
 * Struct Definitions
 ******************************************************************************/
 /**
  * @brief Position struct that will be used in BusData struct and StopData to shows the location of buses and stops.
  */
struct Position {
  /*! Constructor for Position with default 0 and 0 */
    Position() : x(0), y(0) {}
  /*! represents the Longitude of the position */
    float x;
      /*! represents the Latitude of the position */
    float y;
};
/**
 * @brief BusData struct contains the name of Bus, current position of bus, number of passengers in the bus, the available seats in the bus.
   This struct will be utilized for the visualization
 */
struct BusData {
    /*! Constructor for BusData that contains id,
     position struct, number of people, capacity */
    BusData() : id(""), position(Position()), num_passengers(0), capacity(0) {}
    /*! represents id of the bus */
    std::string id;
    /*! represents position (Latitude and Longitude) of the bus */
    Position position;
    /*! represents number of people on the bus */
    int num_passengers;
    /*! represents the number of available seats */
    int capacity;
};
/**
 * @brief StopData struct contains the id of Stop, location of stop, and number of passengers at stops.
   This struct will be utilized for the visualization
 */
struct StopData {
    /*! Constructor for StopData that contains id of stop,
     position of stop, number of people at stop */
    StopData() : id(""), position(Position()), num_people(0) {}
    /*! represents id of stop */
    std::string id;
    /*! represents position (Latitude and Longitude) of the stop */
    Position position;
    /*! represents number of people at stop */
    int num_people;
};
/**
 * @brief RouteData struct contains the id of route, and set of stops.
   This struct will be utilized for the visualization
 */
struct RouteData {
    /*! Constructor for RouteData that contains id of route, set of StopData */
    RouteData() : id(""), stops(std::vector<StopData>(0)) {}
    /*! represents id of route */
    std::string id;
    /*! represents set of StopData */
    std::vector<StopData> stops;
};

#endif  // SRC_DATA_STRUCTS_H_
