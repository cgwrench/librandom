#ifndef __debug_h__
#define __debug_h__

#include <stdio.h>

#ifdef NDEBUG
#define debug(message, ...)
#else
#define debug(message, ...) fprintf(stderr, "[DEBUG] (%s:%d) " #message "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define log_error(message, ...) fprintf(stderr, "[ERROR] (%s:%d) " #message "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define log_warn(message, ...) fprintf(stderr, "[WARN] (%s:%d) " #message "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define log_info(message, ...) fprintf(stderr, "[INFO] (%s:%d) " #message "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif
