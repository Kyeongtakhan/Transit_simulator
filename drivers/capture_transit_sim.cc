/**
 * @file capture_transit_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <ctime>
#include <iostream>
#include <random>
#include <fstream>

#include "src/capture_simulator.h"

int main(int argc, char** argv) {
  std::string name_file = "";
  if (argc == 1) {
     name_file = "transit_out.txt";
  } else {
      name_file = argv[1];
  }

  std::ofstream fd;
  fd.open(name_file);

  int rounds = 80;  // Number of rounds of generation to simulate in test

  srand((long)time(NULL));  // Seed the random number generator...

  CaptureLocalSimulator my_sim(fd);

  fd << "/*************************" << std::endl << std::endl;
  fd << "         STARTING" << std::endl;
  fd << "        SIMULATION" << std::endl;
  fd << "*************************/" << std::endl;

  my_sim.Start();

  fd << "/*************************" << std::endl << std::endl;
  fd << "           BEGIN" << std::endl;
  fd << "          UPDATING" << std::endl;
  fd << "*************************/" << std::endl;

  for (int i = 0; i < rounds; i++) {
    my_sim.Update();
  }

  fd << "/*************************" << std::endl << std::endl;
  fd << "        SIMULATION" << std::endl;
  fd << "         COMPLETE" << std::endl;
  fd << "*************************/" << std::endl;

  fd.close();
  return 0;
}
