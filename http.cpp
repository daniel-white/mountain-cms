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
    std::string response;

    response = MTN_CMS_HTTP_VERSION_1_1_S;
    response += " " + mtn_cms_http_status_to_string(data.status) + '\n';
    response += "Date: 0 " + '\n';
    response += "Server: " + MTN_CMS_HTTP_SERVER_NAME_S + '\n';

    return response;
}

void* mtn_cms_http_worker(void *ptr)
{
    mtn_cms_worker_data *data = (mtn_cms_worker_data *)ptr;
	char buf[5] = { '\0' };
	while ( read(data->sock, buf, 5) > 0)
	{
        mtn_cms_http_response_data rdata;
        std::string res;
        rdata.status = buf;

        res = mtn_cms_http_make_response(rdata);

        write(data->sock, res.data(), res.length());

		int sc = mtn_cms_http_status_to_int(buf);
		std::string status(mtn_cms_http_status_to_string(sc));
		status += '\n';
		std::cout << status;
		flush(std::cout);
		
		//write(data->sock, status.data(), status.length());
	}
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
        perror("Mountain CMS - Unable to open socket");
        return;
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
