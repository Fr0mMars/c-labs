/* В текущем каталоге есть 2 канала in1 in2, в которые в случайном порядке поступают числа,
которые необходимо просуммировать и вывести окончательную сумму на экран.
Сумма выводится в отдельной строке, завершающейся символом конца строки.
Признаком окончания подачи символов в каналы является закрытие этих каналов посылающей стороной.*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/poll.h>

#define BUF_SIZE 256

int main(void)
{
  struct pollfd fds[2];
  char buf[BUF_SIZE];
  int i, rc, num;
  int sum = 0;

  if ((fds[0].fd = open("in1", O_RDONLY | O_NONBLOCK)) < 0)
  {
    perror("open in1");
    exit(-1);
  }
  if ((fds[1].fd = open("in2", O_RDONLY | O_NONBLOCK)) < 0)
  {
    perror("open in2");
    exit(-1);
  }

  fds[0].events = POLLIN;
  fds[1].events = POLLIN;

  while (fds[0].events || fds[1].events)
  {
    if (poll(fds, 2, 0) < 0)
    {
      perror("poll");
      exit(-1);
    }
    for (i = 0; i < 2; i++)
    {
      if (fds[i].events && fds[i].revents)
      {
        rc = read(fds[i].fd, buf, sizeof(buf) - 1);
        if (rc < 0)
        {
          perror("read");
          exit(-1);
        }
        else if (!rc)
        {
          fds[i].events = 0;
        }
        else
        {
          num = atoi(buf);
          sum += num;
        }
      }
    }
  }
  printf("%d\n", sum);
  return 0;
}