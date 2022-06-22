#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

Miara OH(Miara h1, Miara h2)
{
    Miara x = h1 ^ h2;
    Miara setBits = 0;
    while (x > 0)
    {
        B += x & 1;
        x >>= 1;
    }
    return B;
}


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
