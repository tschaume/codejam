// Copyright (c) 2013 Patrick Huck
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

struct TestCase {
  vector<long> v1;
  vector<long> v2;
  void printV(const vector<long>& v) {
    cout << "v = ";
    for ( int i = 0; i < v.size(); ++i ) cout << " " << v[i];
    cout << endl;
  }
  void print() { printV(v1); printV(v2); }
  void clear() { v1.clear(); v2.clear(); }
} tc;

int main(int argc, char *argv[]) {

  if ( argc < 1 ) return 1;

  std::ifstream inFile;
  inFile.open(argv[1]);
  std::ofstream outFile;
  string fn = argv[1];
  fn += ".out";
  outFile.open(fn.c_str());
  string line;
  int nl = -1;
  while ( getline(inFile, line) ) {
    nl++;
    if ( nl == 0 ) continue;
    //cout << line << endl;
    if ( nl % 3 == 1 ) {
      tc.clear();
      continue;
    }
    std::stringstream ss(line);
    string buf;
    while ( ss >> buf ) {
      if ( nl % 3 == 2 ) tc.v1.push_back(atoi(buf.c_str()));
      if ( nl % 3 == 0 ) tc.v2.push_back(atoi(buf.c_str()));
    }
    if ( nl % 3 == 0 ) {
      //tc.print();
      // sort first vector ascending
      std::sort(tc.v1.begin(), tc.v1.end());
      // sort first vector descending
      std::sort(tc.v2.begin(), tc.v2.end(), std::greater<long>());
      // calc scalar product
      long result = 0;
      for ( int j = 0; j < tc.v1.size(); ++j ) {
        result += tc.v1[j] * tc.v2[j];
      }
      outFile << "Case #" << nl/3 << ": " << result << endl;
    }
  }
  inFile.close();
  outFile.close();

  return 0;
}
