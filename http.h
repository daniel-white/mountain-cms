//
// Mountain CMS
// Daniel A. White
//
// http.h
// Stores the HTTP constants

#ifndef HTTP_H
#define HTTP_H

// Methods

#define MTN_CMS_HTTP_METHOD_DELETE                          "DELETE
#define MTN_CMS_HTTP_METHOD_GET                             "GET"
#define MTN_CMS_HTTP_METHOD_HEAD                            "HEAD"
#define MTN_CMS_HTTP_METHOD_OPTIONS                         "OPTIONS"
#define MTN_CMS_HTTP_METHOD_POST                            "POST"
#define MTN_CMS_HTTP_METHOD_PUT                             "PUT"

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

#define MTN_CMS_HTTP_STATUS_INTERNAL_SERVER_ERRROR          500
#define MTN_CMS_HTTP_STATUS_NOT_IMPLEMENTED                 501
#define MTN_CMS_HTTP_STATUS_BAD_GATEWAY                     502
#define MTN_CMS_HTTP_STATUS_SERVICE_UNAVAILABLE             503
#define MTN_CMS_HTTP_STATUS_GATEWAY_TIME_OUT                504
#define MTN_CMS_HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED      505

#endif
