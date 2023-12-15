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
    std::cout << "today is: " << ctime(&tt);

    // CREATE FILE
    std::ofstream f;
    f.open(std::ctime(&tt) + std::string("speedup.txt"));
    f << "Writing this to a file.\n";
    f.close();

    std::cout << "Created file maybe?" << std::endl;

}

