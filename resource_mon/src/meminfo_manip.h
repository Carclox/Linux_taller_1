#ifndef MEMINFO_MANIP_H
#define MEMINFO_MANIP_H

#include <stdio.h>
#include <stdbool.h>
#include<string.h>


int meminfo(FILE *output_data2_file);
void process_memory_info(FILE *mem_input_file, FILE *output_report_file);

#endif // MEMINFO_MANIP_H