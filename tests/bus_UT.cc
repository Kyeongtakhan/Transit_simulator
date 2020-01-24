// Copyright 2019 Kevin Wendt

/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include "../src/passenger.h"
#include "../src/bus.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BusTests : public ::testing::Test {
 protected:
  Passenger* passenger;
  Stop** set_stops1;
  Stop** set_stops2;
  std::list<Stop*> stops1_list;
  std::list<Stop*> stops2_list;
  Stop * stop_CC_EB_1;
  Stop * stop_CC_EB_2;
  Stop * stop_CC_EB_3;
  Stop * stop_CC_EB_4;
  Stop * stop_CC_WB_1;
  Stop * stop_CC_WB_2;
  Stop * stop_CC_WB_3;
  Stop * stop_CC_WB_4;
  Stop * stop_CC_WB_5;
  double * CC_EB_distances;
  double * CC_WB_distances;
  std::list<double> CC_EB_probs;
  std::list<double> CC_WB_probs;
  RandomPassengerGenerator * CC_EB_generator;
  RandomPassengerGenerator * CC_WB_generator;
  Route* TEST_EB;
  Route* TEST_WB;
  Bus* TEST_BUS;
  virtual void SetUp() {
    passenger = new Passenger();
    set_stops1 = new Stop*[4];
    set_stops2 = new Stop*[5];
    //
    stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
    stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
    stop_CC_EB_4 = new Stop(3, 44.975837, -93.222174);

    stop_CC_WB_1 = new Stop(4, 44.975837, -93.222174);
    stop_CC_WB_2 = new Stop(5, 44.984482, -93.181657);
    stop_CC_WB_3 = new Stop(6, 44.983703, -93.178846);
    stop_CC_WB_4 = new Stop(7, 44.980663, -93.180808);
    stop_CC_WB_5 = new Stop(8, 44.976397, -93.221801);

    stops1_list.push_back(stop_CC_EB_1);
    set_stops1[0] = stop_CC_EB_1;
    stops1_list.push_back(stop_CC_EB_2);
    set_stops1[1] = stop_CC_EB_2;
    stops1_list.push_back(stop_CC_EB_3);
    set_stops1[2] = stop_CC_EB_3;
    stops1_list.push_back(stop_CC_EB_4);
    set_stops1[3] = stop_CC_EB_4;

    stops2_list.push_back(stop_CC_WB_1);
    set_stops2[0] = stop_CC_WB_1;
    stops2_list.push_back(stop_CC_WB_2);
    set_stops2[1] = stop_CC_WB_2;
    stops2_list.push_back(stop_CC_WB_3);
    set_stops2[2] = stop_CC_WB_3;
    stops2_list.push_back(stop_CC_WB_4);
    set_stops2[3] = stop_CC_WB_4;
    stops2_list.push_back(stop_CC_WB_5);
    set_stops2[4] = stop_CC_WB_5;

    CC_EB_distances = new double[3];
    CC_WB_distances = new double[4];
    CC_EB_distances[0] = 4;
    CC_EB_distances[1] = 4;
    CC_EB_distances[2] = 2;
    CC_WB_distances[0] = 2;
    CC_WB_distances[1] = 1;
    CC_WB_distances[2] = 2;
    CC_WB_distances[3] = 2;
    CC_EB_probs.push_back(.15);
    CC_EB_probs.push_back(.3);
    CC_EB_probs.push_back(.025);
    CC_EB_probs.push_back(0);
    CC_WB_probs.push_back(.35);
    CC_WB_probs.push_back(.05);
    CC_WB_probs.push_back(.01);
    CC_WB_probs.push_back(.01);
    CC_WB_probs.push_back(0);
    CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, stops1_list);
    CC_WB_generator = new RandomPassengerGenerator(CC_WB_probs, stops2_list);
    TEST_EB = new Route("test1-EB", set_stops1
    , CC_EB_distances, 4, CC_EB_generator);
    TEST_WB = new Route("test1-WB"
    , set_stops2, CC_WB_distances, 5, CC_WB_generator);
    TEST_BUS = new Bus("test-bus", TEST_EB->Clone(), TEST_WB->Clone(), 20, 1);
  }
  virtual void TearDown() {
    delete passenger;
    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete stop_CC_EB_4;
    delete stop_CC_WB_1;
    delete stop_CC_WB_2;
    delete stop_CC_WB_3;
    delete stop_CC_WB_4;
    delete stop_CC_WB_5;
    delete [] CC_EB_distances;
    delete [] CC_WB_distances;
    delete [] set_stops1;
    delete [] set_stops2;
    delete TEST_EB;
    delete TEST_WB;
    delete TEST_BUS;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(BusTests, Constructor) {
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
  CC_EB_test_probs.push_back(.7);
  CC_EB_test_probs.push_back(0);
  CC_WB_test_probs.push_back(.6);
  CC_WB_test_probs.push_back(0);
  CC_EB_test_generator =
  new RandomPassengerGenerator(CC_EB_test_probs, stops1_test_list);
  CC_WB_test_generator =
  new RandomPassengerGenerator(CC_WB_test_probs, stops2_test_list);
  TEST_EB_test = new Route("test1-EB", set_test_stops1,
   CC_EB_test_distances, 2, CC_EB_test_generator);
  TEST_WB_test = new Route("test1-WB", set_test_stops2,
   CC_WB_test_distances, 2, CC_WB_test_generator);
  TEST_BUS = new Bus("test-bus", TEST_EB_test, TEST_WB_test, 20, 1);
  EXPECT_EQ(TEST_BUS->GetName(), "test-bus");
  EXPECT_EQ(TEST_BUS->GetNumPassengers(), 0);
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 1);
  testing::internal::CaptureStdout();
  std::cout << "Name: test-bus\nSpeed: 1\n";
  std::cout << "Distance to next stop: 0\n";
  std::cout << "\tPassengers (0): \n";
  std::string expected_out = testing::internal::GetCapturedStdout();
  testing::internal::CaptureStdout();
  TEST_BUS->Report(std::cout);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out, output);
}

TEST_F(BusTests, CorrectInfo) {
  EXPECT_EQ(TEST_BUS->GetName(), "test-bus");
  EXPECT_EQ(TEST_BUS->GetNumPassengers(), 0);
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 1);
}

TEST_F(BusTests, LoadUnloadTest) {
  std::vector<Passenger*> pass_vect;
  Passenger* passenger = new Passenger(-1, "csci3081");
  Passenger* passenger2 = new Passenger(-2, "csci4061");
  for (int i = 0; i < 10; i++) {
    TEST_BUS->LoadPassenger(passenger);
  }
  for (int i = 0; i < 10; i++) {
    TEST_BUS->LoadPassenger(passenger2);
  }
  EXPECT_NE(TEST_BUS->LoadPassenger(passenger), true);
  EXPECT_EQ(TEST_BUS->LoadPassenger(passenger2), false);
  EXPECT_EQ(TEST_BUS->GetNumPassengers(), 20);

  Stop * stop_CC_EB_10 = new Stop(-1, 44.972392, -93.243774);
  Stop * stop_CC_EB_11 = new Stop(-2, 44.972392, -93.243774);
  TEST_BUS->UnloadPassenger(stop_CC_EB_10->GetId());
  EXPECT_EQ(TEST_BUS->GetCapacity(), 10);
  EXPECT_EQ(TEST_BUS->GetNumPassengers(), 10);
  TEST_BUS->UnloadPassenger(stop_CC_EB_11->GetId());
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20);
  EXPECT_EQ(TEST_BUS->GetNumPassengers(), 0);
  delete stop_CC_EB_10;
  delete stop_CC_EB_11;
  delete passenger;
  delete passenger2;
}

TEST_F(BusTests, UpdatingWithCompleteTripTesting) {
  EXPECT_EQ(TEST_BUS->GetName(), "test-bus");
  EXPECT_EQ(TEST_BUS->GetNumPassengers(), 0) << "Bus data number of passengers";
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20) << "Bus data max capacity ";
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 1);
  for (int i =0; i < 3; i ++) {
    TEST_BUS->Update();
  }
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 1);
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
  "Bus data max capacity ";
  TEST_BUS->Update();
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 1);
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";
  for (int i =0; i < 3; i ++) {
    TEST_BUS->Update();
  }
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 2);
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 2);
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";
  TEST_BUS->Update();
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 2);
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";
  TEST_BUS->Update();
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 3) <<
   "Bus swap route from out to in";
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";
  for (int i =0; i < 2; i ++) {
    TEST_BUS->Update();
  }
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 5) <<
   "Bus swap route from out to in";
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
  "Bus data max capacity ";
  for (int i =0; i < 2; i ++) {
    TEST_BUS->Update();
  }
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 6) <<
   "Bus swap route from out to in";
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";
  for (int i =0; i < 2; i ++) {
    TEST_BUS->Update();
  }
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 7) <<
   "Bus swap route from out to in";
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";

  for (int i =0; i < 2; i++) {
    TEST_BUS->Update();
  }
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 8) <<
   "Bus swap route from out to in";
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";
  TEST_BUS->Update();
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  EXPECT_EQ(TEST_BUS->GetNextStop()->GetId(), 4) <<
  "Bus swap route from out to in";
  EXPECT_EQ(TEST_BUS->GetCapacity(), 20 - TEST_BUS->GetNumPassengers()) <<
   "Bus data max capacity ";
  TEST_BUS->Update();
  EXPECT_EQ(TEST_BUS->IsTripComplete(), false);
  TEST_BUS->Update();
  EXPECT_EQ(TEST_BUS->IsTripComplete(), true);
  Bus* TEST_BUS1 = new Bus("test-bus1", TEST_EB->Clone()
  , TEST_WB->Clone(), 20, 1);
  for (int i =0; i < 20; i++) {
    TEST_BUS1->Update();
  }
  EXPECT_EQ(TEST_BUS1->IsTripComplete(), true);
  EXPECT_EQ(TEST_BUS1->GetCapacity(), 20 - TEST_BUS1->GetNumPassengers()) <<
   "Bus data max capacity ";
}


TEST_F(BusTests, BusDataTesting) {
  EXPECT_EQ(TEST_BUS->GetName(), "test-bus");
  TEST_BUS->UpdateBusData();
  BusData data1 = TEST_BUS->GetBusData();
  EXPECT_EQ(data1.id, "test-bus") <<
   "Bus data id test";
  EXPECT_EQ(data1.num_passengers, 0) <<
   "Bus data number of passengers";
  EXPECT_EQ(data1.capacity, TEST_BUS->GetCapacity()) <<
   "Bus data max capacity ";
  EXPECT_EQ(data1.position.x, 44.973579406738281) <<
   "Expect Same position";
  EXPECT_EQ(data1.position.y, -93.235069274902344)<<
   "Expect Same position";
  Stop* next_stop = TEST_BUS->GetNextStop();
  EXPECT_EQ(next_stop->GetId(), 1);
  TEST_BUS->Update();
  next_stop = TEST_BUS->GetNextStop();
  EXPECT_EQ(next_stop->GetId(), 1);
  for (int i =0; i < 2; i ++) {
    TEST_BUS->Update();
  }
  next_stop = TEST_BUS->GetNextStop();
  EXPECT_EQ(next_stop->GetId(), 1);
  TEST_BUS->UpdateBusData();
  BusData data2 = TEST_BUS->GetBusData();
  EXPECT_EQ(data2.id, "test-bus") <<
   "Bus data id test";
  EXPECT_EQ(data2.capacity, TEST_BUS->GetCapacity()) <<
   "Bus data max capacity ";
  EXPECT_EQ(data2.position.x, 44.972984313964844) <<
   "Expect Same position";
  EXPECT_EQ(data2.position.y, -93.239425659179688)<<
   "Expect Same position";
  for (int i =0; i < 2; i++) {
    TEST_BUS->Update();
  }
  next_stop = TEST_BUS->GetNextStop();
  EXPECT_EQ(next_stop->GetId(), 2);
  TEST_BUS->UpdateBusData();
  BusData data3 = TEST_BUS->GetBusData();
  EXPECT_EQ(data3.id, "test-bus") <<
   "Bus data id test";
  EXPECT_EQ(data3.capacity, TEST_BUS->GetCapacity()) <<
   "Bus data max capacity ";
  EXPECT_EQ(data3.position.x, 44.973579406738281);
  EXPECT_EQ(data3.position.y, -93.235069274902344);
  for (int i = 0; i < 4; i++) {
    TEST_BUS->Update();
  }
  next_stop = TEST_BUS->GetNextStop();
  EXPECT_EQ(next_stop->GetId(), 3);
  TEST_BUS->UpdateBusData();
  BusData data4 = TEST_BUS->GetBusData();
  EXPECT_EQ(data4.id, "test-bus") <<
   "Bus data id test";
  EXPECT_EQ(data4.capacity, TEST_BUS->GetCapacity()) <<
   "Bus data max capacity ";
  EXPECT_EQ(data4.position.x, 44.975391387939453);
  EXPECT_EQ(data4.position.y, -93.226631164550781);
  for (int i =0; i < 6; i++) {
    TEST_BUS->Update();
  }
  next_stop = TEST_BUS->GetNextStop();
  EXPECT_EQ(next_stop->GetId(), 7);
  TEST_BUS->UpdateBusData();
  BusData data5 = TEST_BUS->GetBusData();
  EXPECT_EQ(data5.id, "test-bus") <<
   "Bus data id test";
  EXPECT_EQ(data5.capacity, TEST_BUS->GetCapacity()) <<
   "Bus data max capacity ";
  EXPECT_EQ(data5.position.x, 44.982185363769531);
  EXPECT_EQ(data5.position.y, -93.179824829101562);
  for (int i =0; i < 2; i++) {
    TEST_BUS->Update();
  }
  next_stop = TEST_BUS->GetNextStop();
  EXPECT_EQ(next_stop->GetId(), 8);
  TEST_BUS->Update();
  TEST_BUS->UpdateBusData();
  BusData data6 = TEST_BUS->GetBusData();
  EXPECT_EQ(data6.id, "test-bus") <<
   "Bus data id test";
  EXPECT_EQ(data6.capacity, TEST_BUS->GetCapacity()) <<
   "Bus data max capacity ";
  EXPECT_EQ(data6.position.x, 44.976398468017578);
  EXPECT_EQ(data6.position.y, -93.2218017578125);


  Bus* TEST_BUS1 = new Bus("test-bus1", TEST_EB->Clone()
  , TEST_WB->Clone(), 20, 1);
  for (int i =0; i < 15; i++) {
    TEST_BUS1->Update();
  }
  TEST_BUS->Update();
  TEST_BUS->UpdateBusData();
  BusData data7 = TEST_BUS->GetBusData();
  EXPECT_EQ(data6.id, "test-bus") <<
   "Bus data id test";
  EXPECT_EQ(data6.capacity, TEST_BUS->GetCapacity()) <<
   "Bus data max capacity ";
  EXPECT_EQ(data6.position.x, 44.976398468017578);
  EXPECT_EQ(data6.position.y, -93.2218017578125);
}
