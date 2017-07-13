#pragma once

#include <chrono>

#define SUDOKU_SIZE 9
#define EMPTY_VAL 0


#define DEBUG 
#define TIME_MEASURMENT


#ifdef DEBUG
#  define DEBUG_LOG(x) do { std::cerr << x << std::endl; } while (false)
#else
#  define DEBUG_LOG(x) do {} while (false)
#endif