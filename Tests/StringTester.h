#if !defined(__STRING_TESTER_H__)
#define __STRING_TESTER_H__

#include "String.h"
#include "TestUtils.h"
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

const char *sNames[] = 
{
"Aiden","Olivia","Liam","Emma","Noah","Ava","Ethan","Sophia","Mason","Isabella", "Logan","Mia","Lucas","Charlotte","Jackson","Amelia","Levi","Harper","Sebastian","Evelyn", "Mateo","Abigail","Jack","Emily","Owen","Elizabeth","Theodore","Sofia","Henry","Avery",
"Wyatt","Ella","Asher","Scarlett","Carter","Grace","Julian","Chloe","Grayson","Victoria", "Leo","Riley","Jayden","Aria","Gabriel","Lily","Isaac","Aubrey","Lincoln","Zoey", "Anthony","Penelope","Hudson","Layla","Dylan","Lillian","Ezra","Nora","Thomas","Hazel",
"Charles","Madison","Christopher","Ellie","Jaxon","Stella","Maverick","Paisley","Josiah","Audrey", "Isaiah","Skylar","Andrew","Violet","Elias","Claire","Joshua","Bella","Nathan","Aurora", "Caleb","Lucy","Ryan","Anna","Adrian","Samantha","Miles","Caroline","Eli","Genesis", "Nolan","Aaliyah","Christian","Kennedy","Aaron","Kinsley","Cameron","Allison","Ezekiel","Maya", "Colton","Sarah","Luca","Madelyn","Landon","Adeline","Hunter","Alexa","Jonathan","Ariana", "Santiago","Elena","Axel","Gabriella","Easton","Naomi","Cooper","Alice","Jeremiah","Sadie", "Angel","Hailey","Roman","Eva","Connor","Emilia","Jameson","Autumn","Robert","Quinn",
"Greyson","Nevaeh","Jordan","Piper","Ian","Ruby","Carson","Serenity","Jaxson","Willow", "Leonardo","Everly","Nicholas","Cora","Dominic","Kaylee","Austin","Lydia","Everett","Aubree", "Brooks","Arianna","Xavier","Eliza","Kai","Peyton","Jose","Melanie","Parker","Gianna", "Adam","Isabelle","Jace","Julia","Wesley","Valentina","Kayden","Nova","Silas","Clara", "Bennett","Vivian","Declan","Reagan","Waylon","Mackenzie","Weston","Madeline","Evan","Brielle", "Emmett","Delilah","Micah","Rylee","Ryder","Sloane","Beau","Remi","Damian","Callie", "Brayden","Margaret","Gael","Tessa","Rowan","Zara","Harrison","Camila","Bryson","Molly", "Sawyer","Laila","Amir","Ada","Kingston","Lola","Jason","June","Giovanni","Keira", "Vincent","Elise","Ayden","Juliette","Chase","Fiona","Myles","Olive","Diego","Georgia", "Nathaniel","Blake","Legend","Julio","Paxton","Zane","Maxwell","Archer","Atlas","Cohen"
};

#define NAMES_COUNT (sizeof(sNames)/sizeof(sNames[0]))

static String_t *gString = NULL;

static bool TestStringCreate();
static bool TestStringRelease();
static bool TestStringAppend();
static bool TestStringPrepend();
static bool TestStringClear();
static bool TestStringInsert();
static bool TestStringFind();
static bool TestStringCopyToBuffer();
static bool TestStringCopyToBufferAlloc();

bool RunTestsStringTester()
{
    bool res = false;

    INFO_MSG("Running String Tester...");

    if( TestStringCreate() )
    {
        if( TestStringAppend() )
        {
            if( TestStringFind() )
            {
                if( TestStringCopyToBuffer() )
                {
                    if( TestStringCopyToBufferAlloc() )
                    {
                        if( TestStringClear() )
                        {
                            if( TestStringPrepend() )
                            {
                                if( TestStringFind() )
                                {
                                    if( TestStringCopyToBuffer() )
                                    {
                                        if( TestStringCopyToBufferAlloc() )
                                        {
                                            if( TestStringClear() )
                                            {
                                                if( TestStringInsert() )
                                                {
                                                    if( TestStringFind() )
                                                    {
                                                        if( TestStringCopyToBuffer() )
                                                        {
                                                            if( TestStringCopyToBufferAlloc() )
                                                            {
                                                                if( TestStringClear() )
                                                                {
                                                                    if( TestStringRelease() )
                                                                    {
                                                                        res = true;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return res;
}

static bool TestStringCreate()
{
    bool res = false;

    INFO_MSG("Testing String create...");

    gString = StringCreate( "", 0 );

    if( gString )
    {
        if( gString->mLen == 0 )
        {
            if( gString->mBuffer )
            {
                res = true;
                PASS_MSG("Testing String create...Passed");
            }
            else
            {
                FAIL_MSG("Testing String create...Failed. Buffer not intialized");
            }
        }
        else
        {
            FAIL_MSG("Testing String create...Failed. String Length not initialized");
        }
    }
    else
    {
        FAIL_MSG("Testing String create...Failed. String object not initialized");
    }
    
    return res;
}

static bool TestStringRelease()
{
    bool res = false;

    INFO_MSG("Testing String Release...");

    if( gString )
    {
        StringRelease( gString );

        if( gString->mLen == 0 )
        {
            if( gString->mBuffer == NULL )
            {
                res = true;
                PASS_MSG("Testing String Release...Passed");
            }
        }
    }
    
    return res;
}
static bool TestStringAppend()
{
    bool res = true;
    char *name;
    int lastLen, len;
    INFO_MSG("Testing String Append...");

    for( int i = 0; i < NAMES_COUNT; i++ )
    {
        lastLen = gString->mLen;
        name = (char*) sNames[i];
        len = strlen(name);
        StringAppend( gString, name, len );

        if( gString->mLen != (len + lastLen) )
        {
            res = false;
            FAIL_MSG("Testing String Append...Failed on Append @ (%d - %s). Expected len %d; Actual len %d",
                i,
                name,
                (len + lastLen),
                gString->mLen
            );
            break;
        }
    }

    PASS_MSG("Testing String Append...Passed");
    
    return res;
}


static bool TestStringPrepend()
{
    bool res = true;
    char *name;
    int lastLen, len;
    INFO_MSG("Testing String Prepend...");

    for( int i = 0; i < NAMES_COUNT; i++ )
    {
        lastLen = gString->mLen;
        name = (char*) sNames[i];
        len = strlen(name);
        StringPrepend( gString, name, len );

        if( gString->mLen != (len + lastLen) )
        {
            res = false;
            FAIL_MSG("Testing String Prepend...Failed on Append @ (%d - %s). Expected len %d; Actual len %d",
                i,
                name,
                (len + lastLen),
                gString->mLen
            );
            break;
        }
    }

    PASS_MSG("Testing String Prepend...Passed");
    
    return res;
}

static bool TestStringClear()
{
    bool res = false;

    INFO_MSG("Testing String Clear...");

    StringClear( gString );

    if( gString->mLen == 0 )
    {
        if( gString->mBuffer )
        {
            res = true;
            PASS_MSG("Testing String Clear...Passed");
        }
        else
        {
            FAIL_MSG("Testing String Clear...Failed. Buffer not intialized");
        }
    }
    else
    {
        FAIL_MSG("Testing String Clear...Failed. String Length not initialized");
        }
    
    return res;
}

static bool TestStringInsert()
{
    bool res = true;
    char *name;
    int lastLen, len;
    INFO_MSG("Testing String Insert...");

    for( int i = 0; i < NAMES_COUNT; i++ )
    {
        lastLen = gString->mLen;
        name = (char*) sNames[i];
        len = strlen(name);
        StringInsert( gString, 0, name, len );

        if( gString->mLen != (len + lastLen) )
        {
            res = false;
            FAIL_MSG("Testing String Insert...Failed on Append @ (%d - %s). Expected len %d; Actual len %d",
                i,
                name,
                (len + lastLen),
                gString->mLen
            );
            break;
        }
    }

    PASS_MSG("Testing String Insert...Passed");
    
    return res;
}

static bool TestStringFind()
{
    bool res = true;
    int index;
    char *name;
    INFO_MSG("Testing String Find...");

    for( int i = 0; i < NAMES_COUNT; i++ )
    {
        name = (char*) sNames[i];

        if( (index = StringFind( gString, name, strlen(name) )) < 0 )
        {
            res = false;
            FAIL_MSG("Testing String Find...Failed on Find for %s", name );
            break;
        }
        // INFO_MSG("Testing String Find...Found %s @ %d", name, index );
    }

    PASS_MSG("Testing String Find...Passed");
    
    return res;
}

static bool TestStringCopyToBuffer()
{
    bool res = false;

    INFO_MSG("Testing String Copy to Buffer...");

    char testBuffer[1500];

    if( StringCopyToBuffer( gString, testBuffer, 1500 ) == gString->mLen )
    {
        if( StringFind( gString, testBuffer, gString->mLen ) == 0 )
        {
            res = true;
            PASS_MSG("Testing String Copy to Buffer...Passed");
        }
        else
        {
            FAIL_MSG("Testing String Copy to Buffer...Failed on Copy to buffer check");
        }
    }
    else
    {
        FAIL_MSG("Testing String Copy to Buffer...Failed on Copy to buffer operation");
    }
    
    return res;
}
static bool TestStringCopyToBufferAlloc()
{
    bool res = false;

    INFO_MSG("Testing String Copy to Buffer Alloc...");

    char *testBuffer;

    if( (testBuffer = StringCopyToBufferAlloc( gString ) ) )
    {
        if( StringFind( gString, testBuffer, gString->mLen ) == 0 )
        {
            res = true;
            PASS_MSG("Testing String Copy to Buffer Alloc...Passed");
        }
        else
        {
            FAIL_MSG("Testing String Copy to Buffer Alloc...Failed on Copy to buffer check");
        }
    }
    else
    {
        FAIL_MSG("Testing String Copy to Buffer Alloc...Failed on Copy to buffer operation");
    }
    
    return res;
}


#endif // __STRING_TESTER_H__
