/*
В системе существуют 2 региона разделяемой памяти, заполненной некоторыми числами (типа int).
Каждый из регионов имеет размер 1000 байт. Вам требуется разработать приложение,
которое попарно суммирует первые 100 чисел в этих регионах
и помещает суммы в новый (созданный вашим приложением) регион памяти размером 1000 байт.
Таким образом, после завершения работы Вашего приложения в памяти должен существовать регион
разделяемой памяти размером 1000 байт, содержащий в начале 100 сумм.
Перед завершением работы приложение выводит в стандартный поток ввода-вывода ключ созданного региона,
завершающийся символом конца строки. На вход ваше приложение принимает ключи существующих регионов памяти.
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FTOK_FILE "./solution.c"
#define MAXLEN 1000

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("You need to use at least two and only two parameters\n");
        return EXIT_FAILURE;
    }

    key_t key1, key2, mykey;
    int i, shmid1, shmid2, myshmid;

    struct mem_block
    {
        int nums[250];
    };
    struct mem_block *memory_block_1;
    struct mem_block *memory_block_2;
    struct mem_block *memory_block_my;

    key1 = atoll(argv[1]);
    key2 = atoll(argv[2]);
    mykey = ftok(FTOK_FILE, 1); // генерация ключа
    if (mykey == -1)
    {
        perror("Failed to generate unique key. Server compiler with a wrong name?\n");
        return EXIT_FAILURE;
    }

    /* выделяем блок разделяемой памяти */
    myshmid = shmget(mykey, MAXLEN, 0666 | IPC_CREAT);
    if (myshmid == -1)
    {
        perror("shmget error\n");
        return EXIT_FAILURE;
    }
    /* Получаем идентификаторы для выделенных блоков памяти */

    shmid1 = shmget(key1, MAXLEN, 0644);
    if (shmid1 == -1)
    {
        perror("shmget error: key not valid\n");
        return EXIT_FAILURE;
    }

    shmid2 = shmget(key2, MAXLEN, 0644);
    if (shmid2 == -1)
    {
        perror("shmget error: key not valid\n");
        return EXIT_FAILURE;
    }

    /* отображаем блоки разделяемой памяти в адресное пространство процесса */
    memory_block_my = (struct mem_block *)shmat(myshmid, 0, 0);
    memory_block_1 = (struct mem_block *)shmat(shmid1, 0, SHM_RDONLY);
    memory_block_2 = (struct mem_block *)shmat(shmid2, 0, SHM_RDONLY);

    for (i = 0; i < 100; i++)
    {
        memory_block_my->nums[i] = memory_block_1->nums[i] + memory_block_2->nums[i];
    }

    /* удаляем отображение */
    shmdt((void *)memory_block_my);
    shmdt((void *)memory_block_1);
    shmdt((void *)memory_block_1);

    /* удаляем отображение // удаляем блок разделяемой памяти
   shmctl(myshmid, IPC_RMID, 0);*/

    printf("%d\n", mykey);
    return EXIT_SUCCESS;
}