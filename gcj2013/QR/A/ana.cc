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
const bool verbose = true;

void initIO(const char* str) {
  string fn(str);
  inFile.open(fn.c_str());
  fn.replace(fn.end()-2, fn.end(), "out");
  outFile.open(fn.c_str());
}

typedef map< int, vector<char> > Board;  // row, column

string tictactoe(vector<char> f) { // return X (won), O (won), -
  int nX(0), nO(0), nT(0);
  for ( int i = 0; i < 4; ++i ) {
    char c = f.at(i); if (c=='.') return "";
    nX += (c=='X'); nO += (c=='O'); nT += (c=='T');
  }
  if ( nX == 4 || ( nX == 3 && nT == 1 ) ) return "X";
  if ( nO == 4 || ( nO == 3 && nT == 1 ) ) return "O";
  return "";
}

struct TestCase {
  int nP;  // number of points
  int row;  // row
  Board b;  // board
  string analyze() {
    string res;
    // rows
    for ( int r = 0; r < 4; ++r ) {
      res = tictactoe(b[r]);
      if ( !res.empty() ) return " "+res+" won";
    }
    // columns
    for ( int c = 0; c < 4; ++c ) {
      vector<char> col;
      for ( int r = 0; r < 4; ++r ) col.push_back(b[r].at(c));
      res = tictactoe(col);
      if ( !res.empty() ) return " "+res+" won";
    }
    // diagonal 1
    vector<char> diag;
    for ( int d = 0; d < 4; ++d ) diag.push_back(b[d].at(d));
    res = tictactoe(diag);
    if ( !res.empty() ) return " "+res+" won";
    // diagonal 2
    vector<char> diag2;
    for ( int d = 0; d < 4; ++d ) diag2.push_back(b[3-d].at(d));
    res = tictactoe(diag2);
    if ( !res.empty() ) return " "+res+" won";
    if ( nP > 0 ) return " Game has not completed";
    return " Draw";
  }
  void clear() { row = 0; nP = 0; b.clear(); }
} tc;

int main(int argc, char *argv[]) {
  if ( argc < 1 ) return 1;
  initIO(argv[1]);
  string line, buf;
  int nl = -1;
  tc.clear();
  while ( getline(inFile, line) ) {
    nl++; if (!nl) continue;
    for ( string::iterator it = line.begin(); it < line.end(); ++it ) {
      if ( *it == '.' ) tc.nP++; 
      tc.b[tc.row].push_back(*it);
    }
    tc.row++;
    if ( line.empty() ) {
      outFile << "Case #" << nl/5 << ":" << tc.analyze() << endl;
      tc.clear();
    }
  }
  inFile.close();
  outFile.close();
  return 0;
}
