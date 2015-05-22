# recognizers_test
### Description
This is a project for testing recognition algorythms and mesuring such parameters
 - time of work
 - memory usage

**Attention!**
  All the algorythms imlemented on this repo are C-compatible, but measurement system is not - it's written on C++
 
### Dependencies:
 - **valgrind** (it's used now for memory calculations)
 - **gcc 4.8+** (this is the lowest version I tried to build it on; i think it's definitely could be build on lower versions)
 - **make**
 
### Implemented algorythms:
 - Dynamic Time Warp (tag *comparsion_recognition*)
 
### Usage:
 1. Clone the repo (e.g. `git clone https://github.com/cleac/recognizers_test`)
 2. Checkout to tag you're interested (e.g. `git checkout comparsion_recognition`)
 3. Call command `make` (or `make all`) - you will get all the info in the stdout
