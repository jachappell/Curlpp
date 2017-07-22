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

  Fetch fetch(argv[1]);
  string data;
  
  long result = fetch.Body(data);

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
