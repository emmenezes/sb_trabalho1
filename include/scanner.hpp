#ifndef SCANNER_H
#define SCANNER_H

#include "../include/datatypes.hpp"
#include "../include/error.hpp"

#include <ctype.h>

void CleanMatrix(tokenMatrix * matrix);
void LexicCheck(tokenMatrix * matrix, std::vector<compilationError> * error_list);

#endif