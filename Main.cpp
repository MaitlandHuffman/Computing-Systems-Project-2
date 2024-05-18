//Maitland Huffman

#include <iostream>
#include <iomanip>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdlib> 

using namespace std;

// Process structure representing a process in the system
struct Process {
    double arrivalTime; // Time when process arrived
    double serviceTime; // Time needed for service
    double completionTime; // Time when process completed

    Process(double arrival, double service) : arrivalTime(arrival), serviceTime(service), completionTime(0) {}
};

// Event structure representing either process arrival or departure
struct Event {
    double time; // Time of the event
    bool arrival; // True if arrival event, false if departure event
    Process* process; // Pointer to the associated process

    Event(double t, bool a, Process* p) : time(t), arrival(a), process(p) {}
};

// Comparator for priority queue based on event time
struct CompareEvent {
    bool operator()(const Event& e1, const Event& e2) {
        return e1.time > e2.time;
    }
};

// Function to generate random interarrival times
double generateInterarrivalTime(double lambda) {
    return -log(1.0 - static_cast<double>(rand()) / (RAND_MAX + 1.0)) / lambda;
}

// Function to generate random service times
double generateServiceTime(double avgServiceTime) {
    return -log(1.0 - static_cast<double>(rand()) / (RAND_MAX + 1.0)) * avgServiceTime;
}

int main(int argc, char* argv[]) {
    // Seed random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Input average arrival rate and average service time
    double lambda = 10, avgServiceTime = 0.04; // Default values
    if (argc >= 3) {
        lambda = atof(argv[1]);
        avgServiceTime = atof(argv[2]);
    }
    else {
        cout << "Usage: " << argv[0] << " <lambda> <avg_service_time>" << endl;
        cout << "Using default values: lambda = 10, avg_service_time = 0.04" << endl;
    }

    // Output header
    cout << setw(7) << "Lambda" << setw(24) << "Average Turnaround Time" << setw(19) << "Total Throughput" << setw(19) << "Average CPU Utilization" << setw(27) << "Average Processes in Ready Queue\n";

    // Loop through different lambdas
    for (; lambda <= 30; ++lambda) {
        // Initialize event queue
        priority_queue<Event, vector<Event>, CompareEvent> eventQueue;

        // Initialize simulation clock and metrics
        double clock = 0;
        double totalTurnaroundTime = 0;
        double totalCPUUtilization = 0;
        int totalProcessesInReadyQueue = 0;
        int completedProcesses = 0;

        // Initialize first arrival event
        eventQueue.push(Event(generateInterarrivalTime(lambda), true, nullptr));

        // Simulation loop
        while (completedProcesses < 10000) {
            // Get the next event
            Event currentEvent = eventQueue.top();
            eventQueue.pop();
            double eventTime = currentEvent.time;

            // Update metrics
            if (totalProcessesInReadyQueue > 0) {
                totalCPUUtilization += eventTime - clock;
            }
            clock = eventTime;

            if (currentEvent.arrival) { // If arrival event
                // Generate service time for the arriving process
                double serviceTime = generateServiceTime(avgServiceTime);

                // Create the process
                Process* process = new Process(clock, serviceTime);

                // Schedule departure event for the arriving process
                eventQueue.push(Event(clock + serviceTime, false, process));

                // Generate interarrival time for the next arrival
                eventQueue.push(Event(clock + generateInterarrivalTime(lambda), true, nullptr));

                // Update total processes in ready queue
                totalProcessesInReadyQueue++;
            }
            else { // If departure event
                // Update total processes in ready queue
                totalProcessesInReadyQueue--;

                // Update total processes completed
                completedProcesses++;

                // Update completion time for the completed process
                currentEvent.process->completionTime = clock;

                // Calculate turnaround time for the completed process
                double turnaroundTime = currentEvent.process->completionTime - currentEvent.process->arrivalTime;
                totalTurnaroundTime += turnaroundTime;

                // Deallocate memory for completed process
                delete currentEvent.process;
            }
        }

        // Calculate total time for simulation
        double totalTime = clock;

        // Calculate and output metrics
        double averageTurnaroundTime = totalTurnaroundTime / 10000;
        double totalThroughput = 10000 / totalTime;
        double averageCPUUtilization = totalCPUUtilization / totalTime;
        double averageProcessesInReadyQueue = totalProcessesInReadyQueue / totalTime;

        cout << setw(7) << lambda << setw(24) << averageTurnaroundTime << setw(19) << totalThroughput << setw(19) << averageCPUUtilization << setw(27) << averageProcessesInReadyQueue << endl;
    }

    return 0;
}
