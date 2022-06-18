#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;
int main(int argc, char** argv) {
 unique_ptr<logging> log;
  try {
    log = make_unique<logging>();
  } catch (const exception& e) {
    cout << "Error: logging initialization failed: " << e.what() << endl;
    return 2;
  } catch (...) {
    cout << "Error: logging initialization failed" << endl;
    return 2;
  }

  try {
    if (argc < 3) {
      cout << "Usage: ber <file 1> <file 2>" << endl;
      return 1;
    }

    auto start = chrono::high_resolution_clock::now();
    log->print("opening file1: ", argv[1]);
    std::ifstream f1(argv[1]);
    log->print("opening file2: ", argv[2]);
    ifstream f2(argv[2]);
  }
}
