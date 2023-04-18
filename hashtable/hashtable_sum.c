#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 10
#define MAC_LENGTH 5
// error codes

#define ERR_OK 0    // no error
#define ERR_EMPTY 1 // table is empty
#define ERR_FULL 2  // table is full

/*structure*/

static int err_code = ERR_EMPTY;
static int size = 0;
struct charAndInt
{
  char *mac;
  int port;
};

typedef struct charAndInt macPort;
macPort mac_table[MAX_BUF];

int hashFunction(char *mac)
{
  int sum = sumFunction(mac);
  int key = sum % 10;
  return key;
}

int sumFunction(char *mac)
{
  int sum = 0;
  for (int i = 0; i < MAC_LENGTH; i++)
  {
    sum += mac[i];
  }
  return sum;
}

void push(char *mac, int port)
{
  // printf("mac = %s\n", mac);

  if (size <= MAX_BUF)
  {
    int key = hashFunction(mac);
    if (mac_table[key].mac != NULL)
    {
      int sum = sumFunction(mac);
      int counter = 0;
      // printf("%s \n", mac_table[key].mac);
      while (mac_table[key].mac != NULL && counter <= MAX_BUF)
      {
        sum = sum + 7;
        key = sum % 10;
        counter += 1;
        // printf("counter = %d\n", counter);
        // printf("%s \n", mac_table[key].mac);
      }
    }
    mac_table[key].mac = mac;
    mac_table[key].port = port;
    size += 1;
    // set_error(ERR_OK);
  }
  else
  {
      printf("МАС таблица полна\n");
    // set_error(ERR_FULL);
  }
}

static int searchPort(char *mac)
{

  int key = hashFunction(mac);

  if (mac_table[key].mac == mac)
  {
    printf("MAC %s port %d\n", mac_table[key].mac, mac_table[key].port);
    return mac_table[key].port;
  }

  int counter = 0;
  int sum = sumFunction(mac);
  while (mac_table[key].mac != mac || counter < size)
  {
    sum = sum + 7;
    key = sum % 10;
    counter += 1;
    if (mac_table[key].mac == mac)
    {
      printf("MAC %s port %d\n", mac_table[key].mac, mac_table[key].port);
      return mac_table[key].port;
    }
  }
  return -1;
}

static void clear() // set to default
{
  size = 1;
  for (int i = 0; i < MAX_BUF; i++)
  {
    mac_table[i].mac = NULL;
  }
}

void show()
{
  printf("MAC TABLE:\n");
  for (int i = 0; i < MAX_BUF; i++)
  {
    printf("%s %d \n", mac_table[i].mac, mac_table[i].port);
  }
}

int main()
{
  clear();

  push("1125b", 1);
  push("2125b", 0);
  push("1afaf", 2);
  push("1fafa", 3);
  push("1ffaa", 4);
  push("1aaff", 5);
  push("afaf1", 6);
  push("fafa1", 7);
  push("ffaa1", 8);
  push("aaff1", 9);
  push("11251", 1);

  show();
  searchPort("1125b");
  searchPort("1afaf");
  searchPort("aaff1");
  return 0;
}
