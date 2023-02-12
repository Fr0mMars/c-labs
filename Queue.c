#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// error codes
#define ERR_OK 0    // no error
#define ERR_EMPTY 1 // queue is empty
#define ERR_FULL 2  // queue is full

#define MAX_BUF 4 // maximum queue size

/*structure*/

int err_code = ERR_EMPTY;
char array[MAX_BUF];
int start = 0, end = 0;
bool flag = false;

/*functions*/

// getting an error
int get_error()
{
  return err_code;
}

// assigning an error code to the variable 'ec'
void set_error(int ec)
{
  err_code = ec;
}

// error message output
void err_str(int err_code)
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

// adding an element to the queue
void push(char symbol)
{
  if (end = MAX_BUF && start > 0)
  {
    flag = true;
  }

      if (flag == false)
    {
      if (end < (MAX_BUF))
      {
        array[end] = symbol;
        end = end +1;
        set_error(ERR_OK);
      }
      else
      {
        set_error(ERR_FULL);
      }
    }
    else
    {
      if (end < start)
      {
        array[end++] = symbol;
        set_error(ERR_OK);
      }
      else
      {
        set_error(ERR_FULL);
      }
    }
    
}

// removing the first element from the queue
char shift()
{
  char c = ' ';

  if (flag != false)
  {
    if (start <= end)
    {
      set_error(ERR_OK);
      char c = array[start++];
    }
    else
    {
      set_error(ERR_EMPTY);
    }
  }
  else
  {
    if (start >= end)
    {
      set_error(ERR_OK);
      char c = array[start++];
    }
    else
    {
      set_error(ERR_EMPTY);
    }
  }
  return c;
}

/*main code*/

int main(int argc, char *argv[])
{
  push(1);
  push(2);
  push(3);
  push(4);

  for (int i = 0; i < MAX_BUF; i++)
    printf("%d ", array[i]);

  return 0;
}