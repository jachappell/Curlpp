#include "Fetch.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " url" << endl;
    return 1;
  }

  Fetch fetch;
  
  string data = fetch.Body(argv[1]);

  cout << data << endl;

  return 0;
}
