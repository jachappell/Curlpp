//
// Copyright (c) 2016 James A. Chappell
//
#include "Fetch.h"

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


Fetch::Fetch()
{
  curl_ = new Curl();

  curl_->SetOpt(CURLOPT_WRITEFUNCTION, read_result);
}

Fetch::~Fetch()
{
  delete curl_;
}

CURLcode Fetch::fetch(CURLoption option, const string& url,
                      string& result, long& http_status) const
{
  curl_->SetOpt(option, &result);

  curl_->Url(url);

  CURLcode res = curl_->Perform(http_status);

  if (res != CURLE_OK)
  {
    if (strlen(curl_->error()) > 0)
    {
      result = curl_->error();
    }
  }

  return res;
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
