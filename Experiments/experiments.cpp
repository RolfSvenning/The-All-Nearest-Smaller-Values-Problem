#include "experiments.h"
#include "iostream"
#include <fstream>

// DATE
#include "ctime"
#include "chrono"

void speedup(int rounds, int repetitions){
    std::cout << "Speedup experiment with rounds, repetitions: " << rounds << ", " << repetitions << std::endl;

    // DATE
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t ( today );

    // CREATE FILE
    auto fileName = "../Experiments/Results/" + std::to_string(rounds) + " " + std::to_string(repetitions) + " " + std::ctime(&tt) + std::string(".txt");
    std::ofstream f (fileName);
    f.open(fileName); // std::ctime(&tt) + std::string("speedup.txt")
    f << "Writing this to a file.\n";
    f.close();

//    std::cout << "Created file maybe?" << std::endl;

}

