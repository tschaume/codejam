// Copyright (c) 2013 Patrick Huck
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
typedef long long i64;
std::ifstream inFile;
std::ofstream outFile;
const bool verbose = false;

void progress(const int& n) {
  if ( !(n%100) ) cout << "." << flush;
  if ( !(n%1000) ) cout << " " << n/1000 << "k" << endl;
}

void initIO(const char* str) {
  string fn(str);
  inFile.open(fn.c_str());
  fn.replace(fn.end()-2, fn.end(), "out");
  outFile.open(fn.c_str());
}

struct Snapper {
  bool on; bool power;
  void init() { on = 0; power = 0; }
  void toggle() { if ( power ) on = !on; }
  bool open() { return ( on && power ); }
  void print() { if ( verbose ) cout << "  " << on << " " << power << "  "; }
};

struct TestCase {
  int N;  // number of snappers
  i64 K;  // number of clicks
  vector<Snapper> v;  // vector of Snappers
  inline void print(bool hdr = true) {
    if ( !verbose ) return;
    if ( hdr ) cout << "N = " << N << "  K = " << K << endl;
    for ( int n = 0; n < N; ++n ) v[n].print();
    cout << endl;
  }
  void clear() { N = -1; K = -1; }
  bool ok() { return ( N < 0 && K < 0 ); }
  void init() { 
    Snapper s;
    v.push_back(s);
    v[0].on = 0; v[0].power = 1;  // v[0] always has power
    for ( int n = 1; n < N; ++n ) { 
      v.push_back(s); v[n].init();
    }
  }
  inline void click() {
    v[0].toggle();  // v[0] always toggles
    for ( int n = 1; n < N; ++n ) {
      v[n].toggle(); 
      v[n].power = v[n-1].open();
    }
  }
  string light() {
    return ( (K+1) % (1<<N) == 0 ) ? "ON" : "OFF";
    for ( int n = 0; n < N; ++n ) {
      if ( v[n].open() ) continue;
      return "OFF";
    }
    return "ON";
  };
} tc;

int main(int argc, char *argv[]) {
  if ( argc < 1 ) return 1;
  initIO(argv[1]);
  string line, buf;
  int nl = -1, k;
  std::stringstream ss;
  vector<std::ostringstream> rs;
  while ( getline(inFile, line) ) {
    nl++; if (!nl) continue;
    ss.str() = line;
    tc.clear();
    while ( ss >> buf ) {
      if ( tc.ok() ) std::istringstream(buf) >> tc.N;
      else std::istringstream(buf) >> tc.K;
    }
    tc.init();
    tc.print();
#pragma omp parallel for default(shared) private(tc, k) num_threads(4)
    for ( k = 0; k < tc.K; ++k ) { tc.click(); tc.print(0); }
    outFile << "Case #" << nl << ": " << tc.light() << endl;
  }

  inFile.close();
  outFile.close();
  return 0;
}
