//
// Mountain CMS
// Daniel A. White
//
// http.cpp
// An HTTP server
//

#include "http.h"

CppSQLite3DB* mymtn;

std::string mtn_cms_http_time_to_gmt_string(const time_t& t)
{
  std::ostringstream s;
  tm time;
  gmtime_r(&t, &time);

  switch (time.tm_wday)
  {
    case 0: s << "Sun, "; break;
    case 1: s << "Mon, "; break;
    case 2: s << "Tue, "; break;
    case 3: s << "Wed, "; break;
    case 4: s << "Thu, "; break;
    case 5: s << "Fri, "; break;
    case 6: s << "Sat, ";
  }
  
  if (time.tm_mday < 10)
    s << "0" << time.tm_mday;
  else
    s << time.tm_mday;

  switch (time.tm_mon)
  {
    case 0: s << " Jan "; break;
    case 1: s << " Feb "; break;
    case 2: s << " Mar "; break;
    case 3: s << " Apr "; break;
    case 4: s << " May "; break;
    case 5: s << " Jun "; break;
    case 6: s << " Jul "; break;
    case 7: s << " Aug "; break;
    case 8: s << " Sep "; break;
    case 9: s << " Oct "; break;
    case 10: s << " Nov "; break;
    case 11: s << " Dec ";
  }
  
  s << time.tm_year + 1900 << " ";

  if (time.tm_hour < 10)
    s << "0" << time.tm_hour << ":";
  else
    s << time.tm_hour << ":";

  if (time.tm_min < 10)
    s << "0" << time.tm_min << ":";
  else
    s << time.tm_min << ":";

  if (time.tm_sec < 10)
    s << "0" << time.tm_sec << " GMT";
  else
    s << time.tm_sec << " GMT";


  return s.str();
}

std::string mtn_cms_http_status_to_string(int sc)
{
	switch (sc)
	{
		// 100s
		case MTN_CMS_HTTP_STATUS_CONTINUE:
			return MTN_CMS_HTTP_STATUS_CONTINUE_S;
		case MTN_CMS_HTTP_STATUS_SWITCHING_PROTOCOLS:
			return MTN_CMS_HTTP_STATUS_SWITCHING_PROTOCOLS_S;

		// 200s
		case MTN_CMS_HTTP_STATUS_OK:
			return MTN_CMS_HTTP_STATUS_OK_S;
		case MTN_CMS_HTTP_STATUS_CREATED:
			return MTN_CMS_HTTP_STATUS_CREATED_S;
		case MTN_CMS_HTTP_STATUS_ACCEPTED:
			return MTN_CMS_HTTP_STATUS_ACCEPTED_S;
		case MTN_CMS_HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION:
			return MTN_CMS_HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION_S;
		case MTN_CMS_HTTP_STATUS_NO_CONTENT:
			return MTN_CMS_HTTP_STATUS_NO_CONTENT_S;
		case MTN_CMS_HTTP_STATUS_RESET_CONTENT:
			return MTN_CMS_HTTP_STATUS_RESET_CONTENT_S;
		case MTN_CMS_HTTP_STATUS_PARTIAL_CONTENT:
			return MTN_CMS_HTTP_STATUS_PARTIAL_CONTENT_S;

		// 300s
		case MTN_CMS_HTTP_STATUS_MULTIPLE_CHOICES:
			return MTN_CMS_HTTP_STATUS_MULTIPLE_CHOICES_S;
		case MTN_CMS_HTTP_STATUS_MOVED_PERMANENTLY:
			return MTN_CMS_HTTP_STATUS_MOVED_PERMANENTLY_S;
		case MTN_CMS_HTTP_STATUS_FOUND:
			return MTN_CMS_HTTP_STATUS_FOUND_S;
		case MTN_CMS_HTTP_STATUS_SEE_OTHER:
			return MTN_CMS_HTTP_STATUS_SEE_OTHER_S;
		case MTN_CMS_HTTP_STATUS_NOT_MODIFIED:
			return MTN_CMS_HTTP_STATUS_NOT_MODIFIED_S;
		case MTN_CMS_HTTP_STATUS_USE_PROXY:
			return MTN_CMS_HTTP_STATUS_USE_PROXY_S;
		case MTN_CMS_HTTP_STATUS_TEMPORARY_REDIRECT:
			return MTN_CMS_HTTP_STATUS_TEMPORARY_REDIRECT_S;

		// 400s
		case MTN_CMS_HTTP_STATUS_BAD_REQUEST:
			return MTN_CMS_HTTP_STATUS_BAD_REQUEST_S;
		case MTN_CMS_HTTP_STATUS_UNAUTHORIZED:
			return MTN_CMS_HTTP_STATUS_UNAUTHORIZED_S;
		case MTN_CMS_HTTP_STATUS_PAYMENT_REQUIRED:
			return MTN_CMS_HTTP_STATUS_PAYMENT_REQUIRED_S;
		case MTN_CMS_HTTP_STATUS_FORBIDDEN:
			return MTN_CMS_HTTP_STATUS_FORBIDDEN_S;
		case MTN_CMS_HTTP_STATUS_NOT_FOUND:
			return MTN_CMS_HTTP_STATUS_NOT_FOUND_S;
		case MTN_CMS_HTTP_STATUS_METHOD_NOT_ALLOWED:
			return MTN_CMS_HTTP_STATUS_METHOD_NOT_ALLOWED_S;
		case MTN_CMS_HTTP_STATUS_NOT_ACCEPTABLE:
			return MTN_CMS_HTTP_STATUS_NOT_ACCEPTABLE_S;
		case MTN_CMS_HTTP_STATUS_PROXY_AUTHENICATION_REQUIRED:
			return MTN_CMS_HTTP_STATUS_PROXY_AUTHENICATION_REQUIRED_S;
		case MTN_CMS_HTTP_STATUS_REQUEST_TIME_OUT:
			return MTN_CMS_HTTP_STATUS_REQUEST_TIME_OUT_S;
		case MTN_CMS_HTTP_STATUS_CONFLICT:
			return MTN_CMS_HTTP_STATUS_CONFLICT_S;
		case MTN_CMS_HTTP_STATUS_GONE:
			return MTN_CMS_HTTP_STATUS_GONE_S;
		case MTN_CMS_HTTP_STATUS_LENGTH_REQUIRED:
			return MTN_CMS_HTTP_STATUS_LENGTH_REQUIRED_S;
		case MTN_CMS_HTTP_STATUS_PRECONDITION_FAILED:
			return MTN_CMS_HTTP_STATUS_PRECONDITION_FAILED_S;
		case MTN_CMS_HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE:
			return MTN_CMS_HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE_S;
		case MTN_CMS_HTTP_STATUS_REQUEST_URI_TOO_LARGE:
			return MTN_CMS_HTTP_STATUS_REQUEST_URI_TOO_LARGE_S;
		case MTN_CMS_HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE:
			return MTN_CMS_HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE_S;
		case MTN_CMS_HTTP_STATUS_REQUEST_RANGE_NOT_SATISFIABLE:
			return MTN_CMS_HTTP_STATUS_REQUEST_RANGE_NOT_SATISFIABLE_S;
		case MTN_CMS_HTTP_STATUS_EXPECTATION_FAILED:
			return MTN_CMS_HTTP_STATUS_EXPECTATION_FAILED_S;

		// 500s
		case MTN_CMS_HTTP_STATUS_INTERNAL_SERVER_ERROR:
			return MTN_CMS_HTTP_STATUS_INTERNAL_SERVER_ERROR_S;
		case MTN_CMS_HTTP_STATUS_NOT_IMPLEMENTED:
			return MTN_CMS_HTTP_STATUS_NOT_IMPLEMENTED_S;
		case MTN_CMS_HTTP_STATUS_BAD_GATEWAY:
			return MTN_CMS_HTTP_STATUS_BAD_GATEWAY_S;
		case MTN_CMS_HTTP_STATUS_SERVICE_UNAVAILABLE:
			return MTN_CMS_HTTP_STATUS_SERVICE_UNAVAILABLE_S;
		case MTN_CMS_HTTP_STATUS_GATEWAY_TIME_OUT:
			return MTN_CMS_HTTP_STATUS_GATEWAY_TIME_OUT_S;
		case MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED:
			return MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED_S;
		
		break;
		// Otherwise...
		default:
			return MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED_S;
	}
}

int mtn_cms_http_status_to_int(const char *status)
{
	char *end_ptr = NULL;
	int ret = (int) strtol(status, &end_ptr, 0);

	if ( (ret <= MTN_CMS_HTTP_MAX_STATUS) && (ret >= MTN_CMS_HTTP_MIN_STATUS) )
		return ret;
	else
		return MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED;
}

std::string mtn_cms_http_make_response(const mtn_cms_http_response_data& data)
{
    std::ostringstream response;


    //The status line 
    response << MTN_CMS_HTTP_VERSION_1_1_S;
    response << " " << mtn_cms_http_status_to_string(data.status) << "\n";


    //The date and time
    time_t t = time(NULL);
    response << "Date: " << mtn_cms_http_time_to_gmt_string(t) << "\n";

    response << "Server: " << MTN_CMS_HTTP_SERVER_NAME_S << "\n";

    if (data.length)
      response << "Length: " << data.length << "\n";

    if (data.content_type.length())
      response << "Content-Type: " << data.content_type << "\n";

    if (data.content_encoding.length())
      response << "Content-Encoding: " << data.content_encoding << "\n\n\n";

    return response.str();
}


void* mtn_cms_http_worker(void *ptr)
{
 
    mtn_cms_worker_data *data = (mtn_cms_worker_data *)ptr;
    mtn_cms_http_request_data request;
    mtn_cms_http_response_data response;
    mtn_cms_read_header(data->sock, request);
    mtn_cms_page_builder pb;
    std::string content = "mycontent";
    bool validcontent=false;
    mymtn->open("./test.mtn");
    switch(request.method)
    {
    case MTN_CMS_HTTP_METHOD_GET:
      pb.getpage(&response, &request, mymtn, &content);
      validcontent=true;
      break;
    default:
      response.status = MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED;
      break;
    }
    
    //    response.status = 404;
    std::string response_s = mtn_cms_http_make_response(response);

    write(data->sock, response_s.data(), response_s.length());
    if(validcontent)
      write(data->sock, content.data(), content.length());
	
    close(data->sock);
}

void mtn_cms_read_header(int sock, mtn_cms_http_request_data& request)
{
  char header[535] = { '\0' };
  int bytes = read(sock, header, 535);
  
  char method[11] = { '\0' };
  char page[513] = { '\0' };
  char http[11] = { '\0' };

  
  sscanf(header, "%10s %512s %10s", method, page, http);


  if (strcmp(method, MTN_CMS_HTTP_METHOD_CONNECT_S) == 0 )
    request.method = MTN_CMS_HTTP_METHOD_CONNECT;
  else if (strcmp(method, MTN_CMS_HTTP_METHOD_DELETE_S) == 0 )
    request.method = MTN_CMS_HTTP_METHOD_DELETE;
  else if (strcmp(method, MTN_CMS_HTTP_METHOD_GET_S) == 0 )
    request.method = MTN_CMS_HTTP_METHOD_GET;
  else if (strcmp(method, MTN_CMS_HTTP_METHOD_HEAD_S) == 0 )
    request.method = MTN_CMS_HTTP_METHOD_HEAD;
  else if (strcmp(method, MTN_CMS_HTTP_METHOD_OPTIONS_S) == 0 )
    request.method = MTN_CMS_HTTP_METHOD_OPTIONS;
  else if (strcmp(method, MTN_CMS_HTTP_METHOD_POST_S) == 0 )
    request.method = MTN_CMS_HTTP_METHOD_POST;
  else if (strcmp(method, MTN_CMS_HTTP_METHOD_PUT_S) == 0 )
    request.method = MTN_CMS_HTTP_METHOD_PUT;
  else if (strcmp(method, MTN_CMS_HTTP_METHOD_TRACE_S) == 0 )
    request.method = MTN_CMS_HTTP_METHOD_CONNECT;
  else
    request.method = -1;

  request.page = page;
  request.http = http;

}

void mtn_cms_start_listen(int portnum, int maxconn, CppSQLite3DB& db)
{
  mymtn = &db;
  int yes=1;
    sockaddr_in     saddr;
    hostent         *hp;
    int             sock;
 
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Mountain CMS - Unable to open socket");
        return;
    }

     if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)))
      {
	perror("Mountain CMS - Unable to set socket option");
	exit(-1);
      } 

 
    bzero((void *)&saddr, sizeof(saddr));
    
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(portnum);
    saddr.sin_family = AF_INET;
    
    if ( bind(sock, (sockaddr *)&saddr, sizeof(saddr)) )
    {
        perror("Mountain CMS - Unable to bind socket");
        return;
    }


    if ( listen(sock, maxconn) )
    {
        perror("Mountain CMS - Unable to listen on socket");
        return;
    }
    
    std::vector<mtn_cms_thread_data*> thread_data;
    while (1)
    {
      
        int fd;
        sockaddr addr; 
        socklen_t addrlen = sizeof(sockaddr);
        fd = accept(sock, &addr, &addrlen);

        if (fd != -1)
	{
	  

          mtn_cms_thread_data *td = new mtn_cms_thread_data();
          thread_data.push_back(td);

          td->data.sock = fd;
          td->data.addr = addr;
          td->data.addrlen = addrlen;

          pthread_create(&td->thread, NULL, mtn_cms_http_worker, (void *)&td->data);
          pthread_join(td->thread, NULL);
	 
	}
    }
    
    int size=thread_data.size();
    for (int i=0; i<size; i++)
    {
        delete thread_data[i];
    }
}
