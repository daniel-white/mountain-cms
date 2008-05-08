//
// Mountain CMS
// Daniel A. White
//
// pb.cpp
// Builds the pages and caches them
// 

#include "pb.h"

void mtn_cms_page_builder::getpage( mtn_cms_http_response_data* response,
				    mtn_cms_http_request_data* request,
				    CppSQLite3DB* db,
				    std::string* content)
{
  _response = response;
  _request = request;
  _db = db;
}

std::string mtn_cms_page_builder::datestamp(const time_t& time)
{
  std::string ret = "<h1>Page last built at ";
  ret += mtn_cms_http_time_to_gmt_string(time);
  ret += "</h1>\n";
}

bool mtn_cms_page_builder::getcache(const std::string& page, mtn_cms_cache_item* cache_item)
{
}

void mtn_cms_page_builder::storecache(const std::string& page, mtn_cms_cache_item* cache_item)
{
}

std::string mtn_cms_page_builder::buildpage(std::string page);
