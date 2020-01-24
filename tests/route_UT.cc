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
#include "../src/data_structs.h"
#include "../src/bus.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class RoutesTests : public ::testing::Test {
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
    CC_EB_generator =
    new RandomPassengerGenerator(CC_EB_probs, stops1_list);
    CC_WB_generator =
    new RandomPassengerGenerator(CC_WB_probs, stops2_list);
    TEST_EB = new Route("test1-EB", set_stops1
    , CC_EB_distances, 4, CC_EB_generator);
    TEST_WB = new Route("test1-WB"
    , set_stops2, CC_WB_distances, 5, CC_WB_generator);
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
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(RoutesTests, Constructor) {
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
  CC_EB_test_probs.push_back(.15);
  CC_EB_test_probs.push_back(0);
  CC_WB_test_probs.push_back(.35);
  CC_WB_test_probs.push_back(0);
  CC_EB_test_generator =
  new RandomPassengerGenerator(CC_EB_test_probs, stops1_test_list);
  CC_WB_test_generator =
  new RandomPassengerGenerator(CC_WB_test_probs, stops2_test_list);
  TEST_EB_test = new Route("test2-EB", set_test_stops1
  , CC_EB_test_distances, 2, CC_EB_test_generator);
  TEST_WB_test = new Route("test2-WB", set_test_stops2
  , CC_WB_test_distances, 2, CC_WB_test_generator);
  EXPECT_NE(CC_EB_test_probs.back(), 0.3) <<
  "Should be zero prob at last station\n";
  EXPECT_NE(CC_WB_test_probs.back(), 0.5) <<
  "Should be zero prob at last station\n";
  EXPECT_EQ(TEST_EB_test->GetName(), "test2-EB");
  EXPECT_EQ(TEST_EB_test->GetStops(), stops1_test_list) <<
  "Should be same list of stops\n";
  EXPECT_EQ(TEST_EB_test->GetFirstNextStop()->GetId(), 1) <<
  "Expected second station in Routes\n";
  EXPECT_EQ(TEST_EB_test->GetNumStops(), 2) <<
  "Expect 2 that is total number of stops in route\n";
  EXPECT_EQ(TEST_EB_test->GetNextStopDistance(), 4) <<
  "Expect 4 Distances between first and second stops\n";
  EXPECT_EQ(TEST_EB_test->GetLastStop()->GetId(), 1) <<
  "Expect last station\n";
  EXPECT_EQ(TEST_EB_test->GetCurrentStop()->GetId(), 0) <<
  "Expect currently stop at which bus is";
  EXPECT_EQ(TEST_EB_test->GetTargetStop()->GetId(), 1) <<
  "Expect Next stop\n";
  testing::internal::CaptureStdout();
  std::cout << "Name: test2-EB\nNum stops: 2\n";
  stop_CC_EB_test_2->Report(std::cout);
  stop_CC_EB_test_1->Report(std::cout);
  std::string expected_out = testing::internal::GetCapturedStdout();
  testing::internal::CaptureStdout();
  TEST_EB_test->Report(std::cout);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out, output);
  EXPECT_EQ(TEST_WB_test->GetName(), "test2-WB");
  EXPECT_EQ(TEST_WB_test->GetStops(), stops2_test_list) <<
  "Should be same list of stops\n";
  EXPECT_EQ(TEST_WB_test->GetFirstNextStop()->GetId(), 3) <<
  "Expected second station in Routes\n";
  EXPECT_EQ(TEST_WB_test->GetNumStops(), 2) <<
  "Expect 2 that is total number of stops in route\n";
  EXPECT_EQ(TEST_WB_test->GetNextStopDistance(), 2) <<
  "Expect 4 Distances between first and second stops\n";
  EXPECT_EQ(TEST_WB_test->GetLastStop()->GetId(), 3)  <<
  "Expect last station\n";
  EXPECT_EQ(TEST_WB_test->GetCurrentStop()->GetId(), 2) <<
  "Expect currently stop at which bus is";
  EXPECT_EQ(TEST_WB_test->GetTargetStop()->GetId(), 3) <<
  "Expect Next stop\n";
  testing::internal::CaptureStdout();
  std::cout << "Name: test2-WB\nNum stops: 2\n";
  stop_CC_WB_test_2->Report(std::cout);
  stop_CC_WB_test_1->Report(std::cout);
  std::string expected_out1 = testing::internal::GetCapturedStdout();
  testing::internal::CaptureStdout();
  TEST_WB_test->Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out1, output1);
  delete stop_CC_EB_test_1;
  delete stop_CC_EB_test_2;
  delete stop_CC_WB_test_1;
  delete stop_CC_WB_test_2;
  delete [] CC_EB_test_distances;
  delete [] CC_WB_test_distances;
  delete [] set_test_stops1;
  delete [] set_test_stops2;
  delete TEST_EB_test;
  delete TEST_WB_test;
}
TEST_F(RoutesTests, FunctionEBUpdateTest) {
  Route* TEST_EB1 = TEST_EB->Clone();
  EXPECT_EQ(TEST_EB1->GetCurrentStop()->GetId(), 0) <<
   "Expect 0\n";
  EXPECT_EQ(TEST_EB1->GetTargetStop()->GetId(), 1) <<
   "Expect next stop 1\n";
  EXPECT_EQ(TEST_EB1->GetPreStop()->GetId(), 0) <<
   "Expect previous stop 1\n";;
  TEST_EB1->NextStop();
  TEST_EB1->Update();
  std::list<Stop*> slist = TEST_EB1->GetStops();
  testing::internal::CaptureStdout();
  std::cout << "Name: test1-EB\nNum stops: 4\n";
  for (std::list<Stop*>::iterator it = slist.begin();
  it != slist.end(); it++) {
    (*it)->Report(std::cout);
  }
  std::string expected_out = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  TEST_EB1->Report(std::cout);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out, output) <<
   "Expect to be same output";


  EXPECT_EQ(TEST_EB1->GetNextStopDistance(), 4) <<
   "Expect 4\n";
  EXPECT_EQ(TEST_EB1->GetCurrentStop()->GetId(), 1) <<
   "Expect current stop id: 1\n";
  EXPECT_EQ(TEST_EB1->GetTargetStop()->GetId(), 2) <<
   "Expect next target stop id:4\n";
  EXPECT_EQ(TEST_EB1->GetPreStop()->GetId(), 1) <<
   "Expect previous stop id:1\n";
  TEST_EB1->NextStop();
  TEST_EB1->Update();
  slist = TEST_EB1->GetStops();
  testing::internal::CaptureStdout();
  std::cout << "Name: test1-EB\nNum stops: 4\n";
  for (std::list<Stop*>::iterator it = slist.begin();
  it != slist.end(); it++) {
    (*it)->Report(std::cout);
  }
  std::string expected_out1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  TEST_EB1->Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out1, output1) <<
   "Expect to be same output";

  EXPECT_EQ(TEST_EB1->GetNextStopDistance(), 4) <<
   "Expect 4\n";
  EXPECT_EQ(TEST_EB1->GetCurrentStop()->GetId(), 2)<<
   "Expect current stop id: 2\n";
  EXPECT_EQ(TEST_EB1->GetTargetStop()->GetId(), 3) <<
   "Expect next target stop id: 3\n";
  EXPECT_EQ(TEST_EB1->GetPreStop()->GetId(), 2) <<
   "Expect previous stop id: 2\n";

  TEST_EB1->NextStop();
  TEST_EB1->Update();
  slist = TEST_EB1->GetStops();
  testing::internal::CaptureStdout();
  std::cout << "Name: test1-EB\nNum stops: 4\n";
  for (std::list<Stop*>::iterator it = slist.begin();
  it != slist.end(); it++) {
    (*it)->Report(std::cout);
  }
  std::string expected_out2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  TEST_EB1->Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out2, output2) <<
   "Expect to be same output";

  EXPECT_EQ(TEST_EB1->GetNextStopDistance(), 2) <<
   "Expect 2\n";
  EXPECT_EQ(TEST_EB1->GetCurrentStop()->GetId(), 3) <<
   "Expect current stop id: 3\n";
  EXPECT_EQ(TEST_EB1->GetTargetStop()->GetId(), 0) <<
   "Expect target stop id: 0 (first stop)\n";
  EXPECT_EQ(TEST_EB1->GetPreStop()->GetId(), 3) <<
   "Expect previous stop id: 3\n";
}

TEST_F(RoutesTests, FunctionWBUpdateTest) {
  Route* TEST_WB1 = TEST_WB->Clone();
  EXPECT_EQ(TEST_WB1->GetCurrentStop()->GetId(), 4) <<
   "Expect first stop id: 2\n";
  EXPECT_EQ(TEST_WB1->GetTargetStop()->GetId(), 5) <<
   "Expect next stop id: 5\n";
  EXPECT_EQ(TEST_WB1->GetPreStop()->GetId(), 4) <<
   "Expect previous stop id: 4\n";
  EXPECT_EQ(TEST_WB1->GetNextStopDistance(), 2) <<
   "Expect the first distance 2\n";
  TEST_WB1->NextStop();
  TEST_WB1->Update();
  std::list<Stop*> slist = TEST_WB1->GetStops();
  testing::internal::CaptureStdout();
  std::cout << "Name: test1-WB\nNum stops: 5\n";
  for (std::list<Stop*>::iterator it = slist.begin(); it != slist.end(); it++) {
  (*it)->Report(std::cout);
  }
  std::string expected_out = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  TEST_WB1->Report(std::cout);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out, output) <<
   "Expect to be same output";
  EXPECT_EQ(TEST_WB1->GetNextStopDistance(), 1) <<
   "Expect the 2nd distance 1\n";
  EXPECT_EQ(TEST_WB1->GetCurrentStop()->GetId(), 5) <<
  "Expect the current stop id:5\n";
  EXPECT_EQ(TEST_WB1->GetTargetStop()->GetId(), 6) <<
   "Expect the next stop id:6\n";
  EXPECT_EQ(TEST_WB1->GetPreStop()->GetId(), 5) <<
   "Expect the previous stop id:5\n";
  TEST_WB1->NextStop();
  TEST_WB1->Update();
  slist = TEST_WB1->GetStops();
  testing::internal::CaptureStdout();
  std::cout << "Name: test1-WB\nNum stops: 5\n";
  for (std::list<Stop*>::iterator it = slist.begin();
  it != slist.end(); it++) {
    (*it)->Report(std::cout);
  }
  std::string expected_out1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  TEST_WB1->Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out1, output1) <<
   "Expect to be same output";
  EXPECT_EQ(TEST_WB1->GetNextStopDistance(), 2) <<
   "Expect the 3rd distance 2\n";
  EXPECT_EQ(TEST_WB1->GetCurrentStop()->GetId(), 6) <<
   "Expect the current stop id:6\n";
  EXPECT_EQ(TEST_WB1->GetTargetStop()->GetId(), 7) <<
   "Expect the next stop id:7\n";
  EXPECT_EQ(TEST_WB1->GetPreStop()->GetId(), 6) <<
   "Expect the previous stop id:6\n";
  TEST_WB1->NextStop();
  TEST_WB1->Update();
  slist = TEST_WB1->GetStops();
  testing::internal::CaptureStdout();
  std::cout << "Name: test1-WB\nNum stops: 5\n";
  for (std::list<Stop*>::iterator it = slist.begin();
  it != slist.end(); it++) {
    (*it)->Report(std::cout);
  }
  std::string expected_out2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  TEST_WB1->Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out2, output2) <<
   "Expect to be same output";
  EXPECT_EQ(TEST_WB1->GetNextStopDistance(), 2) <<
   "Expect the 4th distance 2\n";
  EXPECT_EQ(TEST_WB1->GetCurrentStop()->GetId(), 7) <<
   "Expect the current stop id:7\n";
  EXPECT_EQ(TEST_WB1->GetTargetStop()->GetId(), 8) <<
   "Expect the next stop id:8\n";
  EXPECT_EQ(TEST_WB1->GetPreStop()->GetId(), 7) <<
   "Expect the previous stop id:7\n";
  TEST_WB1->NextStop();
  TEST_WB1->Update();
  slist = TEST_WB1->GetStops();
  testing::internal::CaptureStdout();
  std::cout << "Name: test1-WB\nNum stops: 5\n";
  for (std::list<Stop*>::iterator it = slist.begin();
  it != slist.end(); it++) {
    (*it)->Report(std::cout);
  }
  std::string expected_out3 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  TEST_WB1->Report(std::cout);
  std::string output3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out3, output3) <<
   "Expect to be same output";
  EXPECT_EQ(TEST_WB1->GetCurrentStop()->GetId(), 8) <<
   "Expect the current stop id:8\n";
  EXPECT_EQ(TEST_WB1->GetTargetStop()->GetId(), 4) <<
   "Expect the next stop id:4 first stop\n";
  EXPECT_EQ(TEST_WB1->GetPreStop()->GetId(), 8) <<
   "Expect the previous stop id:8\n";
}
TEST_F(RoutesTests, CloneTesting) {
  Route* clone_EB = TEST_EB->Clone();
  Route* clone_WB = TEST_WB->Clone();
  std::list<Stop*> clone_stops;
  std::list<Stop*> origin_stops;
  clone_stops = clone_EB->GetStops();
  origin_stops = TEST_EB->GetStops();
  EXPECT_EQ(clone_stops.size(), origin_stops.size()) <<
   "Expect same size with original and cloned one\n";
  int size = clone_stops.size();
  for (int i=0; i < size; i++) {
    EXPECT_EQ(clone_stops.front()->GetId(), origin_stops.front()->GetId()) <<
     "Expect same stop id\n";
    clone_stops.pop_front();
    origin_stops.pop_front();
  }
  clone_stops = clone_WB->GetStops();
  origin_stops = TEST_WB->GetStops();
  EXPECT_EQ(clone_stops.size(), origin_stops.size()) <<
   "Expect same size with original and cloned one\n";
  for (int i=0; i < size; i++) {
    EXPECT_EQ(clone_stops.front(), origin_stops.front()) <<
     "Expect same stop id\n";
    clone_stops.pop_front();
    origin_stops.pop_front();
  }
}
TEST_F(RoutesTests, OutRouteDataTesting) {
  EXPECT_EQ(TEST_EB->GetName(), "test1-EB");
  EXPECT_EQ(TEST_EB->GetStops(), stops1_list);
  RouteData data = TEST_EB->GetRouteData();
  EXPECT_EQ(data.id, "")<< "Expect empty id default";

  TEST_EB->Update();
  TEST_EB->UpdateRouteData();
  RouteData data1 = TEST_EB->GetRouteData();
  EXPECT_EQ(data1.id, "test1-EB") << "Expect test1-EB";
  EXPECT_EQ(data1.stops[0].id, "0") <<
   "Expect same stop id";
  EXPECT_LE(data1.stops[0].position.x - stop_CC_EB_1->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[0].position.y - stop_CC_EB_1->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[0].num_people, stop_CC_EB_1->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[1].id, "1") << "Expect same stop id";
  EXPECT_LE(data1.stops[1].position.x - stop_CC_EB_2->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[1].position.y - stop_CC_EB_2->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[1].num_people, stop_CC_EB_2->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[2].id, "2") << "Expect same stop id";
  EXPECT_LE(data1.stops[2].position.x - stop_CC_EB_3->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[2].position.y - stop_CC_EB_3->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[2].num_people, stop_CC_EB_3->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[3].id, "3") << "Expect same stop id";
  EXPECT_LE(data1.stops[3].position.x - stop_CC_EB_4->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[3].position.y - stop_CC_EB_4->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[3].num_people, stop_CC_EB_4->GetPassengersPresent()) <<
   "Expect same num_people ";
  for (int i =0; i < 4; i++) {
    TEST_EB->Update();
    TEST_EB->UpdateRouteData();
  }
  data1 = TEST_EB->GetRouteData();
  EXPECT_EQ(data1.id, "test1-EB") <<
   "Expect test1-EB";
  EXPECT_EQ(data1.stops[0].id, "0") <<
   "Expect same stop id";
  EXPECT_LE(data1.stops[0].position.x - stop_CC_EB_1->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[0].position.y - stop_CC_EB_1->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[0].num_people, stop_CC_EB_1->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[1].id, "1") << "Expect same stop id";
  EXPECT_LE(data1.stops[1].position.x - stop_CC_EB_2->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[1].position.y - stop_CC_EB_2->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[1].num_people, stop_CC_EB_2->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[2].id, "2") << "Expect same stop id";
  EXPECT_LE(data1.stops[2].position.x - stop_CC_EB_3->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[2].position.y - stop_CC_EB_3->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[2].num_people, stop_CC_EB_3->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[3].id, "3") << "Expect same stop id";
  EXPECT_LE(data1.stops[3].position.x - stop_CC_EB_4->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[3].position.y - stop_CC_EB_4->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[3].num_people, stop_CC_EB_4->GetPassengersPresent()) <<
   "Expect same num_people ";
}

TEST_F(RoutesTests, InRouteDataTesting) {
  EXPECT_EQ(TEST_WB->GetName(), "test1-WB");
  RouteData data = TEST_WB->GetRouteData();
  EXPECT_EQ(data.id, "") <<
   "Expect empty id default";
  TEST_WB->Update();
  TEST_WB->UpdateRouteData();
  RouteData data1 = TEST_WB->GetRouteData();
  EXPECT_EQ(data1.id, "test1-WB") <<
   "Expect test1-WB";
  EXPECT_EQ(data1.stops[0].id, "4") <<
   "Expect same stop id";
  EXPECT_LE(data1.stops[0].position.x - stop_CC_WB_1->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[0].position.y - stop_CC_WB_1->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[0].num_people, stop_CC_WB_1->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[1].id, "5") << "Expect same stop id";
  EXPECT_LE(data1.stops[1].position.x - stop_CC_WB_2->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[1].position.y - stop_CC_WB_2->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[1].num_people, stop_CC_WB_2->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[2].id, "6") << "Expect same stop id";
  EXPECT_LE(data1.stops[2].position.x - stop_CC_WB_3->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[2].position.y - stop_CC_WB_3->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[2].num_people, stop_CC_WB_3->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[3].id, "7") <<
   "Expect same stop id";
  EXPECT_LE(data1.stops[3].position.x - stop_CC_WB_4->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[3].position.y - stop_CC_WB_4->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[3].num_people, stop_CC_WB_4->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[4].id, "8") << "Expect same stop id";
  EXPECT_LE(data1.stops[4].position.x - stop_CC_WB_4->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[4].position.y - stop_CC_WB_4->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[4].num_people, stop_CC_WB_4->GetPassengersPresent()) <<
   "Expect same num_people ";
  for (int i =0; i < 15; i++) {
    TEST_EB->Update();
    TEST_EB->UpdateRouteData();
  }
  data1 = TEST_WB->GetRouteData();
  EXPECT_EQ(data1.id, "test1-WB") << "Expect test1-WB";
  EXPECT_EQ(data1.stops[0].id, "4") << "Expect same stop id";
  EXPECT_LE(data1.stops[0].position.x - stop_CC_WB_1->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[0].position.y - stop_CC_WB_1->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[0].num_people, stop_CC_WB_1->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[1].id, "5") << "Expect same stop id";
  EXPECT_LE(data1.stops[1].position.x - stop_CC_WB_2->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[1].position.y - stop_CC_WB_2->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[1].num_people, stop_CC_WB_2->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[2].id, "6") << "Expect same stop id";
  EXPECT_LE(data1.stops[2].position.x - stop_CC_WB_3->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[2].position.y - stop_CC_WB_3->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[2].num_people, stop_CC_WB_3->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[3].id, "7") << "Expect same stop id";
  EXPECT_LE(data1.stops[3].position.x - stop_CC_WB_4->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[3].position.y - stop_CC_WB_4->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[3].num_people, stop_CC_WB_4->GetPassengersPresent()) <<
   "Expect same num_people ";
  EXPECT_EQ(data1.stops[4].id, "8") << "Expect same stop id";
  EXPECT_LE(data1.stops[4].position.x - stop_CC_WB_4->GetLongitude(), 0.1) <<
   "Expect less than 0.1 difference longitude ";
  EXPECT_LE(data1.stops[4].position.y - stop_CC_WB_4->GetLatitude(), 0.1) <<
   "Expect less than 0.1 difference latitude ";
  EXPECT_EQ(data1.stops[4].num_people, stop_CC_WB_4->GetPassengersPresent()) <<
   "Expect same num_people ";
}
