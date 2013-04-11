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
