// Copyright (c) 2013 Patrick Huck
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {

  if ( argc < 1 ) return 1;

  std::ifstream inFile;
  inFile.open(argv[1]);
  string line;
  while ( getline(inFile, line) ) {
    cout << line << endl;
  }
  inFile.close();

  return 0;
}
