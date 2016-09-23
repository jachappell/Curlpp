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
  Fetch();
  ~Fetch();
  
  std::string Body(const std::string& url) const
  {
    return fetch(CURLOPT_WRITEDATA, url);
  }

  std::string Header(const std::string& url) const
  {
    return fetch(CURLOPT_HEADERDATA, url);
  }

  Curl *curl() const { return curl_; }


private:
  std::string fetch(CURLoption option, const std::string& url) const;

  static size_t read_result(void *buffer, size_t size, size_t nmemb,
                            void *stream);
  Curl *curl_;
};

#endif
