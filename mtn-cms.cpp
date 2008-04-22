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
	std::cout << mtn_cms_http_status_to_string(500);
	flush(std::cout);
    mtn_cms_start_listen(27000, 1);
    return 0;
}
