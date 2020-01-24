/**
 * @file regression_config_sim_driver.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <fstream>
#include <ostream>
#include "src/rtest_config_manager.h"
#include "src/rtest_configuration_simulator.h"
std::string Is_Output(char**, int);
bool Is_Correct_line_argument(char*);
/*
  This is the function that will check out whether or not line argument contains extra text file to store output where the user want text file.
  This function only iterates from third element of argument. If there is .txt file name, it will return the corresponding name.
*/
std::string Is_Output(char** argmentptr_, int num_argment_) {
    std::string target = ".txt";
    std::string test = "";
    std::string result = "";
    size_t found;
    for (int i =2; i < num_argment_; i++) {
      test = argmentptr_[i];
      found = test.find(target);
      if (found != std::string::npos) {
        return test;
      }
    }
  return result;
}
/*
  This is the function that will check out there is extra configuration variables such as length of sim, and bus_genering timings.
*/
bool Is_Correct_line_argument(char* str) {
    int i;
    std::string test = str;
    if (sscanf(test.c_str(), "%d", &i) == 1) {
        return true;
    } else {
        return false;
    }
}
// *All possible commands lines tested*
int main(int argc, char**argv) {
  std::cout << "Usage: ./build/bin/rtest_configuration_sim <config_filename>";
  std::cout << std::endl;
  std::vector<int> bus_start_timings_;
  int count = 0;
  int rounds = 35;  // default rounds
  int bus_timing = 10;  // defualt rounds
  // name of file that will read configuration routes.
  std::string input_file_name = "";
  // name of file being redirected output.
  std::string output_file_name = "";
  std::ofstream outfile;
  int find_rounds = 0;  // checker for rounds
  bool valid_output = false;
  RtestConfigManager* cm = new RtestConfigManager();
  RtestConfigurationSimulator* config_sim;

  if (argc >= 2) {  // ./config *.txt or more
    input_file_name = argv[1];
    std::ifstream infile("config/" + input_file_name);
     /* try open input config file.
        If error: input file is not open or does not exist,
        then print out error message and use default file "config.txt"
     */
    if (!infile.is_open()) {
      std::cout << "File Opening Failed" << std::endl;
      input_file_name = "config.txt";  // use default file
    }
    infile.close();
    // generates the routes
    cm->ReadConfig(input_file_name);
    // get and set the size of routes in text.
    int size = cm->GetRoutes().size();

    /*
      If output_file_name is empty string, that means there is no .txt file that user want to redirect
      Otherwise, there exists the .txt file that user want to redirect then open the output file.
    */
    output_file_name = Is_Output(argv, argc);
    if (output_file_name != "") {
        valid_output = true;
        outfile.open(output_file_name);
    }

    /*
      Set the extra argument to length of simulation and bus generating if it's valid integer.
      The First appearance should be the length of simulation, otherwise bus_generating timing.
      Bus_start_timing generalization:
        If the routes has more than 2, the bus_generating time is required at least 2.
        For examples, 2 routes -> 1 bus_generting_timing
                      4 routes -> 2 bus_generating_timing
      If the number of bus generating timing is not matched, the program throw the error such that array index bound.
       So the default generation time will be used.
      If there are no valid inputs for rounds, bus_timing_generation, default values will be used.
    */
    for (int i =2; i < argc; i++) {  // valid checker for rounds, bus timing
        if (Is_Correct_line_argument(argv[i]) && find_rounds == 0) {
            rounds = std::atoi(argv[i]);
            find_rounds++;
        } else if (Is_Correct_line_argument(argv[i]) && size /2 != count) {
            bus_start_timings_.push_back(std::atoi(argv[i]));
            count++;
        }
    }
    for (int i = count; i < size /2; i++) {
        std::cout << "Lacks of bus_generting time " <<
          "We will use default bus_timing" <<
          "for" << i+1 << "route" << std::endl;
        bus_start_timings_.push_back(bus_timing);
    }

    /*
     Depending on the output redirection, the constructor of ConfigSimulator will be different.
    */
    if (valid_output) {
        config_sim = new RtestConfigurationSimulator(cm, outfile);
    } else {
        config_sim = new RtestConfigurationSimulator(cm, std::cout);
    }
    // Sets up the configurations
    config_sim->Start(bus_start_timings_);
    for (int i =0; i < rounds; i++) {
        //  Call Update on ConfigurationSimulator
        config_sim->Update();
    }
  } else {  // ./config
    std::cout << "Please type config file name" << std::endl;
    input_file_name = "config.txt";
    cm = new RtestConfigManager();
    cm->ReadConfig(input_file_name);
    bus_start_timings_.push_back(bus_timing);
    config_sim = new RtestConfigurationSimulator(cm, std::cout);
    config_sim->Start(bus_start_timings_);
    for (int i =0; i < rounds; i++) {
        //  Call Update on ConfigurationSimulator
        config_sim->Update();
    }
  }
  return 0;
}
