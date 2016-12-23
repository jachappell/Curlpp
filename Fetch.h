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
  typedef std::pair<CURLcode, long> Status;

  Fetch();
  ~Fetch();
  
  Status Body(const std::string& url, std::string& result) const
  {
    return fetch(CURLOPT_WRITEDATA, url, result);
  }

  Status Header(const std::string& url, std::string& result) const
  {
    return fetch(CURLOPT_HEADERDATA, url, result);
  }

  Curl *curl() const { return curl_; }


private:
  Status fetch(CURLoption option, const std::string& url, std::string& result
               ) const;

  static size_t read_result(void *buffer, size_t size, size_t nmemb,
                            void *stream);
  Curl *curl_;
};

#endif
