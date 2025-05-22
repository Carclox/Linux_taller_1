#ifndef MEMINFO_MANIP_H
#define MEMINFO_MANIP_H

#include <stdio.h>
#include <stdbool.h>
#include<string.h>

const char *mem_file = "data2.txt";
const char *output_file;

int meminfo();
void process_memory_info();

#endif // MEMINFO_MANIP_H