#include "experiments.h"
#include "iostream"
#include <fstream>

// DATE
#include "ctime"
#include "chrono"

void speedup(int rounds, int repetitions){
    std::cout << "Speedup experiment with rounds, repetitions: " << rounds << ", " << repetitions << std::endl;

    // CREATE FILE
    auto fileName = "../Experiments/Results/test_rounds" + std::to_string(rounds) + "_reps" + std::to_string(repetitions) + ".txt";
    auto fileName2 = fileName.c_str();
    std::ofstream f (fileName2);
    auto fp = fopen(fileName.c_str(), "w");

    // DATE
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t ( today );
    std::string date = std::ctime(&tt);
    const char *dateFinal = date.c_str();
    fputs(dateFinal, fp);


    // RUN EXPERIMENT

    
    // WRITE DATE
    f.close();
}

