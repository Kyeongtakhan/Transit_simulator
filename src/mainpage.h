/** \mainpage Transit Simulator made by Kyeongtak Han.
 *
 * \section Intro_sec Introduction
   - - -
 * Welcome, Kyeongtak’s transit simulator
 * This is the real-time bus information system and transit simulator. This is a transit simulator that consists of passengers, stops, routes, and buses. Also, this is a useful software to be further developed and be deployed in the transit industry for the real application. This program will generate the passenger at stops, and the bus on route is moving on two routes with its speeds to pick up the passenger and drop off the passenger at the destination stop. Transit simulator software
 * provides two main simulators. The first main simulator is a configuration simulator that is able to take user or developer defined configuration files to set the configurations. The second simulator is a visualized simulator that shows the all stops in routes, buses, and passengers at stop and bus.<br>
 * [TOC]
 *
 *
 * # Developer Guide
 - - -
 * ## Designing justication
 * The simulator contains core objects which are Bus, Route, Stop, Passenger, PassengerGenerators, config_manager, configuration_simulator.
 *
 * ### Bus
 * The bus is one of the most significant classes in transit simulator. When the bus is generated in the simulator, the bus always has its two routes for the trip. The bus automatically sets up at the first stop in the route with the next stop station information and the distance between the current stop station and the next station. Bus has a BusData struct containing id, position, number of passengers, and capacity to visualize the data. <br>
 * 1) Bus is arriving at Stop
 * - Position
 *   * Bus shows up at the current stop with stop’s longitude and latitude
 * - Behavior
 *   * Load Passenger: If there are passengers at the current stop where the bus is at, bus loads the passengers from the Stop, unless there are no available seats.
 *   * Unload Passenger: If there are passengers on the bus and passengers has the same destination stop where the bus is at, bus drops off the passengers.
 * - Update
 *    * Passengers, distance from the current stop to next stop, previous stop
 *
 * 2) Bus is not arriving at Stop
 * - Position
 *   * Bus shows up at half of the position between previous stop and next stop.
 * - Behavior
 *   * Updating the passenger objects on the Bus
 * - Update
 *   * Passenger’s time on the bus increases and remaining distance to the next stop.
 *
 * 3) Special cases <br>
 * If the bus is at the last station of the outgoing route, the remaining passengers will be dropped off at the last station, then the bus will switch their way to the incoming route. Or if the bus is at the last station of the inbound route, the bus will terminate their trip after dropping off the remaining passengers. Moreover, the bus has its constraint itself for the capacity. The bus cannot overload the passenger on the bus like the real bus. If the bus cannot accommodate those passengers, the bus will leave them in the stop station for the next bus by requesting for stop to re-accommodate the passengers.
 *
 * ### Route
 * The route is a communication way for the bus to access the stop stations in the route. When the route is updated, the route itself generates passengers at each stop based on the probability of which how likely a passenger appears at the stop station and also shares the stops with another bus by cloning the route in the simulator. The bus will dynamically share their route with other generated bus. Thus, once one bus loads the passenger at a specific stop station, the other bus never loads the same passenger form the same stop. Also, when the bus is arriving at the station, the bus will request to set the destination stop to the next stop from the current stop and give the distances between two stop stations. The route updates each stop’s passengers and reports each stops passengers in the route. Route has a RouteData struct containing id and set of StopData struct to visualize the data.
 * - Contains
 *   * Set of Stops
 * - Behavior
 *   * Route updates every stop in the route.
 *   * Route generates new passengers at each stop in the route by using PassengerGenerator.
 *
 * ### Stop
 * The stop is a container that contains the passengers who are waiting for bus and a station where the bus stops. The stop serves as the messenger for the bus and route. For example, when the bus located at stop, the stop responds the bus's request that how many passengers are there and gives the passengers to the bus. Set of stops exists in the route and also when passengers show up at the stop, they will be added into stop to get on the bus. These existing stops are all shared by the route
 * to communicate with the bus. The stop itself updates the passenger’s time when the passenger is waiting for the bus. Stop has a StopData struct containing id, position, number of people to visualize the data.
 * - Contains
 *   * Set of Passengers
 *   * Longitude and Latitude represent the location of Stop.
 * - Behavior
 *   * Stop updates every passenger who are waiting for Bus.
 *
 * ### Passenger
 * A passenger is a basic unit of the transit simulator. Every passenger has a waiting time for the bus and the time on the bus. Also, every passenger owns their destination stop id where he or she wants to go. Depending on the destination stop and speed of the bus, the total waiting time for the passenger is different by each passenger. Passengers are generated by passenger_generator, and generating passengers is subject to the probability that how passenger likely shows up at Stop. Once the
 * passenger shows up at the station, the control of the passenger will depend on the bus and stop. When the bus arrives, the passengers are either loaded on the bus, unloaded to the destination station, or keep staying at the Stop.
 * - Update
 *   * Passenger updates its waiting time or time on the bus.
 *   * Passengers are updated by either Stop or Bus.
 *
 * ### PassengerGenerator
 * PassengerGenerator is an abstract class that contains the virtual PassengerGenerator method. This PassengerGenerator will be declared in RandomPassengerGenerator explained below. PassengerGenerator takes the probability of the stops to generate passenger based on the probability of how likely the passenger shows up at the stop.
 *
 * ### RandomPassengerGenerator
 * RandomPassenger enables the route to generate the passenger randomly based on the stop’s probability. When the Route is being updated, passenger is also being generated. The passenger information derives from the PassengerFactory class.
 * Configuration simulator uses the RandomPassengerGenerator to randomly generate the passengers to stops. Also, visualized simulator uses RandomPassengerGenerator based on probability.
 *
 * ### PassengerFactory
 * Passenger Factory is an actual function that make a passenger object with name of passenger and the destination stop where the passenger wants to go. This PassengerFactory enables the code to avoid specifying and creating the exact passenger class every time.
 *
 * ### ConfigManager
 * A Configuration Manager is a tool to read the configuration text file that defined by the User or Developer. Config Manager makes route object for the visualization simulator and configuration simulator. Config Manager reads the formatted text file and converts text file to  make a route to be used in the simulator.
 * <br> Details of formatting for the configuration files defined in User-Guide.
 *
 * ### Configuration_simulator
 * A configuration simulator takes a configuration text file that contains multiple of routes, stops location, stops name, and probability of passenger coming to stops.
 * Configuration text file should match the correct format in order to be used in config_manager. If the configuration text file does not exist, the default file will be used __config.txt__. Also, the user can define the controllerable variables, especially how many times simulation run, how often the bus being generated, and output redirection. This package is capable of handling wrong configuration text file, multiple routes text file, the wrong number of bus timing, and wrong
 * length of simulation. However, program possibly thorows the error due to the user defined configuration file that contains (last stop probability > 0.0) since the bus has two different routes. Because outbound route and inbound route are different, the passenger in the outbound should have the destination stop in the route. Thus, the passenger who is generated at the last station in outbound must be dropped off in same station.
 * Thus, last station's probability in out and in bound should be always zero.
 *
 * ### Configuration sim
 * A configuration sim is a driver that takes arguments from the user for configuration setting. The configuration simulator will be used the argument for the settings that the user defined. The specification of what argument expected is in User Guide.
 *
 * ### Visualization simulator
 * A visualization simulator is based on the web server and it is connected to web server with the code. The web server is hosted in the local host with the specific port number, which is __127.0.0.1:portnumber__. Visualization simulator shows how the bus is moving, bus's loading/unloading implementations, how many passengers in the bus and stops. This simulator has the same functionality with configuration simulator. The number of simulation and bus generation timing are controllerable by the
 * configuration setting on the web. However, the route and stop are not controllerable.
 * ### deterministic_passenger_factory
 * This factory is made to assist the regression test. This passenger factory always generates the same passenger to test the configuration simulator. Whatever the configuration simualtor reads the configuration files, the expected behavior and output is determined.
  * Unlike the passenger_factory, the passenger generation is determined.
 * ## Programming Guide
 * High-Level Programming Design
 * There are High-Level programming techniques in the software.
 * ### Prototype Pattern with Clone Method
 * Prototype Pattern and Clone method is used for the routes. This pattern allows the developer to hide the complexity of making new instances and to share the same object with the Bus class.
 * For examples, whenever the bus object created, two routes are required for the Bus constructor. Thus, without creating a new instance of the routes, we just get the routes from the Prototype and cloning the routes to bus.
 *
 * ### Factory Class
 * Factory Method is a method that provides an interface for creating passenger object. This pattern allows the software to create the passengers constantly without specifying the passenger everytime in the simulator. This pattern makes the program to generate passengers without any memory overhead. Two passenger factories exist; deterministic_passenger_factory; passenger_factory. The usage details mentioned below.
 *
 * ### Pointers, Dynamic Allocation, and Reference
 * Pointers, Dynamic Allocation, and Reference are used in all source file to improve the performances of the code and efficiently uses the limited memory.
 *
 * ### Regression Test
 * Regression Test is a test to ensure that the modified code still works after modification of the code.
 * The regressions test in this package is a configuration test.  Regression test driver (regression_config_sim_driver.cc) will read a variety configuration files that defined by user. By using the deterministic passenger factory and passenger generator, the generated passenger is always same, but depending on the probability of stops, the stop that passenger shows up will be different.
 *
 * ### Web server communication
 * This software has two main simulators, configuration simulator and visualized simulator. To visualize the code, the local host server is required to draw the maps from the map API and set up the configuration select box. Also, the code interacts with the web server by requesting the data from the code and get current data for Bus, Route, Stop.
 *
 * ### Google Style Compilation
 * The coding style follows the Google Style Compilation. Here is the specification of the Google Style Compilation https://google.github.io/styleguide/cppguide.html.  The tool that developer could check the compilation error is a cpp-lint. The cpp-lint should be installed in your own computer to run.
 * - Benefits of the Google style Compilation
 *   * Google style compilation helps the developers to understand the classes, methods, and variables meaning.
 * - Naming Conventions not captured by cpplint
 *   * Member methods in the class should have a camel case at each word.
 *   * Member variables are all lower case separated by an underscore and end with “_”.
 *   * Local variables have same conventions with member variables except ending character.
 * Ex) bool IsAtEnd() (member method), bool this_is_flag_ (member variable), int temp_variable (variable)
 * - How to use the Google style Compilation
 *   * Go to the directory where you want to google style checking, then type cpplint/cpplint-cse-sh –root= *.cc or *.h
 *   * For example, if you were in the src directory, the command should be ../../cpplint/cpplint-cse-sh –root= *.cc or *.h.
 *
 * # User Guide
  - - -
 * Welcome to real time bus transit simulator again. Here is the user-guide how to download the software package, how to create executable files, how to run the simulator, and everything that user need to know this program. <br>
 * __Note) If you have not yet read the overview of the program, please read it.__
 *
 * __Getting started with downloading the software package.__
 * ## Download the packages
 * Before downloading the package, you should have an authorized account on University of Minnesota GitHub repository. <br>
 * If you don’t have an account on GitHub, please go __https://github.umn.edu__ then sign up please.
 * 1. Command Line in terminal (Linux or Mac possible):
 *    1. Opens up the terminal
 *    2. Makes a directory you want.  Enters __mkdir transit_sim__ then Enters __cd transit_sim__
 *    3. Types __git clone https://github.umn.edu/umn-csci-3081-f19/repo-han00127.git__
 * 2. Web page: <br>
 *    1. Goes to the website (https://github.umn.edu/umn-csci-3081-f19/repo-han00127)
 *    2. clicks the rightmost button (Clone or download). You can see the __Download ZIP__.
 *    3. Then extract the files to the folder where you want to unzip. <br>
 * 3. If you have already a GitHub account, you can fork files to your account by clinking “Fork” button on the top.
 * ## Composition of the packages
 * Project contains 6 directories; config, docs, drivers, src, tests, and web_graphics. <br>
 * __config__ folder contains the configuration text file that you want to set configuration for the simulators (configuration simulator and visualized simulator).<br>
 * __docs__ folder contains UML files, documents for this software.<br>
 * __driver__ folder contains single driver files for simulation to run and regression test driver.<br>
 * __src__ folder contains all necessary source files for simulations.<br>
 * __tests__ folder contains unit tests for source file functionality.<br>
 * __web_graphics__ folder contains the files for the visualized simulator.<br>
 * ## How to create executable files
 * __Getting started with creating executable files for the simulator.__
 * Expected way to create executable files is by the terminal and make sure the spelling should be right.
 * There are four possible executable files in this package. (config_sim, vis_sim, capture_transit_sim, transit_sim) <br>
 * 1. Go to the project directory by typing “cd project” at your cloned folder.
 * 2. If you want to see all available simulator, types __make all__ in the terminal .
 *    This command generates all executable files; config_sim; vis_sim; capture_transit_sim; transit_sim. <br> Or <br> If you want to generate specific simulator, types __make you want to generate listed above__ in the terminal.
 * <br>Ex) __make config_sim make vis_sim make capture_transit_sim make transit_sim__
 * 3. To see the executable files, types __cd ..__ then __cd build/bin__. The directory in build/bin is the directory where all executable files are built.
 *
 * __Getting started with creating test files for the unit test.__ <br>
 * Available unit test files are all_fail_test, bus_test, passenger_test, route_test, stop_test, unittest.
 * 1. At the project directory, Types __make tests__
 * 2. All unit test files are built in the build/bin directory.
 * 3. To see the executable files, type __cd ..__ then __cd build/bin__. The directory in build/bin is the directory where all executable files are built. <br>
 *
 * Addition For Driver Test and Regression Test.
 * 1. At the project directory, types __cd src__
 * 2. enters __make driver name of files_test__ or For the Regression test __make regression_config_sim_test__.
 * 3. To see the executable files, type __cd ..__ then __cd build/bin__. The directory in build/bin is the directory where all executable files are built. <br>
 *
 * ## How to run executable files
 * __Getting started with running executable files for the simulator.__ <br>
 * After creating executable files you want, Navigates to the base project folder.
 * If you have no idea where you are in, just types __pwd__ in the terminal. If the last directory is __project/src__, enters __cd ..__ The command rolling back to project folder depends on the current directory where you are in. If there is 2 more word after project, you should type __cd ..__ two times.<br>
 * project/src $ cd .. <br>
 * project/build/bin $ cd ../../ <br>
 * This commands let you go back to the base direcotory (project) <br>
 * - __config_sim:__ <br>
 * In the project directory, you must type ./build/bin/config_sim <configuration text name.txt> <Option: you want to redirect output to file name.txt> <Option: length of simulation> <Option: bus generating timing> to run config_sim. <br>
 * __Options) Controllerable variables for config_sim__.
 *     * Input text file name -> configuration file you want to use the route for simulator.
 *     * Output redirect file name -> captures output then stores in the file.
 *     * Length of Simulation (Integer) -> simulation rounds.
 *     * Bus generating timing (Integer) -> bus generation timing controller <br>
 * Don’t worry. If you have no idea what you should type. Just types __./build/bin/config_sim__.
 * This command will use the default configuration file (config.txt), length of simulation (35), and bus generating timing (10). You must type __./build/bin/config_sim__. If you miss config_sim, the program won’t work. <br>
 * Example code to run here <br>
 * home/han00127/3081/repo-han00127/project $ make config_sim <br>
 * /home/han00127/3081/repo-han00127/project $./build/bin/config_sim <br>
 * Or <br>
 * /home/han00127/3081/repo-han00127/project $./build/bin/config_sim config.txt redirect.txt 100 30 <br>
 * /home/han00127/3081/repo-han00127/project $./build/bin/config_sim config.txt 100 30 <br>
 * /home/han00127/3081/repo-han00127/project $./build/bin/config_sim config.txt  <br>
 * /home/han00127/3081/repo-han00127/project $./build/bin/config_sim config.txt  50 <br>
 * /home/han00127/3081/repo-han00127/project $./build/bin/config_sim config.txt hello this is cse -> This kind of argument don't allow this configuration simulator <br>
 * - __vis_sim:__ <br>
 * In the project directory, you must types __./build/bin/vis_sim <Required:port number>__ to run vis_sim. Port number should be over the 8000 and shouldn’t be multiples of 10. After typing command, if you successfully connect to server, you will see __Usage: ./build/bin/ExampleServer 8xxx Using default config file: config.txt starting server...__, meaning that you can access to the server on your brewers. You only need to type the following address on your browsers (any browsers). <br>
 * __http://127.0.0.1:port number/web_graphics/project.html__
 * Example code to run here <br>
 * /home/han00127/3081/repo-han00127/project $ make vis_sim <br>
 * /home/han00127/3081/repo-han00127/project $./build/bin/vis_sim 8033 <br>
 * Then if you are successfully connected to server with the software, you can see the image below.

 * ![image1](/home/han00127/3081/repo-han00127/project/docs/1.png)
 * __Top most button__ is a configuration button to controller the simulation rounds. <br>
 * __Next__ one is a configuration for bus generation timings. <br>
 * __Last__ one is a start button to run the program. <br>
 * After starting button, the successful simulation working image is below.
 * ![image1](/home/han00127/3081/repo-han00127/project/docs/2.png)
 *
 * - __capture_transit_sim:__ <br>
 * After making executable file and navigating to the base project folder, types ./build/bin/capture_transit_sim Option:output redirectingname.txt
 * Types ./build/bin/capture_transit_sim. This command generates the default output redirecting text file named transit_out.txt in the project directory. This output file locates on the project folder. If you enter everything with the text file name you want to redirect out, it should be in the project directory. <br>
 * /home/han00127/3081/repo-han00127/project $ make capture_transit_sim <br>
 * /home/han00127/3081/repo-han00127/project $ ./build/bin/capture_transit_sim <br>
 * Or <br>
 * /home/han00127/3081/repo-han00127/project $ ./build/bin/capture_transit_sim testoutput.txt <br>
 * - __transit_sim:__ <br>
 * After making executable file, Navigate to the base project folder, types __./build/bin/transit_sim__ <br>
 * /home/han00127/3081/repo-han00127/project $ ./build/bin/transit_sim
 * - __regression_config_sim_test:__ <br>
 * After making executable file by typing __make regression_config_sim_test__ in src, navigates to the base project folder, types “./build/bin/regression_config_sim_test” <br>
 * regression config_sim will test that when the configuration text file is changed, the expected simulator has the same havior everytime. <br>
 * example code here
 * Types ./build/bin/regression_config_sim_test config_text.txt (you want to test) outputfile.txt (option: simulation rounds) (option: bus generation timing) <br>
 * This command generates the default output redirecting text file you type in terminal in the project directory. This output file locates on the project folder. If you enter everything with the text file name you want to redirect out, it should be in the project directory. <br>
 * /home/han00127/3081/repo-han00127/project/src $ make regression_config_sim_test <br>
 * /home/han00127/3081/repo-han00127/project/src $ cd .. <br>
 * /home/han00127/3081/repo-han00127/project $ ./build/bin/regression_config_sim_test config.txt testoutput.txt <br>
 * /home/han00127/3081/repo-han00127/project $ ./build/bin/regression_config_sim_test config.txt testoutput2.txt <br>
 * /home/han00127/3081/repo-han00127/project $ diff testoutput.txt testoutput2.txt <br>
 * __Note__ that if there is something pop up in the terminal, it means that our regression test fail <br>
 *
 * ## How to clean all executable files
 * Navigate to the project directory, then just type __make clean__ <br>
 * ex) __project $ make clean__
 * ## Additional Note
 * ### Configuration file
 * When you want to use the configuration files declared by you, please follow this formatting. <br>
 * Formatting for the configuration files constraint. <br>
 * The name of configuration files should be the text extension files such as *.txt. <br>
 * The location of configuration files should be in the /config directory.<br>
 * Content of the configuration files must follow up the below formatting. <br>
 * __Note)__
 * - __The last stop’s probability of passenger coming is always zed ro since passenger cannot come to the last stop to take a bus.__
 * - __Longitude: double, Latitude: double, probability: double__
 * - __Refactoring1 in the release_notes in src directory has details of how to solve the problem.__
 * - __The number of routes in the configuration should be even numbers since the bus has their trip from the outbound and inbound route.__
 *
 * __Formatting__ <br>
 * ROUTE_GENERAL, name of Thoroughfare <br>
 *
 * Stop Name, Long, Lat, Pass Gen Prob <br>
 *
 * ROUTE, name of the outbound route <br>
 *
 * STOP, name of stop, Longitude of stop, Latitude of stop, probability of the passenger is coming <br>
 * STOP, name of stop, Longitude of stop, Latitude of stop, 0 <br>
 *
 * ROUTE, name of the outbound route
 * STOP, name of stop, Longitude of stop, Latitude of stop, probability of the passenger is coming <br>
 * STOP, name of stop, Longitude of stop, Latitude of stop, 0 <br>
 *
 * ### Regression Test
 * Regression test is required to generate executable files in the src directory by __typing make regression_config_sim_test__. You shouldn't test the configuration text file that contains the last stop's probability is greater than zero. This kinds of configuration file will throw error whenever it is executed.
 * Please be careful of using the configuration files. If you want to test your own configuration text files, please follow the instruction and formatting mentioned in Configuration file.
 */
