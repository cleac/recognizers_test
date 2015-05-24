/*
This file is part of recognizers_test

Copyright (C) 2015  Alexander Nesterenko <nestorf250@gmail.com>

This program is free software: you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see < http : //www.gnu.org/licenses/>.
*/

#include <chrono>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <signal.h>

#include "memory_counter.h"
#include "fake_templates.h"
#include "comparsion_recognizer.h"

#define init_analyze	algo_analyzer::init();
#define end_analyze		algo_analyzer::finish();


namespace algo_analyzer {
static auto start_time = std::chrono::high_resolution_clock::now();

inline static void init() {
	algo_analyzer::start_time = std::chrono::high_resolution_clock::now();

}

inline void finish() {
	auto end_time = std::chrono::high_resolution_clock::now();
	clearTestTemplates();
	freeFakeData();
	fprintf(stderr, "Time elapsed: %lu microsec's\n",
	        std::chrono::duration_cast
	        <std::chrono::microseconds>(end_time - start_time).count());
	fprintf(stderr, "Memory of templates used %u\n", getTemplateMemoryUsage());
	fprintf(stderr, "Memory allocated by classifier %lu\n", getUsedMemory());
}
};

void signal_callback_handler(int signum) {
	if (signum == SIGTERM || signum == SIGINT) {
		algo_analyzer::finish();
		exit(0);
	}
}

int main(int argc, char const *argv[]) {
	printf("\nrecognizers_test  Copyright (C) 2015  Alexander Nesterenko <nestorf250@gmail.com>\n"
	       "This program comes with ABSOLUTELY NO WARRANTY.\n"
	       "This is free software, and you are welcome to redistribute it\n"
	       "under certain conditions.\n\n");
	//Set handlers to be able to kill program
	signal(SIGINT, signal_callback_handler);
	signal(SIGTERM, signal_callback_handler);

	//Init test parameters
	const int dim_count = 6;
	const int templates_count = 4;
	const int template_len = 50;
	//Init fake test data
	double* fake_data = getFakeData(dim_count, template_len);
	for (int i = 0 ; i < template_len ; i++)
		for (int j = 0; j < dim_count; j++)
			*(fake_data + i * dim_count + j) = 10;
	//Init fake test templates
	initTestTemplates(templates_count, dim_count, template_len);
	//Benchmark algorythm
	int result = -1;
	init_analyze
	{
		result = findMatch(fake_data, template_len, dim_count);
	}
	end_analyze
	fprintf(stderr, "Recognized: %i\n", result);
	return 0;
}
