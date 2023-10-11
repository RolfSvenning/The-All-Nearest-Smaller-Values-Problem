//
// Created by Rolf Svenning on 12/04/2023.
// See https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/
// "We can include constants.h into as many code files as we want,
// but these variables will only be instantiated once and shared across all code files."
//

#ifndef IMPLEMENTATIONS__CONSTANTS_H
#define IMPLEMENTATIONS__CONSTANTS_H

const int n = 4096; // last was n=20001; maybe slightly better to use inline const int n = 20...
//inline const std::array<int, n> A = {19,15,3,4,1,7,9,8,5,6,11,12,13,10,16,17,18,20,2};

#endif //IMPLEMENTATIONS__CONSTANTS_H
