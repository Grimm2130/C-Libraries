#include "PrintUtils.h"
#include <stdio.h>
#include <stdarg.h>

#define DEFAULT_BUFFER_SIZE 0x100

/// @brief Color Print
/// @param format Format for color print
/// @param msg Message
/// @param args
void ColorPrint( const Signal_t format, const char * msg, ... )
{
    static char buffer[DEFAULT_BUFFER_SIZE];
    buffer[0] = '\0';

    va_list arg;
    va_start( arg, msg );
    vsnprintf( buffer, DEFAULT_BUFFER_SIZE, msg, arg );
    va_end( arg );

    switch (format)
    {
    case INFO:
        printf( ANSI_COLOR_BLUE "%s%s\n", buffer, ANSI_COLOR_RESET );
    break;
    case WARN:
        printf( ANSI_COLOR_YELLOW "%s%s\n", buffer, ANSI_COLOR_RESET );
    break;
    case ERROR:
        printf( ANSI_COLOR_RED "%s%s\n", buffer, ANSI_COLOR_RESET );
    break;
    case SUCCESS:
        printf( ANSI_COLOR_GREEN "%s%s\n", buffer, ANSI_COLOR_RESET );
    break;
        
    default:
        printf( "%s\n", buffer );
        break;
    }
}
