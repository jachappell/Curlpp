//
// Copyright (c) 2016 James A. Chappell
//
#include "Fetch.h"

#include <stdexcept>
#include <string.h>

using namespace std;

class CurlGlobalInit : private boost::noncopyable
{
public:
  CurlGlobalInit()
  {
    Curl::GlobalInit();
  }

  ~CurlGlobalInit()
  {
     Curl::GlobalCleanup();
  }
};


static CurlGlobalInit init;


Fetch::Fetch(const char *url)
  : curl_(make_unique<Curl>())
{
  curl_->SetOpt(CURLOPT_WRITEFUNCTION, read_result);

  if (url)
  {
    Url(url);
  }
}


long Fetch::fetch(CURLoption option, string& result) const
{
  curl_->SetOpt(option, &result);

  long http_status;
  CURLcode res = curl_->Perform(http_status);

  if (res != CURLE_OK)
  {
    string error;
    if (curl_->error() && (strlen(curl_->error()) > 0))
    {
      error = curl_->error();
    }
    else
    {
      error = "CURLcode = " + to_string(res);
    }
    switch(res)
    {
      case CURLE_URL_MALFORMAT:
        throw logic_error(error);
        break;

      default:
        throw runtime_error(error);
        break;
    }
  }

  return http_status;
}


size_t Fetch::read_result(void *buffer, size_t size, size_t nmemb,
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
