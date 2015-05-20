#include <chrono>
#include <unistd.h>
#include <iostream>
#include <signal.h>

//User includes
#include "recognizer.h"


namespace program_timer {
static auto start_time = std::chrono::high_resolution_clock::now();

inline static void start() {
	program_timer::start_time = std::chrono::high_resolution_clock::now();
}

inline void finish() {
	auto end_time = std::chrono::high_resolution_clock::now();
	fprintf(stderr, "Time elapsed: %lu nanosec's\n",
	        std::chrono::duration_cast
	        <std::chrono::nanoseconds>(end_time - start_time).count());
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
	int first_size = 5000, sec_size = 5000;
	int dim_count = 6;
	double *first_seq = new double[first_size * dim_count],
	*sec_seq = new double[sec_size * dim_count];
	for ( int i = 0 ; i < first_size; i++) {
		for (int j = 0; j < dim_count; j++) {
			*(first_seq + i * dim_count + j) = 1;
			*(sec_seq + i * dim_count + j) = -5;
		}
	}
	fprintf(stderr, "Benchmarking recognition of %i dimensions\n", dim_count);
	program_timer::start();
	double res = CompareData(first_seq, first_size, sec_seq, sec_size, dim_count);
	program_timer::finish();
	delete[] first_seq;
	delete[] sec_seq;
	fprintf(stderr, "Result %lf\n", res);
	return 0;
}
