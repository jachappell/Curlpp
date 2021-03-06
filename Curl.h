//
// Copyright (c) 2016 James A. Chappell
//
//  A very simple c++ wrapper around libcurl
//
#ifndef STORAGE_B_CURL_H_
#define STORAGE_B_CURL_H_

#include <curl/curl.h>
#include <string>
#include <cctype>

namespace Storage_B
{
  namespace Curlpp
  {
    class Curl
    {
    public:
      Curl()
        : curl_(curl_easy_init())
        , headers_(nullptr)
        , post_(nullptr)
        , last_(nullptr)
      {
        SetOpt(CURLOPT_NOSIGNAL, 1);
        SetOpt(CURLOPT_ERRORBUFFER, error_buffer_);
      }

      // no copy
      Curl(const Curl&) = delete;
      Curl& operator=(const Curl&) = delete;

      ~Curl()
      {
        ClearHeaders();
        ClearForm();
        curl_easy_cleanup(curl_);
      }

      CURL *curl() const { return curl_; }

      CURLcode Url(const std::string& url)
      {
        return SetOpt(CURLOPT_URL, url.c_str());
      }

      CURLcode SetOpt(CURLoption option, const char *parameter)
      {
        return curl_easy_setopt(curl_, option, parameter);
      } 

      CURLcode SetOpt(CURLoption option, int parameter)
      {
        return curl_easy_setopt(curl_, option, parameter);
      } 

      CURLcode SetOpt(CURLoption option, size_t (*f)(void *, size_t, size_t,
                                                     void *))
      {
        return curl_easy_setopt(curl_, option, f);
      } 

      CURLcode SetOpt(CURLoption option, void *parameter)
      {
        return curl_easy_setopt(curl_, option, parameter);
      }

      CURLcode SetVerbose()
      {
        return SetOpt(CURLOPT_VERBOSE, 1);
      } 

      void AppendHeaders(const std::string& header)
      {
        headers_ = curl_slist_append(headers_, header.c_str());
      }

      void Header()
      {
        SetOpt(CURLOPT_HTTPHEADER, headers_);
      }

      void ClearHeaders()
      {
        if (headers_)
        {
          curl_slist_free_all(headers_);
          headers_ = nullptr;
        }
      }

      void FormAdd(const std::string& name, const std::string& value)
      {
        curl_formadd(&post_, &last_, CURLFORM_COPYNAME, name.c_str(),
                     CURLFORM_COPYCONTENTS, value.c_str(), CURLFORM_END);
      }

      void Form()
      {
        SetOpt(CURLOPT_HTTPPOST, post_);
      }

      void ClearForm()
      {
        if (post_)
        {
          curl_formfree(post_);
          post_ = nullptr;
          last_ = nullptr;
        }
      }

      CURLcode Perform(long& code)
      {
        CURLcode status = curl_easy_perform(curl_);
        if (curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &code) != CURLE_OK)
        {
          code = -1;
        }
        
        return status;
      }

      static bool httpStatusOK(long status)
      {
        return (status >= 200) && (status < 300);
      }

      static bool httpClientError(long status)
      {
        return (status >= 400) && (status < 500);
      }

      const char *error() const { return error_buffer_; }

      static CURLcode GlobalInit(long flags = CURL_GLOBAL_DEFAULT)
      {
        return curl_global_init(flags);
      }

      static void GlobalCleanup()
      {
        curl_global_cleanup();
      }

    private:
      CURL *curl_;
      char error_buffer_[CURL_ERROR_SIZE];
      
      struct curl_slist *headers_;

      struct curl_httppost *post_;
      struct curl_httppost *last_;
    };
  }
}

#endif
