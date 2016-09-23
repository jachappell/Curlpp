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


static size_t read_result(void *buffer, size_t size, size_t nmemb,
                                  void *stream)
{
  string *out = static_cast<string *>(stream);
  if (out)
  {
    string new_string((const char* )buffer);
    size_t buf_size = size * nmemb;
    *out += string((const char* )buffer);
    return buf_size;
  }

  return -1;
}


