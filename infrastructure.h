/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * 基础设施
 */

#pragma once
#include <stdbool.h>

//颜色宏定义
#define CWL_NONE         "\033[m"
#define CWL_RED          "\033[0;32;31m"
#define CWL_LIGHT_RED    "\033[1;31m"
#define CWL_GREEN        "\033[0;32;32m"
#define CWL_LIGHT_GREEN  "\033[1;32m"
#define CWL_BLUE         "\033[0;32;34m"
#define CWL_LIGHT_BLUE   "\033[1;34m"
#define CWL_DARK_GRAY    "\033[1;30m"
#define CWL_CYAN         "\033[0;36m"
#define CWL_LIGHT_CYAN   "\033[1;36m"
#define CWL_PURPLE       "\033[0;35m"
#define CWL_LIGHT_PURPLE "\033[1;35m"
#define CWL_BROWN        "\033[0;33m"
#define CWL_YELLOW       "\033[1;33m"
#define CWL_LIGHT_GRAY   "\033[0;37m"
#define CWL_WHITE        "\033[1;37m"
#include <stddef.h>


typedef struct struct_range {
	size_t left;
	size_t right;
} range_t;

typedef unsigned int uint;
typedef unsigned char byte;
#define USE_ARRAY(T) typedef struct struct_array_##T{uint length; T* items;} array_##T;
#define ARRAY(T) array_##T

USE_ARRAY(range_t)

#define LONG_LINE "--------------------------------------------\n"

