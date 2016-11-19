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
  string data;
  long http_status;
  
  CURLcode result = fetch.Body(argv[1], data, http_status);

  if (result == CURLE_OK)
  {
    if ((http_status >= 200) && (http_status < 300))
    {
      cout << data << endl;
    }
    else
    {
      cout << "http_status = " << http_status << endl;
    }
  }
  else
  {
    cerr << "CURLcode = " << result << ": " << data << endl;
  }

  return result;
}
