#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

int recursion(int n, int threadNum, bool loggingEnabled) {
    if (n == 0) {
	return 0;
    }
    if (loggingEnabled) {
        std::cout << "\nThread [#" << threadNum << "]: " << n;
    }
    return n + recursion(n - 1, threadNum, loggingEnabled);
}

std::tuple<int, bool> options() {
     int numOfFibonnaci;
     std::string loggingEnabledInput;

    std::cout << "Fibonnaci Simulator V1.0\n";
    std::cout << "\nEnter number of Fibonacci Numbers >> ";
    std::cin >> numOfFibonnaci;
    std::cout << "Enable logging [Yes, No] >> ";
    std::cin >> loggingEnabledInput;
    std::transform(loggingEnabledInput.begin(), loggingEnabledInput.end(), loggingEnabledInput.begin(),
		[](unsigned char c) { return std::tolower(c); });

    if (loggingEnabledInput == "yes" || loggingEnabledInput == "true") {
        return std::make_tuple(numOfFibonnaci, true);
    }
	return std::make_tuple(numOfFibonnaci, false);
    }

int main() {
    auto listOfOption = options();
    auto start = std::chrono::high_resolution_clock::now();
    int numOfSequences = std::get<0>(listOfOption);
    bool loggingEnabled = std::get<1>(listOfOption);
    int numOfThreads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;

     for (int x = 0; x < numOfThreads; x++) {
	  threads.emplace_back(recursion, numOfSequences / numOfThreads, x, loggingEnabled);
     }
     for (auto& thread : threads) {
          thread.join();
     }

     auto end = std::chrono::high_resolution_clock::now();
     std::chrono::duration<double> elapsed = end - start;
     std::cout << "\nTime taken: " << elapsed.count() << " seconds" << std::endl;
     return 0;
  }
