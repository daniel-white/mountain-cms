//
// Mountain CMS
// Daniel A. White
//
// http.cpp
// An HTTP server
//

#include "http.h"


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
/*
		// 400s
		case MTN_CMS_HTTP_STATUS_BAD_REQUEST                     400
		case MTN_CMS_HTTP_STATUS_UNAUTHORIZED                    401
		case MTN_CMS_HTTP_STATUS_PAYMENT_REQUIRED                402
		case MTN_CMS_HTTP_STATUS_FORBIDDEN                       403
		case MTN_CMS_HTTP_STATUS_NOT_FOUND                       404
		case MTN_CMS_HTTP_STATUS_METHOD_NOT_ALLOWED              405
		case MTN_CMS_HTTP_STATUS_NOT_ACCEPTABLE                  406
		case MTN_CMS_HTTP_STATUS_PROXY_AUTHENICATION_REQUIRED    407
		case MTN_CMS_HTTP_STATUS_REQUEST_TIME_OUT                408
		case MTN_CMS_HTTP_STATUS_CONFLICT                        409
		case MTN_CMS_HTTP_STATUS_GONE                            410
		case MTN_CMS_HTTP_STATUS_LENGTH_REQUIRED                 411
		case MTN_CMS_HTTP_STATUS_PRECONDITION_FAILED             412
		case MTN_CMS_HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE        413
		case MTN_CMS_HTTP_STATUS_REQUEST_URI_TOO_LARGE           414
		case MTN_CMS_HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE          415
		case MTN_CMS_HTTP_STATUS_REQUEST_RANGE_NOT_SATISFIABLE   416
		case MTN_CMS_HTTP_STATUS_EXPECTATION_FAILED              417
		*/

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
		
		default:
			return "";
	}
}

void* mtn_cms_http_worker(void *ptr)
{
    mtn_cms_worker_data *data = (mtn_cms_worker_data *)ptr;



    write(data->sock, "Hello, World\n", 20);
    close(data->sock);
}

void mtn_cms_start_listen(int portnum, int maxconn)
{
    sockaddr_in     saddr;
    hostent         *hp;
    int             sock;
 
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Mountain CMS - Unable to open socket.");
        return;
    }
 
    bzero((void *)&saddr, sizeof(saddr));
    
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(portnum);
    saddr.sin_family = AF_INET;
    
    if ( bind(sock, (sockaddr *)&saddr, sizeof(saddr)) )
    {
        perror("Mountain CMS - Unable to bind socket.");
        return;
    }

    if ( listen(sock, maxconn) )
    {
        perror("Mountain CMS - Unable to listen on socket.");
        return;
    }
    
    std::vector<mtn_cms_thread_data*> thread_data;
    while (1)
    {
        int fd;
        sockaddr addr; 
        socklen_t addrlen;
        fd = accept(sock, &addr, &addrlen);
        if (fd == -1)
            return ;

        mtn_cms_thread_data *td = new mtn_cms_thread_data();
        thread_data.push_back(td);

        td->data.sock = fd;
        td->data.addr = addr;
        td->data.addrlen = fd;


        pthread_create(&td->thread, NULL, mtn_cms_http_worker, (void *)&td->data);
        pthread_join(td->thread, NULL);
    }
    
    int size=thread_data.size();
    for (int i=0; i<size; i++)
    {
        delete thread_data[i];
    }
}
