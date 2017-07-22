//
// Copyright (c) 2016 James A. Chappell

#ifndef __FETCH_H__
#define __FETCH_H__

#include <string>
#include <boost/noncopyable.hpp>

#include "Curl.h"

class Fetch : private boost::noncopyable
{
public:
  Fetch(const char *url = nullptr);
  ~Fetch();
  
  long Body(std::string& result) const
  {
    return fetch(CURLOPT_WRITEDATA, result);
  }
  
  long Body(const char *url, std::string& result)
  {
    Url(url);
    return fetch(CURLOPT_WRITEDATA, result);
  }

  long Header(std::string& result) const
  {
    return fetch(CURLOPT_HEADERDATA, result);
  }

  long Header(const char *url, std::string& result)
  {
    Url(url);
    return fetch(CURLOPT_HEADERDATA, result);
  }

  void Url(const char *url)
  {
    curl_->Url(url);
  }

  Curl *curl() const { return curl_; }


private:
  long fetch(CURLoption option, std::string& result) const;

  static size_t read_result(void *buffer, size_t size, size_t nmemb,
                            void *stream);
  Curl *curl_;
};

#endif
