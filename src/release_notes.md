* Refactoring1 (Potential error on generating Passengers at last stop)*
    - branch : refactor/iter2
    - changed: fixes two files config_manager.cc and passenger_generator.cc
    - assumption: User accidently puts the probability at the last stop. It causes serious problem.
    - location : config_manager.cc line # 90 and Line 196
                 <br>
                 currProbabilities = CheckLastProb(currProbabilities); <br>
                 passenger_generator line # 13 to 16 <br>
                 if (probs.back() > 0.0) { <br>
                   probs.pop_back();<br>
                   probs.push_back(0.0);<br>
                 }<br>
    - After refactoring, there has no error causing in generating passenger even if User defined configuration text file contains greater than 0 probability.

* Refactoring2: (Extract Method and Replace Temp with Query)*
    - branch : refactor/iter3
    - list of files : config_manager, bus, route
    - assumption: Developer might need to fix or enhance the code to meet their requirements.
    - location:
        - specification linked to pdf: https://github.umn.edu/umn-csci-3081-f19/repo-han00127/tree/refactor/iter3/project/docs/refactor.pdf
    - After refactoring, the core of the classes in the software is easier to develop the program.

* Regression Test: Deterministic Passenger generation with diverse configuration text files that is user-defined.
    - branch: fix/24-regression-passenger-factory
      branche has already been merged into devel. Don't need to find the branch for Regression test.
    - list of files : deterministic_passenger_factory.cc, deterministic_passenger_factory.h, passenger_factory.cc, passenger_factory.h, rtest_configuration_simulator.cc, rtest_configuration_simulator.h, rtest_passenger_generator.cc, rtest_passenger_generator.h, regression_config_sim_driver.cc
    - usage: Those files mentioned above used only for Regression Test. Our software such as configuration simulator and visualization simulator will be affected by the Regression testing.
    - bugs: In the previous version, regualr simulator and regression test shares the same passenger factory. The bugs occurs when configuration simulator and visualization simulator executes. All generated passengers are same.
    - solution: makes new deterministic passenger factory for passenger generator that is used for regression test not to affect the configuration simulator and visualization simulator. Regression test files only used deterministic passenger factory and passenger generator.
    - How to test: Go to src directory then type "make regression_config_sim_test"
                   then the excutable file exists in the build/bin directory.
