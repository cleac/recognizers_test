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

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "Recognizer.h"

void signal_callback_handler(int signum) {
	if (signum == SIGTERM || signum == SIGINT) {
		exit(0);
	}
}

int main(int argc, char const *argv[]) {
	printf("\nrecognizers_test  Copyright (C) 2015  Alexander Nesterenko <nestorf250@gmail.com>\n"
	       "This program comes with ABSOLUTELY NO WARRANTY.\n"
	       "This is free software, and you are welcome to redistribute it\n"
	       "under certain conditions.\n\n");
	//Set handlers to be able to kill program if it gets stuck somewhere
	signal(SIGINT, signal_callback_handler);
	signal(SIGTERM, signal_callback_handler);
	//Init test parameters
	const int dim_count = 2;
	const int templates_count = 2;
	const int template_len = 2;

	Recognizer rec;
	double test_template[3] = {2,2,2};

	RecognitionResult recognitionResult = rec.analyzeData(test_template);
	printf("result is %i with probability: %f", recognitionResult.id, recognitionResult.probability);
	int result = -1;

	fprintf(stdout, "\nRecognized: %i\n", result);
	return 0;
}
