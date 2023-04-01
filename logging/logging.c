#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#define LOG_ERR 1      // error
#define LOG_DBG 2      // debag
#define LOG_INFO 3     // message
#define ERR_OK 0       // no error
#define ERR_OPENING 11 // Error occured while opening file
#define ERR_WRITE 12   // Error occured while write file
#define ERR_SAVE 13    // Error occured while save file

static int err_code = ERR_OK;
static int err_level = LOG_ERR;
int nConfigLogLevel = LOG_ERR;

/*functions*/

// getting an error
static int get_error()
{
    return err_code;
}

// assigning an error code to the variable 'ec'
static void set_error(int ec)
{
    err_code = ec;
}

// error message output
static void err_str(int err_code)
{

    switch (err_code)
    {
        // log errors
    case ERR_OPENING:
        printf("Error occured while opening file\n");
        break;
    case ERR_WRITE:
        printf("Error occured while write file\n");
        break;
    case ERR_SAVE:
        printf("Error occured while save file\n");
        break;
    case ERR_OK:
        printf("no error\n");
        break;
    default:
        printf("незнай чо за код ошибки\n");
        break;
    }
}

static char *stamp_time()
{
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);
    time_str[strlen(time_str) - 1] = '\0';
    return time_str;
}

void write_log(char *message)
{
    assert(message);
    char *filename = "log.txt";
    FILE *fp = fopen(filename, "a");
    if (fp)
    {
        fputs(message, fp);
        fclose(fp);
        printf("File has been written\n");
    }
    else
    {
        set_error(ERR_OPENING);
        err_str(err_code);
    }
}

void LOGERROR(char *logmsg)
{
    assert(logmsg);
    if (nConfigLogLevel == LOG_ERR)
    {

        char *error_time = stamp_time();

        if (NULL == error_time)
        {
            exit(1);
        }
        char msg[sizeof(error_time) + 200];
        snprintf(msg, sizeof(msg), "Error %s: %s\n", error_time, logmsg);
        write_log(msg);
    }
}

void LOGDEBUG(char *logmsg)
{
    assert(logmsg);
    if (nConfigLogLevel == LOG_DBG)
    {
        char *error_time = stamp_time();

        if (NULL == error_time)
        {
            exit(1);
        }
        char msg[sizeof(error_time) + 200];
        snprintf(msg, sizeof(msg), "Debug %s: %s\n", error_time, logmsg);
        write_log(msg);
    }
}

void LOGINFO(char *logmsg)
{
    assert(logmsg);
    char *error_time = stamp_time();
    if (NULL == error_time)
    {
        exit(1);
    }
    char msg[sizeof(error_time) + 200];
    snprintf(msg, sizeof(msg), "Info %s: %s\n", error_time, logmsg);
    write_log(msg);
}
