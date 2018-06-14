#include "Fetch.h"

#include <iostream>

using namespace std;
using namespace Storage_B::Curlpp;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " url" << endl;
    return 1;
  }

  Fetch fetch(argv[1]);
  string data;
  
  long result = fetch(data);

  if (Curl::httpStatusOK(result))
  {
    cout << data << endl;
  }
  else
  {
    cerr << "http_status = " << result << endl;
  }

  return 0;
}
