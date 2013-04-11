// Copyright (c) 2013 Patrick Huck
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
typedef long long i64;
std::ifstream inFile;
std::ofstream outFile;
const bool verbose = false;

void initIO(const char* str) {
  string fn(str);
  inFile.open(fn.c_str());
  fn.replace(fn.end()-2, fn.end(), "out");
  outFile.open(fn.c_str());
}

struct TestCase {
  int N;  // number of snappers
  i64 K;  // number of clicks
  void print() { cout << "N = " << N << "  K = " << K << endl; }
  void clear() { N = -1; K = -1; }
  bool ok() { return ( N < 0 && K < 0 ); }
} tc;

int main(int argc, char *argv[]) {
  if ( argc < 1 ) return 1;
  initIO(argv[1]);
  string line, buf;
  int nl = -1;
  while ( getline(inFile, line) ) {
    nl++; if (!nl) continue;
    std::stringstream ss(line);
    tc.clear();
    while ( ss >> buf ) {
      if ( tc.ok() ) std::istringstream(buf) >> tc.N;
      else std::istringstream(buf) >> tc.K;
    }
    tc.print();
    outFile << "Case #" << nl << ":";
    // --> generate correct output
    outFile << endl;
  }
  inFile.close();
  outFile.close();
  return 0;
}
