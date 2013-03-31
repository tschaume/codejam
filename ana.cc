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
} p;

std::pair<int,int> getIndexes(const char& c) {
  for ( int i = 0; i < p.vk.size(); ++i ) {  // key index
    for ( int j = 0; j < p.vk[i].size(); ++j ) {  // character index
      if ( p.vk[i][j] != c ) continue;
      return std::make_pair(i+2,j+1);
    }
  }
  return std::make_pair(0,1);
}

int main(int argc, char *argv[]) {

  p.init();
  p.print();

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
    for(string::size_type i = 0; i < line.size(); ++i) {
      std::pair<int,int> ipair = getIndexes(line[i]);  // index pair
      cout << " " << ipair.first << "." << ipair.second;
    }
    cout << endl;
    outFile << "Case #" << nl << ":";
    // --> generate correct output
    outFile << endl;
  }
  inFile.close();
  outFile.close();

  return 0;
}
