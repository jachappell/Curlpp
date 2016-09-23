//
// Copyright (c) 2016 James A. Chappell
//
#include "Fetch.h"

#include <iostream>

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

string Fetch::fetch(CURLoption option, const string& url) const
{
  string result;
  
  curl_->SetOpt(option, &result);

  curl_->Url(url);

  long http_status;
  CURLcode res = curl_->Perform(http_status);

  if (res != CURLE_OK)
  {
    cerr << "http_status = " << http_status << "\n";
    cerr << curl_->error() << endl;
  }

  return result;
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
