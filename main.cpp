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

#include "criteria_recognizer.h"
#include "fake_templates.h"


namespace program_timer {
static auto start_time = std::chrono::high_resolution_clock::now();

inline static void start() {
	program_timer::start_time = std::chrono::high_resolution_clock::now();
}

inline void finish() {
	auto end_time = std::chrono::high_resolution_clock::now();
	fprintf(stderr, "Time elapsed: %lu microsec's\n",
	        std::chrono::duration_cast
	        <std::chrono::microseconds>(end_time - start_time).count());
}
};//TIMER

void signal_callback_handler(int signum) {
	if (signum == SIGTERM || signum == SIGINT) {
		program_timer::finish();
		exit(0);
	}
}

int main(int argc, char const *argv[]) {
	if (argc > 1 && !strcmp(argv[1], "-h")) {
		printf("%s\n", "recognizers_test  Copyright (C) 2015  Alexander Nesterenko <nestorf250@gmail.com>\n"
		       "This program comes with ABSOLUTELY NO WARRANTY.\n"
		       "This is free software, and you are welcome to redistribute it\n"
		       "under certain conditions.\n");
		exit(0);
	}

	signal(SIGINT, signal_callback_handler);
	signal(SIGTERM, signal_callback_handler);
	//Init test parameters
	const int dim_count = 6;
	const int templates_count = 4;
	const int template_len = 50;
	//Init fake test data
	double* fake_data = new double[dim_count * template_len];
	for (int i = 0 ; i < template_len ; i++)
		for (int j = 0; j < dim_count; j++)
			*(fake_data + i * dim_count + j) = 10;
	//Init fake test templates
	initTestTemplates(templates_count, dim_count, template_len);
	//Benchmark algorythm
	int result = -1;
	program_timer::start(); {
		// double res = CompareData(first_seq, first_size, sec_seq, sec_size, dim_count);
		/*result = findMatch(fake_data, template_len);*/
		buildTree(fake_data,template_len,1,dim_count);
	} program_timer::finish();
	delete[] fake_data;
	fprintf(stderr, "%i\n", result);
	clearTestTemplates();
	return 0;
}
