//
// Copyright (c) 2016 James A. Chappell

#ifndef STORAGE_B_FETCH_H__
#define STORAGE_B_FETCH_H__

#include <memory>
#include <string>

#include "Curl.h"

namespace Storage_B
{
  namespace Curlpp
  {
    class Fetch
    {
    public:
      Fetch(const char *url = nullptr);
      
      long operator()(std::string& result,
                      CURLoption option = CURLOPT_WRITEDATA) const
      {
        return fetch(option, result);
      }
      
      long operator()(const std::string& url, std::string& result,
                      CURLoption option = CURLOPT_WRITEDATA)
      {
        Url(url);
        return fetch(option, result);
      }

      void Url(const std::string& url)
      {
        curl_->Url(url);
      }

      std::unique_ptr<Curl> const& curl() { return curl_; }


    private:
      long fetch(CURLoption option, std::string& result) const;

      static size_t read_result(void *buffer, size_t size, size_t nmemb,
                                void *stream);

      std::unique_ptr<Curl> curl_;
    };
  }
}
#endif
