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
    mtn_cms_start_listen(8080, 1);
    return 0;
}