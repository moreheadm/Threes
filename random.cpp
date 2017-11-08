/*
 * File: random.cpp
 *
 *
 */

#include <random>
#include <ctime>
#include "random.h"

std::default_random_engine random_engine(std::time(0));

