#include <chrono>
#include <unistd.h>
#include <iostream>
#include <signal.h>

//User includes
#include "uwave_recognizer.h"
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
	signal(SIGINT, signal_callback_handler);
	signal(SIGTERM, signal_callback_handler);
	//Init test parameters
	const int dim_count = 6;
	const int templates_count = 250;
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
		result = findMatch(fake_data,template_len);
	} program_timer::finish();
	delete[] fake_data;
	fprintf(stderr, "%i\n", result);
	clearTestTemplates();
	return 0;
}
