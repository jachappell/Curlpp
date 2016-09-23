#include "Curl.h"

#include <iostream>

static size_t read_result(void *buffer, size_t size, size_t nmemb, void *stream);

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " url" << endl;
    return 1;
  }
  
  Curl::GlobalInit();

  Curl curl;

  curl_easy_setopt(curl.curl(), CURLOPT_WRITEFUNCTION, read_result);

  string result;

  curl_easy_setopt(curl.curl(), CURLOPT_WRITEDATA, &result);

  curl.Url(argv[1]);
  
  long http_status;
  CURLcode res = curl.Perform(http_status);
    
  cerr << "http_status = " << http_status << "\n";

  Curl::GlobalCleanup();

  if ((res != CURLE_OK) || (http_status != 200))
  {
    cerr << curl.error() << endl;
    return 1;
  }

  cout << result << endl;

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


