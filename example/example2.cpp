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
  
  Fetch::Status result = fetch.Body(data);

  if (result.first == CURLE_OK)
  {
    if ((result.second >= 200) && (result.second < 300))
    {
      cout << data << endl;
    }
    else
    {
      cout << "http_status = " << result.second << endl;
    }
  }
  else
  {
    cerr << "CURLcode = " << result.first << ": " << data << endl;
  }

  return result.first;
}
