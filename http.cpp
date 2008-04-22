//
// Mountain CMS
// Daniel A. White
//
// http.cpp
// An HTTP server
//

#include "http.h"

#define HOSTNAME 512

void mtn_cms_http_worker(void *ptr)
{
    mtn_cms_worker_data *data = (mtn_cms_worker_data *)ptr;

    write(data->sock, "Hello, World\n", 20);
    close(data->sock);
}

void mtn_cms_start_listen(int portnum, int maxconn)
{
    sockaddr_in     saddr;
    hostent         *hp;
    char            hostname[HOSTNAME];
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
        fd = accept(sock, NULL, NULL);
        if (fd == -1)
            return ;
        mtn_cms_thread_data *td = new mtn_cms_thread_data();
        thread_data.push_back(td);
        td->data.sock = fd;
        pthread_create(&td->thread, NULL, mtn_cms_http_worker, (void *)&td->data);
        pthread_join(td->thread, NULL);
    }
    
    int size=thread_data.size();
    for (int i=0; i<size; i++)
    {
        delete thread_data[i];
    }
}
