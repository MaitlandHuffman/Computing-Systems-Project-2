Overview
This project simulates a simple queueing system to analyze various performance metrics such as average turnaround time, total throughput, average CPU utilization, and average processes in the ready queue. The simulation uses random interarrival and service times to mimic real-world scenarios and evaluates these metrics for different arrival rates (lambda).

Prerequisites
  C++ compiler (e.g., g++, clang++)
  Standard C++ libraries (iostream, iomanip, queue, cmath, ctime, cstdlib)

Files
  main.cpp: Contains the main logic for the simulation.

Compilation
  To compile the program, use the following command:
    g++ -o process_simulation main.cpp

Usage
  Run the program with the following command:
  ./process_simulation <lambda> <avg_service_time>
  
  <lambda>: The average arrival rate of processes (in arrivals per second) (default is 10).
  <avg_service_time>: The average service time required for each process (in seconds) (default is 0.04).

If no arguments are provided, the program will use the default values.(

Example Commands
  To run the program with default values:
  ./process_simulation
  To run the program with custom values:
  ./process_simulation 15 0.05

Output
  The program outputs a table with the following columns:
  Lambda: The current arrival rate being simulated.
  Average Turnaround Time: The average time taken for processes from arrival to completion.
  Total Throughput: The number of processes completed per unit time.
  Average CPU Utilization: The proportion of time the CPU is busy processing.
  Average Processes in Ready Queue: The average number of processes waiting in the queue.
  
Example Output:
 
Lambda    Average Turnaround Time    Total Throughput    Average CPU Utilization    Average Processes in ready queue
     10                  0.045                222.22                   0.99                        1.01
     11                  0.048                232.56                   0.98                        1.03
     12                  0.052                240.00                   0.97                        1.05
...
     30                  0.097                309.28                   0.94                        1.20



How It Works
  Initialization:
  The random number generator is seeded using the current time.
  Average arrival rate (lambda) and average service time are read from command-line arguments or set to default values.(lambda = 10 and average service time of .04 seconds)


Event Simulation:
  A priority queue (eventQueue) is used to manage events, which can be either process arrivals or departures.
  The first arrival event is initialized and added to the event queue.
  Event Handling:
  The simulation runs until 10,000 processes have completed.
  For each event:
  Arrival: A new process is created with a randomly generated service time. The arrival of the next process is scheduled.
  Departure: The process completes, metrics are updated, and memory is deallocated.
  
Metrics Calculation:
  Turnaround Time: Time from process arrival to completion.
  Throughput: Number of processes completed per unit time.
  CPU Utilization: Proportion of time the CPU is actively processing.
  Processes in Ready Queue: Average number of processes waiting for service.
  Notes
  The random number generation for interarrival and service times uses an exponential distribution.
  Memory management is crucial as processes are dynamically allocated and deallocated.
  
Authors
Maitland Huffman

