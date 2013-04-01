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
  vector<int> v1;
  vector<int> v2;
  void printV(const vector<int>& v) {
    cout << "v = ";
    for ( int i = 0; i < v.size(); ++i ) cout << " " << v[i];
    cout << endl;
  }
  void print() { printV(v1); printV(v2); }
  void clear() { v1.clear(); v2.clear(); }
} tc;

typedef vector<TestCase> Data;

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
  Data d;
  while ( getline(inFile, line) ) {
    nl++;
    if ( nl == 0 ) continue;
    cout << line << endl;
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
    if ( nl % 3 == 0 ) d.push_back(tc);
    outFile << "Case #" << nl << ":";
    // --> generate correct output
    outFile << endl;
  }
  inFile.close();
  outFile.close();

  for ( int i = 0; i < d.size(); ++i ) {
    cout << "i = " << i << endl;
    d[i].print();
  } 

  return 0;
}
