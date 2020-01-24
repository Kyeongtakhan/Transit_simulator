// Copyright 2019 Kyeongtak Han


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include "../src/passenger.h"
#include "../src/data_structs.h"
#include "../src/bus.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class FailTests : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(FailTests, FailRouteConstructor) {
  Stop** set_test_stops1;
  Stop** set_test_stops2;
  std::list<Stop*> stops1_test_list;
  std::list<Stop*> stops2_test_list;
  Stop * stop_CC_EB_test_1;
  Stop * stop_CC_EB_test_2;
  Stop * stop_CC_WB_test_1;
  Stop * stop_CC_WB_test_2;
  double * CC_EB_test_distances;
  double * CC_WB_test_distances;
  std::list<double> CC_EB_test_probs;
  std::list<double> CC_WB_test_probs;
  set_test_stops1 = new Stop*[2];
  set_test_stops2 = new Stop*[2];
  stop_CC_EB_test_1 = new Stop(0, 22.972392, -63.243774);
  stop_CC_EB_test_2 = new Stop(1, 23.973580, -62.235071);
  stop_CC_WB_test_1 = new Stop(2, 24.975837, -60.222174);
  stop_CC_WB_test_2 = new Stop(3, 22.972392, -63.243774);
  stops1_test_list.push_back(stop_CC_EB_test_1);
  set_test_stops1[0] = stop_CC_EB_test_1;
  stops1_test_list.push_back(stop_CC_EB_test_2);
  set_test_stops1[1] = stop_CC_EB_test_2;
  stops2_test_list.push_back(stop_CC_WB_test_1);
  set_test_stops2[0] = stop_CC_WB_test_1;
  stops2_test_list.push_back(stop_CC_WB_test_2);
  set_test_stops2[1] = stop_CC_WB_test_2;
  CC_EB_test_distances = new double[1];
  CC_WB_test_distances = new double[1];
  CC_EB_test_distances[0] = 4;
  CC_WB_test_distances[0] = 2;
  double probability1 = 1.0;
  double last_probability2 = 1.0;
  double probability3 = 1.0;
  double last_probability4 = 1.0;
  EXPECT_LT(probability1 + 1.0, 1) << "Expect less than 1.0 \n";
  EXPECT_EQ(last_probability2 + 1.0, 1) << "Expect equalt to 1.0 \n";
  EXPECT_LT(probability3 + 1.0, 1) << "Expect less than 1.0 \n";
  EXPECT_EQ(last_probability4 + 1.0, 1) << "Expect equalt to 1.0 \n";
  CC_EB_test_probs.push_back(.7);
  CC_EB_test_probs.push_back(.99);
  CC_WB_test_probs.push_back(.3);
  CC_WB_test_probs.push_back(.99);
  EXPECT_EQ(CC_EB_test_probs.back(), 0) <<
  "Should be zero prob at last station\n";
  EXPECT_EQ(CC_WB_test_probs.back(), 0) <<
  "Should be zero prob at last station\n";
  delete stop_CC_EB_test_1;
  delete stop_CC_EB_test_2;
  delete stop_CC_WB_test_1;
  delete stop_CC_WB_test_2;
  delete [] CC_EB_test_distances;
  delete [] CC_WB_test_distances;
  delete [] set_test_stops1;
  delete [] set_test_stops2;
}
TEST_F(FailTests, RouteIndexWithBusTiming) {
  Stop** set_test_stops1;
  Stop** set_test_stops2;
  std::list<Stop*> stops1_test_list;
  std::list<Stop*> stops2_test_list;
  Stop * stop_CC_EB_test_1;
  Stop * stop_CC_EB_test_2;
  Stop * stop_CC_WB_test_1;
  Stop * stop_CC_WB_test_2;
  double * CC_EB_test_distances;
  double * CC_WB_test_distances;
  std::list<double> CC_EB_test_probs;
  std::list<double> CC_WB_test_probs;
  RandomPassengerGenerator * CC_EB_generator;
  RandomPassengerGenerator * CC_WB_generator;
  Route* TEST_EB;
  Route* TEST_WB;
  set_test_stops1 = new Stop*[2];
  set_test_stops2 = new Stop*[2];
  stop_CC_EB_test_1 = new Stop(0, 22.972392, -63.243774);
  stop_CC_EB_test_2 = new Stop(1, 23.973580, -62.235071);
  stop_CC_WB_test_1 = new Stop(2, 24.975837, -60.222174);
  stop_CC_WB_test_2 = new Stop(3, 22.972392, -63.243774);
  stops1_test_list.push_back(stop_CC_EB_test_1);
  set_test_stops1[0] = stop_CC_EB_test_1;
  stops1_test_list.push_back(stop_CC_EB_test_2);
  set_test_stops1[1] = stop_CC_EB_test_2;
  stops2_test_list.push_back(stop_CC_WB_test_1);
  set_test_stops2[0] = stop_CC_WB_test_1;
  stops2_test_list.push_back(stop_CC_WB_test_2);
  set_test_stops2[1] = stop_CC_WB_test_2;
  CC_EB_test_distances = new double[1];
  CC_WB_test_distances = new double[1];
  CC_EB_test_distances[0] = 4;
  CC_WB_test_distances[0] = 2;
  CC_EB_test_probs.push_back(.7);
  CC_EB_test_probs.push_back(0);
  CC_WB_test_probs.push_back(.3);
  CC_WB_test_probs.push_back(0);
  CC_EB_generator =
  new RandomPassengerGenerator(CC_EB_test_probs, stops1_test_list);
  CC_WB_generator =
  new RandomPassengerGenerator(CC_WB_test_probs, stops2_test_list);
  TEST_EB = new Route("test1-EB", set_test_stops1
  , CC_EB_test_distances, 2, CC_EB_generator);
  TEST_WB = new Route("test1-WB"
  , set_test_stops2, CC_WB_test_distances, 2, CC_WB_generator);

  Stop** set_test2_stops1;
  Stop** set_test2_stops2;
  std::list<Stop*> stops1_test2_list;
  std::list<Stop*> stops2_test2_list;
  Stop * stop_CC_EB_test2_1;
  Stop * stop_CC_EB_test2_2;
  Stop * stop_CC_WB_test2_1;
  Stop * stop_CC_WB_test2_2;
  double * CC_EB_test2_distances;
  double * CC_WB_test2_distances;
  std::list<double> CC_EB_test2_probs;
  std::list<double> CC_WB_test2_probs;
  RandomPassengerGenerator * CC_EB_generator2;
  RandomPassengerGenerator * CC_WB_generator2;
  Route* TEST2_EB;
  Route* TEST2_WB;
  set_test2_stops1 = new Stop*[2];
  set_test2_stops2 = new Stop*[2];
  stop_CC_EB_test2_1 = new Stop(0, 21.972392, -58.243774);
  stop_CC_EB_test2_2 = new Stop(1, 21.973580, -58.235071);
  stop_CC_WB_test2_1 = new Stop(2, 21.975837, -57.222174);
  stop_CC_WB_test2_2 = new Stop(3, 21.972392, -58.243774);
  stops1_test2_list.push_back(stop_CC_EB_test2_1);
  set_test2_stops1[0] = stop_CC_EB_test2_1;
  stops1_test2_list.push_back(stop_CC_EB_test2_2);
  set_test2_stops1[1] = stop_CC_EB_test2_2;
  stops2_test2_list.push_back(stop_CC_WB_test2_1);
  set_test2_stops2[0] = stop_CC_WB_test2_1;
  stops2_test2_list.push_back(stop_CC_WB_test2_2);
  set_test2_stops2[1] = stop_CC_WB_test2_2;
  CC_EB_test2_distances = new double[1];
  CC_WB_test2_distances = new double[1];
  CC_EB_test2_distances[0] = 1;
  CC_WB_test2_distances[0] = 2;
  CC_EB_test2_probs.push_back(.3);
  CC_EB_test2_probs.push_back(0);
  CC_WB_test2_probs.push_back(.1);
  CC_WB_test2_probs.push_back(0);

  CC_EB_generator2 =
  new RandomPassengerGenerator(CC_EB_test2_probs, stops1_test2_list);
  CC_WB_generator2 =
  new RandomPassengerGenerator(CC_WB_test2_probs, stops2_test2_list);
  TEST2_EB = new Route("test2-EB", set_test2_stops1
  , CC_EB_test2_distances, 2, CC_EB_generator2);
  TEST2_WB = new Route("test2-WB"
  , set_test2_stops2, CC_WB_test2_distances, 2, CC_WB_generator2);

  std::vector<Route *> prototypeRoutes;
  prototypeRoutes.push_back(TEST_EB);
  prototypeRoutes.push_back(TEST_WB);
  prototypeRoutes.push_back(TEST2_EB);
  prototypeRoutes.push_back(TEST2_WB);
  std::vector<int> bus_timing_generation;
  bus_timing_generation.push_back(10);
  EXPECT_EQ(static_cast<int>(prototypeRoutes.size())/2,
   static_cast<int>(bus_timing_generation.size())) <<
   "Will occur ArrayIndexBound when simulator start";

  EXPECT_EQ(static_cast<int>(prototypeRoutes.size()),
  static_cast<int>(bus_timing_generation.size())+1) <<
  "Will occur ArrayIndexBound when simulator start";

  delete stop_CC_EB_test_1;
  delete stop_CC_EB_test_2;
  delete stop_CC_WB_test_1;
  delete stop_CC_WB_test_2;
  delete [] CC_EB_test_distances;
  delete [] CC_WB_test_distances;
  delete [] set_test_stops1;
  delete [] set_test_stops2;
  delete TEST_EB;
  delete TEST_WB;
  delete stop_CC_EB_test2_1;
  delete stop_CC_EB_test2_2;
  delete stop_CC_WB_test2_1;
  delete stop_CC_WB_test2_2;
  delete [] CC_EB_test2_distances;
  delete [] CC_WB_test2_distances;
  delete [] set_test2_stops1;
  delete [] set_test2_stops2;
  delete TEST2_EB;
  delete TEST2_WB;
}


TEST_F(FailTests, FailBus) {
  Stop** set_test_stops1;
  Stop** set_test_stops2;
  std::list<Stop*> stops1_test_list;
  std::list<Stop*> stops2_test_list;
  Stop * stop_CC_EB_test_1;
  Stop * stop_CC_EB_test_2;
  Stop * stop_CC_WB_test_1;
  Stop * stop_CC_WB_test_2;
  double * CC_EB_test_distances;
  double * CC_WB_test_distances;
  std::list<double> CC_EB_test_probs;
  std::list<double> CC_WB_test_probs;
  RandomPassengerGenerator * CC_EB_test_generator;
  RandomPassengerGenerator * CC_WB_test_generator;
  Route* TEST_EB_test;
  Route* TEST_WB_test;
  Bus* TEST_BUS;
  set_test_stops1 = new Stop*[2];
  set_test_stops2 = new Stop*[2];
  stop_CC_EB_test_1 = new Stop(0, 22.972392, -63.243774);
  stop_CC_EB_test_2 = new Stop(1, 23.973580, -62.235071);
  stop_CC_WB_test_1 = new Stop(2, 24.975837, -60.222174);
  stop_CC_WB_test_2 = new Stop(3, 22.972392, -63.243774);
  stops1_test_list.push_back(stop_CC_EB_test_1);
  set_test_stops1[0] = stop_CC_EB_test_1;
  stops1_test_list.push_back(stop_CC_EB_test_2);
  set_test_stops1[1] = stop_CC_EB_test_2;
  stops2_test_list.push_back(stop_CC_WB_test_1);
  set_test_stops2[0] = stop_CC_WB_test_1;
  stops2_test_list.push_back(stop_CC_WB_test_2);
  set_test_stops2[1] = stop_CC_WB_test_2;
  CC_EB_test_distances = new double[1];
  CC_WB_test_distances = new double[1];
  CC_EB_test_distances[0] = 4;
  CC_WB_test_distances[0] = 2;
  CC_EB_test_probs.push_back(0);
  CC_EB_test_probs.push_back(0);
  CC_WB_test_probs.push_back(0);
  CC_WB_test_probs.push_back(0);
  CC_EB_test_generator =
  new RandomPassengerGenerator(CC_EB_test_probs, stops1_test_list);
  CC_WB_test_generator =
  new RandomPassengerGenerator(CC_WB_test_probs, stops2_test_list);
  TEST_EB_test = new Route("test1-EB", set_test_stops1
  , CC_EB_test_distances, 2, CC_EB_test_generator);
  TEST_WB_test = new Route("test1-WB"
  , set_test_stops2, CC_WB_test_distances, 2, CC_WB_test_generator);
  TEST_BUS = new Bus("test-bus", TEST_EB_test, TEST_WB_test, 20, 1);
  for (int i =0; i < 5; i++) {
    TEST_EB_test->Update();
    TEST_WB_test->Update();
    TEST_BUS->Update();
  }
  EXPECT_NE(TEST_BUS->GetNumPassengers(), 0) <<
  "Expect zero passenger load\n";
  EXPECT_NE(stop_CC_EB_test_1->GetPassengersPresent(), 0) <<
  "Expect zero passenger at stop\n";
  EXPECT_NE(stop_CC_EB_test_2->GetPassengersPresent(), 0) <<
  "Expect zero passenger at stop\n";
  EXPECT_NE(stop_CC_WB_test_1->GetPassengersPresent(), 0) <<
  "Expect zero passenger at stop\n";
  EXPECT_NE(stop_CC_WB_test_2->GetPassengersPresent(), 0) <<
  "Expect zero passenger at stop\n";
  for (int i =0; i < 8; i++) {
      TEST_BUS->Update();
  }
  EXPECT_NE(TEST_BUS->GetNumPassengers(), 0) <<
   "Expect zero passenger at stop\n";
  Passenger* pass;
  for (int i =0; i < 21; i++) {
    pass = new Passenger(1, "csci3081");
    TEST_BUS->LoadPassenger(pass);
  }

  EXPECT_EQ(TEST_BUS->GetNumPassengers(), 22) << "Expect 20 passengers\n";
  delete stop_CC_EB_test_1;
  delete stop_CC_EB_test_2;
  delete stop_CC_WB_test_1;
  delete stop_CC_WB_test_2;
  delete [] CC_EB_test_distances;
  delete [] CC_WB_test_distances;
  delete [] set_test_stops1;
  delete [] set_test_stops2;
  delete pass;
  delete TEST_EB_test;
  delete TEST_WB_test;
  delete TEST_BUS;
}
