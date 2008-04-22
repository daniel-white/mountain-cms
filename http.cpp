//
// Mountain CMS
// Daniel A. White
//
// http.cpp
// An HTTP server
//

#include "http.h"

#define HOSTNAME 512

void mtn_cms_http_worker(void *data)
{

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
    gethostname(hostname, HOSTNAME);
    hp = gethostbyname(hostname);
    
    bcopy( (void *)hp->h_addr, (void *)&saddress.sin_addr, hp->h_length);
    saddr.sin_port = htons(portnum);
    saddr.sin_famly = AF_INET;
    
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
    while (1)
    {
        int fd;
        fd = accept(sock, NULL, NULL);
        if (fd == -1)
            return ;
       std::cout << "I am connected to!\n";
    }
}
