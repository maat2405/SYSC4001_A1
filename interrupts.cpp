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
    int context_time = 10; // context

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

            
        }

        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
