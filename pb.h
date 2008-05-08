//
// Mountain CMS
// Daniel A. White
//  
// pb.h                                             
// Builds the pages and caches them
//

#ifndef PB_H
#define PB_H

#include "http.h"
#include "mtn-cms.h"

struct mtn_cms_http_response_data;
struct mtn_cms_http_request_data;

struct mtn_cms_cache_item
{
  std::string data;
  time_t created;
  int tol;
  bool valid;

  mtn_cms_cache_item() { created = 0; tol = 0; valid=false; }
};

class mtn_cms_page_builder
{
  void getpage( mtn_cms_http_response_data* response,
	        mtn_cms_http_request_data* request,
		CppSQLite3DB* db,
		std::string* content);
 private:
  CppSQLite3DB* _db;
  mtn_cms_http_response_data* _response;
  mtn_cms_http_request_data* _request;

  std::string datestamp(const time_t& time);
  bool getcache(const std::string& page, mtn_cms_cache_item* cache_item);
  void storecache(const std::string& page, mtn_cms_cache_item* cache_item);
  std::string buildpage(std::string page); 
};

#endif
