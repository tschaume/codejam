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

typedef vector<char> Key;  // characters for each key

struct Pad {
  vector<Key> vk;  // vector of keys
  void init() {
    Key k;
    for ( char c = 'a'; c <= 'z'; ++c ) {  // loop alphabet
      k.push_back(c);
      bool isExcept = (vk.size() == 5 || vk.size() == 7);
      if ( ( isExcept && k.size() == 4 ) ||
           ( !isExcept && k.size() == 3 ) ) {
        vk.push_back(k); k.clear();
      }
    }
  }
  void print() {
    for ( int i = 0; i < vk.size(); ++i ) {
      cout << i << ":";
      for ( int j = 0; j < vk[i].size(); ++j ) {
        cout << " " << vk[i][j];
      }
      cout << endl;
    }
  }
};

int main(int argc, char *argv[]) {

  Pad p;
  p.init();
  p.print();
  return 0;

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
    cout << line << endl;
    // --> do something with line (stringstream etc.)
    outFile << "Case #" << nl << ":";
    // --> generate correct output
    outFile << endl;
  }
  inFile.close();
  outFile.close();

  return 0;
}
