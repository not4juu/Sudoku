#pragma once

//#define DEBUG 

#ifdef DEBUG
#  define DEBUG_LOG(x) do { std::cerr << x std::endl; } while (false)
#else
#  define DEBUG_LOG(x) do {} while (false)
#endif