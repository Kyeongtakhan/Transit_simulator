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
#include "../src/passenger.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {
 protected:
  Passenger* passenger;
  virtual void SetUp() {
    passenger = new Passenger();
  }
  virtual void TearDown() {
    delete passenger;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, GetDestination) {
  Passenger* p1;
  p1 = new Passenger(5, "tak");
  EXPECT_EQ(p1->GetDestination(), 5);
  Passenger* p2;
  p2 = new Passenger();
  EXPECT_EQ(p2->GetDestination(), -1);
  EXPECT_NE(p2->GetDestination(), 1);
  Passenger* p3;
  p3 = new Passenger(22);
  EXPECT_EQ(p3->GetDestination(), 22);
  delete p1;
  delete p2;
  delete p3;
}


TEST_F(PassengerTests, GetOnBus) {
  Passenger* p1;
  p1 = new Passenger();
  EXPECT_EQ(p1->IsOnBus(), false);
  p1->GetOnBus();
  EXPECT_EQ(p1->IsOnBus(), true);

  Passenger* p2;
  p2 = new Passenger(5, "tak");
  EXPECT_EQ(p2->IsOnBus(), false);
  p2->GetOnBus();
  EXPECT_EQ(p2->IsOnBus(), true);
  Passenger* p3;
  p3 = new Passenger(77);
  EXPECT_EQ(p3->IsOnBus(), false);
  p3->GetOnBus();
  EXPECT_EQ(p3->IsOnBus(), true);

  delete p1;
  delete p2;
  delete p3;
}

TEST_F(PassengerTests, TotalWait) {
  Passenger* pass1;
  pass1 = new Passenger(12, "UMNstudent");
  EXPECT_EQ(pass1->GetTotalWait(), 0);
  EXPECT_NE(pass1->IsOnBus(), true);
  for (int i = 0; i < 20; i++) {
    pass1->Update();
  }
  EXPECT_EQ(pass1->GetTotalWait(), 20);
  pass1->GetOnBus();
  EXPECT_EQ(pass1->IsOnBus(), true);
  EXPECT_EQ(pass1->GetTotalWait(), 21);
  pass1->Update();
  EXPECT_EQ(pass1->GetTotalWait(), 22);

  Passenger* pass2;
  pass2 = new Passenger();
  EXPECT_EQ(pass2->GetTotalWait(), 0);
  EXPECT_NE(pass2->IsOnBus(), true);
  for (int i = 0; i < 10; i++) {
    pass2->Update();
  }
  EXPECT_EQ(pass2->GetTotalWait(), 10);
  pass2->GetOnBus();
  EXPECT_EQ(pass2->IsOnBus(), true);
  EXPECT_EQ(pass2->GetTotalWait(), 11);
  pass2->Update();
  EXPECT_EQ(pass2->GetTotalWait(), 12);

  Passenger* pass3;
  pass3 = new Passenger(2, "CSCIstudents");
  pass3->Update();
  EXPECT_EQ(pass3->GetTotalWait(), 1);

  Passenger* pass4;
  pass4 = new Passenger(12);
  EXPECT_EQ(pass4->GetTotalWait(), 0);
  for (int i = 0; i < 17; i++) {
    pass4->Update();
  }
  pass4->GetOnBus();
  EXPECT_EQ(pass4->GetTotalWait(), 18);
  pass4->Update();
  EXPECT_EQ(pass4->GetTotalWait(), 19);



  delete pass1;
  delete pass2;
  delete pass3;
  delete pass4;
}

TEST_F(PassengerTests, PrintReport) {
  Passenger* pass1;
  pass1 = new Passenger(10, "tak");
  std::string str1 = "Name: tak\nDestination: 10\nTotal Wait: 0";
  std::string str2 = "\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  std::string expected_out_1 = str1 + str2;
  testing::internal::CaptureStdout();
  pass1->Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, expected_out_1);

  Passenger* pass2;
  pass2 = new Passenger();
  std::string str3 = "Name: Nobody\nDestination: -1\nTotal Wait: 0";
  std::string str4 = "\n\tWait at Stop: 0\n\tTime on bus: 0\n";
  std::string expected_out_2 = str3 + str4;
  testing::internal::CaptureStdout();
  pass2->Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output2, expected_out_2);

  Passenger* pass4;
  pass4 = new Passenger();
  for (int i = 0; i < 10; i++) {
    pass4->Update();
  }
  pass4->GetOnBus();
  std::string str7 = "Name: Nobody\nDestination: -1\nTotal Wait: 11";
  std::string str8 = "\n\tWait at Stop: 10\n\tTime on bus: 1\n";
  std::string expected_out_4 = str7 + str8;
  testing::internal::CaptureStdout();
  pass4->Report(std::cout);
  std::string output4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output4, expected_out_4);
  pass4->Update();
  std::string str9 = "Name: Nobody\nDestination: -1\nTotal Wait: 12";
  std::string str10 = "\n\tWait at Stop: 10\n\tTime on bus: 2\n";
  std::string expected_out_5 = str9 + str10;
  testing::internal::CaptureStdout();
  pass4->Report(std::cout);
  std::string output5 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output5, expected_out_5);

  Passenger* pass3;
  pass3 = new Passenger(12, "UMNstudent");
  for (int i =0; i < 20; i++) {
    pass3->Update();
  }
  pass3->GetOnBus();
  std::string str5 = "Name: UMNstudent\nDestination: 12\nTotal Wait: 21";
  std::string st6 = "\n\tWait at Stop: 20\n\tTime on bus: 1\n";
  std::string expected_out_3 = str5 + st6;
  testing::internal::CaptureStdout();
  pass3->Report(std::cout);
  std::string output3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output3, expected_out_3);

  Passenger* pass5;
  pass5 = new Passenger(82);
  for (int i = 0; i < 2; i++) {
    pass5->Update();
  }
  pass5->GetOnBus();
  for (int i = 0; i < 3; i++) {
    pass5->Update();
  }
  pass5->Update();
  std::string str11 = "Name: Nobody\nDestination: 82\nTotal Wait: 7";
  std::string str12 = "\n\tWait at Stop: 2\n\tTime on bus: 5\n";
  std::string expected_out_6 = str11 + str12;
  testing::internal::CaptureStdout();
  pass5->Report(std::cout);
  std::string output6 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output6, expected_out_6);


  delete pass1;
  delete pass2;
  delete pass3;
  delete pass4;
  delete pass5;
}

TEST_F(PassengerTests, UpdatingPassenger) {
  Passenger* p1;
  p1 = new Passenger();
  p1->GetOnBus();
  p1->Update();
  EXPECT_EQ(p1->GetTotalWait(), 2);

  Passenger* p2;
  p2 = new Passenger(5, "CSCIstudents");
  p2->Update();
  EXPECT_EQ(p2->GetTotalWait(), 1);
  p2->GetOnBus();
  for (int i = 0; i < 7; i++) {
    p2->Update();
  }
  EXPECT_EQ(p2->GetTotalWait(), 9);
  std::string str1 = "Name: CSCIstudents\nDestination: 5\nTotal Wait: 9";
  std::string st2 = "\n\tWait at Stop: 1\n\tTime on bus: 8\n";
  std::string expected_out_1 = str1 + st2;
  testing::internal::CaptureStdout();
  p2->Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, expected_out_1);
  delete p1;
  delete p2;
}
