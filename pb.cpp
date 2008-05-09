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
  mtn_cms_cache_item cache;
  if (getcache(request->page, &cache))
    {
      time_t t = time(NULL);
      if ( t <= (cache.ttl + cache.created) )
	{
	  (*content) = cache.data;
	  response->status = MTN_CMS_HTTP_STATUS_OK;
	  response->length = cache.data.length();
	  response->content_type = MTN_CMS_MIME_TEXT_HTML;
	} 
    }
  
  if ( buildpage(request->page, *content))
    {
      response->status = MTN_CMS_HTTP_STATUS_OK;
      response->length = content->length();
      response->content_type = MTN_CMS_MIME_TEXT_HTML;
      return;
   }


  response->status = MTN_CMS_HTTP_STATUS_NOT_FOUND;
  return;
}

std::string mtn_cms_page_builder::datestamp(const time_t& time, int ttl)
{
  std::string ret = "<h1>Page last built at ";
  ret += mtn_cms_http_time_to_gmt_string(time);
  ret += " with a T.T.L. of ";
  ret += ttl;
  ret += "second(s) </h1>\n";
}

bool mtn_cms_page_builder::getcache(const std::string& page, mtn_cms_cache_item* cache_item)
{
  std::string _q = "SELECT * FROM `page_cache` WHERE page = \'" + page + "\'"; 
try
  {
  CppSQLite3Query q = _db->execQuery(_q.c_str());

  perror("hola");

  while (!q.eof())
    {
      int len;
      cache_item->data = q.getStringField("data");
      cache_item->created = q.getIntField("created");
      cache_item->ttl = q.getIntField("ttl");
      cache_item->valid = true;
      q.nextRow();
    } 
  }
 catch (CppSQLite3Exception ex)
   {
     cache_item->valid = false;
   }
 cache_item->data = "hello world";
  return !cache_item->valid;
}

void mtn_cms_page_builder::storecache(const std::string& page, mtn_cms_cache_item* cache_item)
{
  try
    {
    }
  catch (CppSQLite3Exception ex)
    {
    }

}

bool mtn_cms_page_builder::buildpage(std::string page, std::string& data)
{
  try
    {
      std::ostringstream s;
      std::string head, nav, content, stamp, foot;
     
      std::string _q;
 
      _q = "SELECT * FROM `pages` WHERE page = \'" + page + "\'";
      if ( _db->execQuery(_q.c_str()).eof() )
	return false;

      content = _db->execQuery(_q.c_str()).getStringField("data");

      _q = "SELECT * FROM `pages` WHERE page = \'Navigation\'";
      nav = _db->execQuery(_q.c_str()).getStringField("data");

      _q = "SELECT * FROM `pages` WHERE page = \'Header\'";
      head = _db->execQuery(_q.c_str()).getStringField("data");

      _q = "SELECT * FROM `pages` WHERE page = \'Footer\'";
      foot = _db->execQuery(_q.c_str()).getStringField("data");

      stamp = datestamp(time(NULL), 60);

      s << head << nav << content << stamp << foot;

      data = s.str();

      return true;
    }
  catch (CppSQLite3Exception ex)
    {
    }
  return false;
}
