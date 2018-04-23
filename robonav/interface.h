/*
Interface.h
Date: 15/03/18
Author: 101119509
Description: [Add Details]
*/

#pragma once
#include "Search.h"

void selectSearchAlgorithm(char* argv[], Search& aObject);

bool readData(char *argv[], Search& aObject);

bool writeData(char *argv[], Search& aObject);