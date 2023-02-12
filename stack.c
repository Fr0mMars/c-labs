#include <stdio.h>
#include <string.h>
//error codes
#define ERR_OK 0 // no error
#define ERR_EMPTY 1 // stack is empty 
#define ERR_FULL 2 // stack is full 

#define MAX_BUF 100 // maximum stack size 

/*variables*/

int err_code = ERR_EMPTY; 
char array[MAX_BUF];
char str[] = "((1+2)(2+3)(3+4)((4+5)(5+6)))";
char str2[] = "COH";
int top = -1;

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
  switch(err_code)
  {
    case ERR_EMPTY:
      printf("пуст");
      break;
    case ERR_FULL:
      printf("полон");
      break;
    case ERR_OK:
      printf("нет ошибок");
      break;
    default:
      printf("незнай чо за код ошибки");
      break;
  }

  
}

// adding an element to the stack
void push(char symbol)
{

    if (top < (MAX_BUF - 1))
    {
        array[++top] = symbol;
        set_error(ERR_OK);
    }
    else
    {
        set_error(ERR_FULL);
    }
}

//removing the last element from the stack
char pop()
{
    char c = ' ';
    if (top >= 0)

    {
        set_error(ERR_OK);
        char c = array[top];
        top--;
    }
    else
    {
        set_error(ERR_EMPTY);
    }
    return c;
}

//getting the last element from the stack
char peak()
{
    char c = ' ';
    if (top >= 0)
    {
        set_error(ERR_OK);
        c = array[top];
    }
    else
    {
        set_error(ERR_EMPTY);
    }
    return c;
}

                                                    /*main code*/

int main(int argc, char *argv[])
{
    int len = strlen(str); // adding to variable len length string str

   for (int i = 0; i < len; i++)  // iterate over the elements of a string str
        {
      switch(str[i])
      {
        case '(':
          push('(');
          break;
        case ')':
          pop();
          break;
        default:
          continue;
          break;
      }

      int rc = get_error();
      if (rc != ERR_OK) err_str(rc);
    }

    if (peak() == ERR_OK)
    {
        printf("Непарные скобки присутсвуют\n");
    }
    else
    {
        printf("Непарные скобки отсутсвуют\n");
    }

    /*
        for (int i = 0; i < strlen(str2); i++)
        {

            push(str2[i]);
            if (get_error() == ERR_FULL)
            {
                printf("main: Стек полон\n");
            }
        }

        for (int i = 0; i < strlen(str2); i++)
        {
            printf("%c", peak());

            pop();

            if (get_error() == ERR_EMPTY)
            {
                printf("лишняя ) в позиции: %d \n", i);
                break;
            }
        }
        */

    return 0;
}