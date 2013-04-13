// Copyright (c) 2013 Patrick Huck
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

typedef std::pair<int, int> Coord;  // [row,col] pair/coordinate
typedef map<int, vector<int> > Lawn;  // data/matrix
typedef map<int, vector<Coord> > Mower;  // number to coordinate mapping
Mower::reverse_iterator it;

struct TestCase {
  int row;
  Lawn l;
  Mower m;
  bool loop() {
    if ( verbose ) {
      cout << endl << "Lawn:" << endl;
      for ( int r = 0; r < l.size(); ++r ) {
        for ( int c = 0; c < l[r].size(); ++c ) cout << l[r].at(c) << " ";
        cout << endl;
      }
      cout << "Mower:" << endl;
    }
    for ( it = m.rbegin(); it != m.rend(); it++) {
      if ( verbose ) cout << it->first << ": ";
      for ( int k = 0; k < m[it->first].size(); ++k ) {
        int r = m[it->first].at(k).first;
        int c = m[it->first].at(k).second;
        if ( verbose ) cout << "(" << r << "," << c << ") ";
        // check row
        bool rowOk = true;
        for ( int i = 0; i < l[r].size(); ++i ) {
          if ( it->first < l[r].at(i) ) { rowOk = false; break; }
        }
        // check column
        bool colOk = true;
        for ( int i = 0; i < l.size(); ++i ) {
          if ( it->first < l[i].at(c) ) { colOk = false; break; }
        }
        if ( !rowOk && !colOk ) return false;
      }
      if ( verbose ) cout << endl;
    }
    return true;
  }
  string analyze() { return loop() ? "YES" : "NO"; }
  void clear() { row = 0; l.clear(); m.clear(); }
} tc;

int main(int argc, char *argv[]) {
  if ( argc < 1 ) return 1;
  initIO(argv[1]);
  string line, buf;
  int nl = -1;
  int curNrRows, val;
  int curClearLine = 1;
  int nTC = 0;
  while ( getline(inFile, line) ) {
    nl++; if (!nl) continue;
    std::stringstream ss(line);
    if ( nl == curClearLine ) {
      std::istringstream(line) >> curNrRows;
      curClearLine += curNrRows+1;
      tc.clear();
    } else {  // fill new testcase
      while ( ss >> buf ) {  // fill columns for current row
        std::istringstream(buf) >> val;
        // fill mower
        tc.m[val].push_back(std::make_pair<int>(tc.row, tc.l[tc.row].size()));
        // fill lawn matrix
        tc.l[tc.row].push_back(val);
      }
      tc.row++;
      if ( tc.row == curNrRows ) {
        nTC++;
        outFile << "Case #" << nTC << ": " << tc.analyze() << endl;
      }
    }
  }
  inFile.close();
  outFile.close();
  return 0;
}
