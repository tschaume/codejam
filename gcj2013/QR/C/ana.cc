// Copyright (c) 2013 Patrick Huck
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <time.h>

using namespace std;
typedef unsigned long long i64;
std::ifstream inFile;
std::ofstream outFile;
const bool verbose = true;

void initIO(const char* str) {
  string fn(str);
  inFile.open(fn.c_str());
  fn.replace(fn.end()-2, fn.end(), "out");
  outFile.open(fn.c_str());
}

i64 A, B, ii, iRoot, rmin(-1), rmax(-1), nextSquareA;
bool b1, b2;
int cnt, om;
set<i64> fsSet;
clock_t start, stop1, stop2, stop3, stop4, stop5, end;

void print() { cout << "A = " << A << "  B = " << B << endl; }

bool isFair(i64 i) {  //  palindrome
  // order of magnitude
  om = 1; ii = i;
  while ( ii > 9 ) { om*=10; ii/=10; }
  while ( i > 0 ) {
    if ( (i%10) != (i/om) ) return false; // lowest & highest digit
    i=i%om; i/=10; om/=100; // truncate digits
  }
  return true;
}

int analyze() {
  cnt = 0; B++; nextSquareA=-1;
  for ( ; A!=B; ++A ) {
    //if ( !(A%100000000) ) {
    //  end = clock();
    //  cout << A << ": " << (float)(end-start)/CLOCKS_PER_SEC << endl;
    //  start = clock();
    //}
    if ( A >= rmin && A <= rmax ) {  // number already done
      cnt += fsSet.count(A);
      //cout << A << ": b2 = " << b2 << "  iRoot = " << iRoot;
      //cout << "  next2 = " << nextSquareA << endl;
    } else {
      b2 = false;
      if ( nextSquareA<0 ) {  // first square not found yet
        iRoot = (i64)sqrt(A);
        b2 = (iRoot*iRoot==A);
        if (b2) nextSquareA = (iRoot+1)*(iRoot+1);
      }
      else if ( A==nextSquareA ) {
        iRoot = (i64)sqrt(A);
        nextSquareA = (iRoot+1)*(iRoot+1);
        b2 = true;
      }
      if ( b2 && isFair(A) && isFair(iRoot) ) {
        cnt++; fsSet.insert(A);
      }
    }
  }
  return cnt;
}

int main(int argc, char *argv[]) {
  if ( argc < 1 ) return 1;
  initIO(argv[1]);
  string line, buf;
  int nl = -1;
  while ( getline(inFile, line) ) {
    nl++; if (!nl) continue;
    std::istringstream ss(line);
    ss >> A >> B;
    if ( verbose ) print();
    outFile << "Case #" << nl << ": " << analyze() << endl;
    if ( rmin > 0 && A < rmin ) rmin = A;
    if ( rmax > 0 && B > rmax ) rmax = B-1;
    if ( nl == 1 ) { rmin = A; rmax = B; }
    cout << "rmin = " << rmin << "  rmax = " << rmax << endl;
  }
  inFile.close();
  outFile.close();
  return 0;
}
