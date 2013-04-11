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

// given: N flavors of milkshake
// prepare N batches (one for each flavor either melted or unmelted)
// >= 1 type for each customer which he likes
// minimum # of melted batches

struct Customer {
  // each type is a combination of flavor & (un)malted
  int T;  // number of types customer likes
  vector< std::pair<int, bool> > vT;  // vector of types (flavor, malted)
  void print() {
    cout << "  T = " << T << endl;
    for ( int i = 0; i < vT.size(); ++i ) {
      cout << "   " << vT[i].first << " " << vT[i].second << endl;
    }
  }
} C;

struct TestCase {
  int N;  // number of flavors
  int M;  // number of customers
  vector<Customer> vC;  // vector of customers
  void print() {
    cout << "N = " << N << " , M = " << M << endl;
    for ( int i = 0; i < vC.size(); ++i ) vC[i].print();
  }
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
  int nl = -2;
  tc.M = 0;
  while ( getline(inFile, line) ) {
    nl++;
    if ( nl == -1 ) continue;  // first line
    if ( nl%(2+tc.M) == 0 && nl > 1 ) {
      tc.print();
      tc.vC.clear();
    }
    cout << "l." << nl << ": " << line << endl;
    if ( nl%(2+tc.M) == 0 ) tc.N = atoi(line.c_str());
    else if ( nl%(2+tc.M) == 1 ) tc.M = atoi(line.c_str());
    else if ( nl%(2+tc.M) < 2+tc.M ) {
      string buf;
      std::stringstream ss(line);
      int n = -1; int f;
      while ( ss >> buf ) {
        n++;
        if ( n == 0 ) C.T = atoi(buf.c_str());
        else if ( n%2 == 1 ) f = atoi(buf.c_str());
        else if ( n%2 == 0 ) {
          bool flag = atoi(buf.c_str());
          C.vT.push_back(std::make_pair(f, flag));
        }
      }
      tc.vC.push_back(C);
      C.vT.clear();
    }
    outFile << "Case #" << nl << ":";
    // --> generate correct output
    outFile << endl;
  }
  inFile.close();
  outFile.close();

  return 0;
}
