#if !defined(__WORDS_H__)
#define __WORDS_H__

typedef struct Word
{
    const char *word;
    void (*print)( const char * str );
} Word_t;

#define     WORD_SIZE   sizeof( Word_t )

void PrintStr( const char * str );

static const Word_t gWords[ ] = 
{
    {"Hello World", PrintStr},
    {"Good Morning", PrintStr},
    {"Good Evening", PrintStr},
    {"Welcome Home", PrintStr},
    {"Have a Nice Day", PrintStr},
    {"C Programming", PrintStr},
    {"Embedded Systems", PrintStr},
    {"System Startup", PrintStr},
    {"System Shutdown", PrintStr},
    {"Memory Allocation", PrintStr},
    {"Pointer Arithmetic", PrintStr},
    {"Function Callback", PrintStr},
    {"Data Structure", PrintStr},
    {"Linked List", PrintStr},
    {"Binary Tree", PrintStr},
    {"Hash Table", PrintStr},
    {"Stack Overflow", PrintStr},
    {"Queue Empty", PrintStr},
    {"Buffer Ready", PrintStr},
    {"Buffer Full", PrintStr},
    {"UART Initialized", PrintStr},
    {"SPI Transfer", PrintStr},
    {"I2C Bus Ready", PrintStr},
    {"ADC Conversion", PrintStr},
    {"DAC Output", PrintStr},
    {"Timer Started", PrintStr},
    {"Timer Expired", PrintStr},
    {"Interrupt Triggered", PrintStr},
    {"Task Created", PrintStr},
    {"Task Deleted", PrintStr},
    {"Scheduler Running", PrintStr},
    {"RTOS Kernel", PrintStr},
    {"Watchdog Reset", PrintStr},
    {"Low Power Mode", PrintStr},
    {"Sleep Mode", PrintStr},
    {"Wake Up Signal", PrintStr},
    {"Clock Configured", PrintStr},
    {"PLL Locked", PrintStr},
    {"GPIO High", PrintStr},
    {"GPIO Low", PrintStr},
    {"Button Pressed", PrintStr},
    {"Button Released", PrintStr},
    {"LED On", PrintStr},
    {"LED Off", PrintStr},
    {"Sensor Ready", PrintStr},
    {"Sensor Error", PrintStr},
    {"Calibration Done", PrintStr},
    {"Calibration Failed", PrintStr},
    {"Flash Write", PrintStr},
    {"Flash Read", PrintStr},
    {"EEPROM Access", PrintStr},
    {"Configuration Loaded", PrintStr},
    {"Configuration Saved", PrintStr},
    {"Network Connected", PrintStr},
    {"Network Disconnected", PrintStr},
    {"Packet Sent", PrintStr},
    {"Packet Received", PrintStr},
    {"Checksum Valid", PrintStr},
    {"Checksum Error", PrintStr},
    {"Authentication OK", PrintStr},
    {"Authentication Failed", PrintStr},
    {"Access Granted", PrintStr},
    {"Access Denied", PrintStr},
    {"File Opened", PrintStr},
    {"File Closed", PrintStr},
    {"File Not Found", PrintStr},
    {"Read Complete", PrintStr},
    {"Write Complete", PrintStr},
    {"Operation Started", PrintStr},
    {"Operation Finished", PrintStr},
    {"Operation Aborted", PrintStr},
    {"System Ready", PrintStr},
    {"System Error", PrintStr},
    {"Fatal Error", PrintStr},
    {"Recovery Mode", PrintStr},
    {"Update Available", PrintStr},
    {"Update Installed", PrintStr},
    {"Reboot Required", PrintStr},
    {"Rebooting Now", PrintStr},
    {"Hello Worlds", PrintStr},
    {"Final Message", PrintStr}
};

#define WORDS_COUNT ( sizeof(gWords)/sizeof(Word_t) )

#endif // __WORDS_H__
