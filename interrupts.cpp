/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 * 
 * @author Maathusan Sathiendran
 * @author Sonai Haghgooie
 *
 */

#include<interrupts.hpp>

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/

    int simulation_time = 0; // this is the total duration of the sim
    const int context_time = 10; // context
    const int isr_time = 40; // isr

    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        //activity will return from the file which kind, duration_intr is the duration of the interrupt
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/

        if (activity == "CPU") {
            execution += std::to_string(simulation_time) + ", " + std::to_string(duration_intr) + ", CPU Burst\n";
            simulation_time += duration_intr;
        }

        else if (activity == "SYSCALL") {
            auto [execution_temp, simulation_time_temp] = intr_boilerplate(simulation_time, duration_intr, context_time, vectors);
            execution += execution_temp;
            simulation_time = simulation_time_temp;

            execution += std::to_string(simulation_time) + ", " + std::to_string(delays[duration_intr]) + ", " + "SYSCALL: run the ISR for device " + std::to_string(duration_intr) + "\n";
            simulation_time += delays[duration_intr];

            execution += std::to_string(simulation_time) + ", " + std::to_string(isr_time) + ", " + "transfer data from device to memory\n";
            simulation_time += isr_time;

            execution += std::to_string(simulation_time) + ", " + std::to_string(isr_time) + ", " + "check for errors\n";
            simulation_time += isr_time;

            execution += std::to_string(simulation_time) + ", " + std::to_string(1) + ", " + "IRET\n";
            simulation_time++;

        }

        else if (activity == "END_IO") {
            auto [execution_temp, simulation_time_temp] = intr_boilerplate(simulation_time, duration_intr, context_time, vectors);
            execution += execution_temp;
            simulation_time = simulation_time_temp;

            execution += std::to_string(simulation_time) + ", " + std::to_string(delays[duration_intr]) + ", " + "END I/O\n";
            simulation_time += delays[duration_intr];

            execution += std::to_string(simulation_time) + ", " + std::to_string(1) + ", " + "IRET\n";
            simulation_time++;
        }

        else if (activity == "UNKOWN_ACTIVITY") {
            execution += std::to_string(simulation_time) + ", " + std::to_string(1) + ", " + "Unknown Activity\n";
            simulation_time++;
        }

        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
