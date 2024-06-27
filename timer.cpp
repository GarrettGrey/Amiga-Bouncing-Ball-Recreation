#include <chrono>
#include <iostream>
#include<unistd.h>

using namespace std;

int main(){
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	sleep(1);
  	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
  	chrono::duration<double, std::milli> time_span = t2 - t1;
  	std::cout << "It took me " << time_span.count() << " milliseconds.";
  	std::cout << std::endl;
}