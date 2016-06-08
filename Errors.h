#ifndef _AW_ERRORS_H_
#define _AW_ERRORS_H_

#include <sys/types.h>
//#include <errno.h>

namespace AwMirrorOp {

#ifdef _WIN32
typedef int	    status_t;
#else
typedef int32_t	    status_t;
#endif

#ifdef _WIN32
#undef NO_ERROR
#endif

enum {
    OK			= 0,
    NO_ERROR		= 0,

    UNKNOWN_ERROR	= 0x80000000,

    NO_MEMORY		= 0x80000001,
    INVALID_OPERATION	= 0x80000002,
    NO_INIT		= 0x80000003,
    TIMED_OUT		= 0x80000004,
    NOT_ENOUGH_DATA	= 0x80000005,
};

#ifdef _WIN32
#define NO_ERROR 0L
#endif

}; // namespace AwMirrorOp
#endif // _AW_ERRORS_H_
