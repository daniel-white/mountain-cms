//
// Mountain CMS
// Daniel A. White
//
// http.h
// Stores the HTTP constants
//

#ifndef HTTP_H
#define HTTP_H

#include "mtn-cms.h"
#include "sqlite/CppSQLite3.h"

// Mountain CMS HTTP server defines
#define MTN_CMS_HTTP_SERVER_NAME_S                           "Mountain CMS"
#define MTN_CMS_HTTP_SERVER_VERSION_S                        "EarlyAlpha"
#define MTN_CMS_HTTP_SERVER_DEFAULT_PORT                     80

// HTTP versions
#define MTN_CMS_HTTP_VERSION_1_0_S                          "HTTP/1.0"
#define MTN_CMS_HTTP_VERSION_1_1_S                          "HTTP/1.1"

// methods

#define MTN_CMS_HTTP_METHOD_CONNECT_S                       "CONNECT"
#define MTN_CMS_HTTP_METHOD_DELETE_S                        "DELETE"
#define MTN_CMS_HTTP_METHOD_GET_S                           "GET"
#define MTN_CMS_HTTP_METHOD_HEAD_S                          "HEAD"
#define MTN_CMS_HTTP_METHOD_OPTIONS_S                       "OPTIONS"
#define MTN_CMS_HTTP_METHOD_POST_S                          "POST"
#define MTN_CMS_HTTP_METHOD_PUT_S                           "PUT"
#define MTN_CMS_HTTP_METHOD_TRACE_S                         "TRACE"

#define MTN_CMS_HTTP_METHOD_CONNECT                         0
#define MTN_CMS_HTTP_METHOD_DELETE                          1
#define MTN_CMS_HTTP_METHOD_GET                             2
#define MTN_CMS_HTTP_METHOD_HEAD                            3
#define MTN_CMS_HTTP_METHOD_OPTIONS                         4
#define MTN_CMS_HTTP_METHOD_POST                            5
#define MTN_CMS_HTTP_METHOD_PUT                             6
#define MTN_CMS_HTTP_METHOD_TRACE                           7

// status codes as numbers

#define MTN_CMS_HTTP_STATUS_CONTINUE                        100
#define MTN_CMS_HTTP_STATUS_SWITCHING_PROTOCOLS             101

#define MTN_CMS_HTTP_STATUS_OK                              200
#define MTN_CMS_HTTP_STATUS_CREATED                         201
#define MTN_CMS_HTTP_STATUS_ACCEPTED                        202
#define MTN_CMS_HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION   203
#define MTN_CMS_HTTP_STATUS_NO_CONTENT                      204
#define MTN_CMS_HTTP_STATUS_RESET_CONTENT                   205
#define MTN_CMS_HTTP_STATUS_PARTIAL_CONTENT                 206

#define MTN_CMS_HTTP_STATUS_MULTIPLE_CHOICES                300
#define MTN_CMS_HTTP_STATUS_MOVED_PERMANENTLY               301
#define MTN_CMS_HTTP_STATUS_FOUND                           302
#define MTN_CMS_HTTP_STATUS_SEE_OTHER                       303
#define MTN_CMS_HTTP_STATUS_NOT_MODIFIED                    304
#define MTN_CMS_HTTP_STATUS_USE_PROXY                       305
#define MTN_CMS_HTTP_STATUS_TEMPORARY_REDIRECT              307

#define MTN_CMS_HTTP_STATUS_BAD_REQUEST                     400
#define MTN_CMS_HTTP_STATUS_UNAUTHORIZED                    401
#define MTN_CMS_HTTP_STATUS_PAYMENT_REQUIRED                402
#define MTN_CMS_HTTP_STATUS_FORBIDDEN                       403
#define MTN_CMS_HTTP_STATUS_NOT_FOUND                       404
#define MTN_CMS_HTTP_STATUS_METHOD_NOT_ALLOWED              405
#define MTN_CMS_HTTP_STATUS_NOT_ACCEPTABLE                  406
#define MTN_CMS_HTTP_STATUS_PROXY_AUTHENICATION_REQUIRED    407
#define MTN_CMS_HTTP_STATUS_REQUEST_TIME_OUT                408
#define MTN_CMS_HTTP_STATUS_CONFLICT                        409
#define MTN_CMS_HTTP_STATUS_GONE                            410
#define MTN_CMS_HTTP_STATUS_LENGTH_REQUIRED                 411
#define MTN_CMS_HTTP_STATUS_PRECONDITION_FAILED             412
#define MTN_CMS_HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE        413
#define MTN_CMS_HTTP_STATUS_REQUEST_URI_TOO_LARGE           414
#define MTN_CMS_HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE          415
#define MTN_CMS_HTTP_STATUS_REQUEST_RANGE_NOT_SATISFIABLE   416
#define MTN_CMS_HTTP_STATUS_EXPECTATION_FAILED              417

#define MTN_CMS_HTTP_STATUS_INTERNAL_SERVER_ERROR           500
#define MTN_CMS_HTTP_STATUS_NOT_IMPLEMENTED                 501
#define MTN_CMS_HTTP_STATUS_BAD_GATEWAY                     502
#define MTN_CMS_HTTP_STATUS_SERVICE_UNAVAILABLE             503
#define MTN_CMS_HTTP_STATUS_GATEWAY_TIME_OUT                504
#define MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED      505

#define MTN_CMS_HTTP_MIN_STATUS								MTN_CMS_HTTP_STATUS_CONTINUE 
#define MTN_CMS_HTTP_MAX_STATUS								MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED

// status codes as strings

#define MTN_CMS_HTTP_STATUS_CONTINUE_S                      "100 Continue"
#define MTN_CMS_HTTP_STATUS_SWITCHING_PROTOCOLS_S           "101 Switching Protocols"

#define MTN_CMS_HTTP_STATUS_OK_S                            "200 OK"
#define MTN_CMS_HTTP_STATUS_CREATED_S                       "201 Created"
#define MTN_CMS_HTTP_STATUS_ACCEPTED_S                      "202 Accepted"
#define MTN_CMS_HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION_S "203 Non-Authoritative Information"
#define MTN_CMS_HTTP_STATUS_NO_CONTENT_S                    "204 No Content"
#define MTN_CMS_HTTP_STATUS_RESET_CONTENT_S                 "205 Reset Content"
#define MTN_CMS_HTTP_STATUS_PARTIAL_CONTENT_S               "206 Partial Content"

#define MTN_CMS_HTTP_STATUS_MULTIPLE_CHOICES_S              "300 Multiple Choices"
#define MTN_CMS_HTTP_STATUS_MOVED_PERMANENTLY_S             "301 Moved Permanently"
#define MTN_CMS_HTTP_STATUS_FOUND_S                         "302 Found"
#define MTN_CMS_HTTP_STATUS_SEE_OTHER_S                     "303 See Other"
#define MTN_CMS_HTTP_STATUS_NOT_MODIFIED_S                  "304 Use Modified"
#define MTN_CMS_HTTP_STATUS_USE_PROXY_S                     "305 Use Proxy"
#define MTN_CMS_HTTP_STATUS_TEMPORARY_REDIRECT_S            "307 Temporary Redirect"

#define MTN_CMS_HTTP_STATUS_BAD_REQUEST_S                   "400 Bad Request"
#define MTN_CMS_HTTP_STATUS_UNAUTHORIZED_S                  "401 Unauthorized"
#define MTN_CMS_HTTP_STATUS_PAYMENT_REQUIRED_S              "402 Payment Required"
#define MTN_CMS_HTTP_STATUS_FORBIDDEN_S                     "403 Forbidden"
#define MTN_CMS_HTTP_STATUS_NOT_FOUND_S                     "404 Not Found"
#define MTN_CMS_HTTP_STATUS_METHOD_NOT_ALLOWED_S            "405 Not Allowed"
#define MTN_CMS_HTTP_STATUS_NOT_ACCEPTABLE_S                "406 Not Acceptable"
#define MTN_CMS_HTTP_STATUS_PROXY_AUTHENICATION_REQUIRED_S  "407 Authenication Required"
#define MTN_CMS_HTTP_STATUS_REQUEST_TIME_OUT_S              "408 Request Time-out"
#define MTN_CMS_HTTP_STATUS_CONFLICT_S                      "409 Conflict"
#define MTN_CMS_HTTP_STATUS_GONE_S                          "410 Gone"
#define MTN_CMS_HTTP_STATUS_LENGTH_REQUIRED_S               "411 Length Required"
#define MTN_CMS_HTTP_STATUS_PRECONDITION_FAILED_S           "412 Precondition Required"
#define MTN_CMS_HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE_S      "413 Request Enity Too Large"
#define MTN_CMS_HTTP_STATUS_REQUEST_URI_TOO_LARGE_S         "414 Request-URI Too Large"
#define MTN_CMS_HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE_S        "415 Unsupported Media Type"
#define MTN_CMS_HTTP_STATUS_REQUEST_RANGE_NOT_SATISFIABLE_S "416 Requested range not satisfiable"
#define MTN_CMS_HTTP_STATUS_EXPECTATION_FAILED_S            "417 Expectation Failed"

#define MTN_CMS_HTTP_STATUS_INTERNAL_SERVER_ERROR_S         "500 Internal Server Error"
#define MTN_CMS_HTTP_STATUS_NOT_IMPLEMENTED_S               "501 Not Implemented"
#define MTN_CMS_HTTP_STATUS_BAD_GATEWAY_S                   "502 Bad Gateway"
#define MTN_CMS_HTTP_STATUS_SERVICE_UNAVAILABLE_S           "503 Service Unavailable"
#define MTN_CMS_HTTP_STATUS_GATEWAY_TIME_OUT_S              "504 Gateway Time-out"
#define MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED_S    "505 HTTP Version not supported"

struct mtn_cms_worker_data
{
    int sock;
    sockaddr addr; 
    socklen_t addrlen;
};

struct mtn_cms_http_request_data
{
  std::string page;
  int method;
  std::string http;
};

struct mtn_cms_http_response_data
{

    std::string content_type;
    std::string content_encoding;
    unsigned int length;
    int status;

  mtn_cms_http_response_data() { length = 0; status = 0; }
};

struct mtn_cms_thread_data
{
    mtn_cms_worker_data data;
    pthread_t thread;
};

// HTTP server functions
void* mtn_cms_http_worker(void *data);
void mtn_cms_start_listen(int port, int maxconn, CppSQLite3DB& db);
void mtn_cms_read_header(int sock, mtn_cms_http_request_data& request);


// data manipulation
std::string mtn_cms_http_status_to_string(int sc);
int mtn_cms_http_status_to_int(const char *status);
std::string mtn_cms_http_time_to_gmt_string(const time_t& t);

// Header manipulation
std::string mtn_cms_http_make_response(const mtn_cms_http_response_data& data);

#endif
