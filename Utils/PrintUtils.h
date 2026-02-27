#if !defined(__PRINT_UTILS_H__)
#define __PRINT_UTILS_H__

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef enum Signal
{
    INFO,
    WARN,
    ERROR,
    SUCCESS
} Signal_t;

void ColorPrint(const Signal_t format, const char *msg, ...);

#define ERROR_MSG(msg, ...)                \
    ColorPrint(ERROR, msg, ##__VA_ARGS__);

#define ERROR_MSG_TERM(msg, ...)                \
    ColorPrint(ERROR, msg, ##__VA_ARGS__); \
    exit(-1)

#define WARN_MSG(msg, ...)                \
    ColorPrint(WARN, msg, ##__VA_ARGS__); 

#define INFO_MSG(msg, ...)                \
    ColorPrint(INFO, msg, ##__VA_ARGS__); 

#endif // __PRINT_UTILS_H__
