#include <stdio.h>
#include <string.h>
// error codes
#define ERR_OK 0    // no error
#define ERR_EMPTY 1 // queue is empty
#define ERR_FULL 2  // queue is full

#define MAX_BUF 4             // maximum queue size
#define MAX_INDEX MAX_BUF - 1 // maximum index number

/*structure*/

static int err_code = ERR_EMPTY;
static char array[MAX_BUF];
static int start = 0; //current index for function shift
static int end = 0; //current index for function push
static int size = 0; // current queue size

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
    case ERR_EMPTY:
        printf("пустая очередь");
        break;
    case ERR_FULL:
        printf("полная очередь");
        break;
    case ERR_OK:
        printf("нет ошибок");
        break;
    default:
        printf("незнай чо за код ошибки");
        break;
    }
}


static void init() //set queue to default
{
    size = 0;
    start = 0;
    end = 0;
    set_error(ERR_OK);
}

static int getsize() //get queue size
{
    return size;
}

static int isfull() //check is queue full
{
    return size >= MAX_BUF;
}

static int isempty() //check is queue empty
{
    return size <= 0;
}

// calculate next index in array
static int next(int nCurrentIndex)
{
    return (nCurrentIndex < MAX_INDEX) ? ++nCurrentIndex : 0;
}

// adding an element to the queue
void push(char symbol)
{


    if (  isfull() )
    {
        set_error(ERR_FULL);
        printf("Очередь полна\n");
    }
     else 
    {

        array[end] = symbol;
        printf("end before push = %d\n", end);
        end = next(end);
        printf("end after push = %d\n", end);
        set_error(ERR_OK);
        size++;
        
    }
}

// removing the first element from the queue
char shift()
{
    char c = ' ';

    if (isempty())
    {
        set_error(ERR_EMPTY);
        printf("Очередь пуста\n");
    }
    else
    {
        char c = array[start];
        array[start] = 0;
        start = next(start);
        set_error(ERR_OK);
        printf("start = %d\n", start);
        size--;
    }

    return c;
}

// print array
void show ()
{
 for (int i = 0; i < MAX_BUF; i++)
        printf("%d ", array[i]);
}