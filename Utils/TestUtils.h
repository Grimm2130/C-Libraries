#if !defined(__TEST_UTILS_H__)
#define __TEST_UTILS_H__

#include "PrintUtils.h"

#define PASS_MSG( msg, ... )    \
    ColorPrint( SUCCESS, msg, ##__VA_ARGS__ )

#define FAIL_MSG( msg, ... )                \
    ColorPrint( ERROR, msg, ##__VA_ARGS__ ) 

#endif // __TEST_UTILS_H__
