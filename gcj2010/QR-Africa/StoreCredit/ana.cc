// Copyright (c) 2013 Patrick Huck
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

struct TestCase {
  int C;  // store credit (5 <= C <= 1000)
  int I;  // number of items in the store (3 <= I <= 100/2000)
  vector<int> vp;  // vector of prices P (1 <= P <= 1000)
  void print() {
    cout << "  C = " << C << "  I = " << I << endl;
    cout << "  vp = ";
    for( int i = 0; i < vp.size(); ++i) cout << "  " << vp[i];
    cout << endl;
  }
};

// TODO: check read-in variables and its limits
int main(int argc, char *argv[]) {

  if ( argc < 1 ) return 1;  // missing input file

  std::ifstream inFile;
  inFile.open(argv[1]);
  int nl = -1;
  string line;
  std::ofstream outFile;
  string fnout = argv[1];
  fnout += ".out";
  outFile.open(fnout.c_str());
  TestCase tc;
  int c = 0;
  while ( getline(inFile, line) ) {
    nl++;
    if ( nl == 0 ) continue;
    cout << line << endl;
    std::stringstream ss(line);
    string buf;
    switch ( nl % 3 ) {
    case 1:  // store credit
      tc.vp.clear();
      tc.C = atoi(line.c_str()); break;
    case 2:  // number of items
      tc.I = atoi(line.c_str()); break;
    case 0:  // vector of prices
      while ( ss >> buf) tc.vp.push_back(atoi(buf.c_str()));
      c++;
      tc.print();
      break;
    default: break;
    }
    bool done = false;  // flag to abort if match found
    for (int i = 0; i < tc.I; ++i) {  // loop prices
      int p1 = tc.vp[i];  // first price
      if ( p1 > tc.C ) continue;  // not enough credit
      for (int j = i+1; j < tc.I; ++j) {
        int p2 = tc.vp[j];  // second price
        if ( p2 > tc.C ) continue;  // not enough credit
        if ( p1+p2 != tc.C ) continue;  // prices don't match
        done = true;  // matching prices found
        outFile << "Case #" << c+1 << ": " << i+1 << " " << j+1 << endl;
        break;
      }
      if ( done ) break;  // solution is unique
    }
  }
  inFile.close();
  outFile.close();
  
  return 0;
}
