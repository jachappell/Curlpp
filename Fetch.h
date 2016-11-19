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
  
  CURLcode Body(const std::string& url, std::string& result,
                long& http_status) const
  {
    return fetch(CURLOPT_WRITEDATA, url, result, http_status);
  }

  CURLcode Header(const std::string& url, std::string& result,
                  long& http_status) const
  {
    return fetch(CURLOPT_HEADERDATA, url, result, http_status);
  }

  Curl *curl() const { return curl_; }


private:
  CURLcode fetch(CURLoption option, const std::string& url,
                 std::string& result, long& http_status) const;

  static size_t read_result(void *buffer, size_t size, size_t nmemb,
                            void *stream);
  Curl *curl_;
};

#endif
