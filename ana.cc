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
    for( int i = 0; i < vp.size(); ++i) {
      cout << "  " << vp[i];
    }
    cout << endl;
  }
};

struct InputFile {
  int N;  // number of test cases (N = 10/50)
  vector<TestCase> vtc;  // vector of test cases
  void print() {
    cout << "N = " << N << endl;
    for( int i = 0; i < vtc.size(); ++i) {
      vtc[i].print();
    }
  }
};

// TODO: use fin.N to check #cases in input file
// TODO: check read-in variables and its limits
int main(int argc, char *argv[]) {

  if ( argc < 1 ) return 1;  // missing input file

  InputFile fin;
  std::ifstream inFile;
  inFile.open(argv[1]);
  int nl = -1;
  string line;
  while ( getline(inFile, line) ) {
    cout << line << endl;
    nl++;
    if ( nl == 0 ) {  // special case: first line
      fin.N = atoi(line.c_str());
      continue;
    }
    TestCase tc;
    std::stringstream ss(line);
    string buf;
    switch ( nl % 3 ) {
    case 1:  // store credit
      tc.C = atoi(line.c_str()); break;
    case 2:  // number of items
      tc.I = atoi(line.c_str()); break;
    case 0:  // vector of prices
      while ( ss >> buf) {
        tc.vp.push_back(atoi(buf.c_str()));
      }
      fin.vtc.push_back(tc);
      break;
    default: break;
    }
  }
  inFile.close();
  cout << "number of lines = " << nl << endl;
  fin.print();

  return 0;
}
