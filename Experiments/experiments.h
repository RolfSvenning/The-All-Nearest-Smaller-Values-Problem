
#ifndef ANSV2_EXPERIMENTS_H
#define ANSV2_EXPERIMENTS_H

int writeToFile(const std::string& fileName, const std::string& text);

//long largestN(double (*ANSV)(long*, long, long*, long*, long)); // _iobuf fp

void experiment(const std::string& filename, long n, long BLOCK_SIZE, const std::string& algorithmType, const std::string& inputType,  int rounds);
void experimentAllInputs(const std::string& filename, long BLOCK_SIZE, long n, const std::string& algorithmType, int repetitions);
void experimentAllInputsAllAlgorithms(const std::string& filename, long n, long BLOCK_SIZE, int repetitions);

void experimentRunningTime(long largestPowerOfTwo, long BLOCK_SIZE, int repetitions);
void experimentBlocksize(long n, int repetitions);
#endif // ANSV2_EXPERIMENTS_H
