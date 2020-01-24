// Copyright 2019 Kyeongtak Han

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/stop.h"
#include "../src/passenger.h"
/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class StopTests : public ::testing::Test {
 protected:
  Stop* stop;
  virtual void SetUp() {
    stop = new Stop();
  }
  virtual void TearDown() {
    delete stop;
  }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(StopTests, Constructor) {
  Stop* stop1;
  stop1 = new Stop(8, 22, 34.1);
  EXPECT_EQ(stop1->GetId(), 8);
  Stop* stop2;
  stop2 = new Stop();
  EXPECT_EQ(stop2->GetId(), 1);

  std::string expected_out = "ID: 8\nPassengers waiting: 0\n";
  testing::internal::CaptureStdout();
  stop1->Report(std::cout);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out, output);

  std::string expected_out1 = "ID: 1\nPassengers waiting: 0\n";
  testing::internal::CaptureStdout();
  stop2->Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out1, output1);
  delete stop1;
  delete stop2;
}

TEST_F(StopTests, updating) {
  Stop* stop1;
  stop1 = new Stop(1, 22, 34.1);
  Passenger* pass1;
  pass1 = new Passenger(5, "tak");
  stop1->AddPassengers(pass1);
  stop1->Update();
  EXPECT_EQ(pass1->GetTotalWait(), 1);
  stop1->Update();
  EXPECT_EQ(pass1->GetTotalWait(), 2);
}
TEST_F(StopTests, AddPassengers) {
  Stop* stop1;
  stop1 = new Stop(1, 22, 34.1);
  Passenger* pass1 = new Passenger(5, "tak");;
  for (int i =0; i < 20; i++) {
    stop1->AddPassengers(pass1);
  }
  stop1->Update();

  std::string expected_out = "ID: 1\nPassengers waiting: 20\n";
  std::string str1 = "Name: tak\nDestination: 5\n"
  "Total Wait: 20\n\tWait at Stop: 20\n\tTime on bus: 0\n";
  for (int i =0; i < 20; i++) {
    expected_out += str1;
  }
  testing::internal::CaptureStdout();
  stop1->Report(std::cout);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expected_out, output);
}

TEST_F(StopTests, GetWaitingPassengers) {
  std::vector<Passenger*> pass_vect;
  Stop* stop1;
  stop1 = new Stop(1, 22, 34.1);
  EXPECT_EQ(stop1->GetPassengersPresent(), 0);
  Passenger* pass1;
  pass1 = new Passenger(5, "tak");
  stop1->AddPassengers(pass1);
  EXPECT_EQ(stop1->GetWaitingPassengers(), pass1);
  EXPECT_EQ(stop1->GetPassengersPresent(), 0);
  Passenger* pass2;
  pass2 = new Passenger(2, "CSCIstudent");
  Stop* stop2 = new Stop(1, 22, 34.1);
  for (int i =0; i < 20; i++) {
    stop2->AddPassengers(pass2);
  }
  EXPECT_EQ(stop2->GetPassengersPresent(), 20);
  for (int i = 0; i < 10; i++) {
    pass_vect.push_back(stop2->GetWaitingPassengers());
  }
  EXPECT_EQ(pass_vect.size(), 10);
  EXPECT_EQ(stop2->GetPassengersPresent(), 10);
  for (int i = 0; i < 10; i++) {
    pass_vect.push_back(stop2->GetWaitingPassengers());
  }
  EXPECT_EQ(pass_vect.size(), 20);
  EXPECT_EQ(stop2->GetPassengersPresent(), 0);
  delete stop1;
  delete stop2;
  delete pass2;
  delete pass1;
}

TEST_F(StopTests, passengers_present) {
  Stop* stop1;
  stop1 = new Stop(1, 22, 34.1);
  EXPECT_EQ(stop1->GetPassengersPresent(), 0);
  Passenger* pass1;
  pass1 = new Passenger(5, "tak");
  stop1->AddPassengers(pass1);
  EXPECT_EQ(stop1->GetPassengersPresent(), 1);
  Passenger* pass2;
  pass2 = new Passenger(2, "CSCIstudent");
  stop1->AddPassengers(pass2);
  EXPECT_EQ(stop1->GetPassengersPresent(), 2);
  Stop* stop2 = new Stop(1, 22, 34.1);
  for (int i =0; i < 20; i++) {
    stop2->AddPassengers(pass1);
  }
  EXPECT_EQ(stop2->GetPassengersPresent(), 20);
  delete stop1;
  delete stop2;
  delete pass2;
  delete pass1;
}

TEST_F(StopTests, GetLongitudeLatitude) {
  Stop* stop1;
  stop1 = new Stop(1, 22, 34.1);
  EXPECT_EQ(stop1->GetLongitude(), 22);
  EXPECT_EQ(stop1->GetLatitude(), 34.1);
  Stop* stop2;
  stop2 = new Stop();
  EXPECT_EQ(stop2->GetLongitude() - 44.973723, 0);
  EXPECT_EQ(stop2->GetLatitude() - -93.235365000000002, 0);
  delete stop1;
  delete stop2;
}


TEST_F(StopTests, PrintReport) {
  Stop* stop1;
  stop1 = new Stop(1, 22, 34.1);
  std::string expected_out_1 = "ID: 1\nPassengers waiting: 0\n";
  testing::internal::CaptureStdout();
  stop1->Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, expected_out_1);
  Passenger* pass1;
  pass1 = new Passenger(5, "tak");
  stop1->AddPassengers(pass1);


  std::string str1 = "ID: 1\nPassengers waiting: 1\nName: tak\nDestination: 5";
  std::string str2 = "\nTotal Wait: 0\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  testing::internal::CaptureStdout();
  std::string expected_out_2 = str1 + str2;
  stop1->Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output2, expected_out_2);
  delete pass1;
  delete stop1;
}
