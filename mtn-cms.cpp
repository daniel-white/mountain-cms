//
// Mountain CMS
// Daniel A. White
//
// mtn-cms.h
// The main program
//

#include "mtn-cms.h"

int main(int argc, char **argv)
{
	//std::cout << mtn_cms_http_status_to_string( mtn_cms_http_status_to_int("100000") );
	flush(std::cout);
    mtn_cms_start_listen(2700, 1);
    return 0;
}
