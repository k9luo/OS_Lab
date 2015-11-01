/**
* @file: helloworld.c
* @brief: Two simple tasks running pseduo-parallelly
*/

#include <LPC17xx.h>
#include <RTL.h>
#include <stdio.h>
#include "uart_polling.h"
#include "../../RTX_CM3/INC/RTL_ext.h"

__task void enumerateTasks()
{
	int num;
	while (1) {
		num = os_tsk_count_get();
		printf("number of tasks: %d.\n", num);
	}
}

__task void task1()
{
	unsigned int i = 0;
	for(;; i++)
	{
		printf("Task1: %d\n", i);
		os_dly_wait(100);
	}
}

__task void task2()
{
	while(1)
	{
		printf("Task2: Task2!\n");
		os_dly_wait(300);
	}
}
__task void task3()
{
	while(1)
	{
		printf("Task3: Task3!\n");
		os_dly_wait(400);
	}
}
__task void task4()
{
	while(1)
	{
		printf("Task4: Task4!\n");
		os_dly_wait(500);
	}
}

__task void init(void)
{
	os_tsk_create(enumerateTasks, 1);
 	os_tsk_create(task1, 1); // task1 at priority 1
 	os_tsk_create(task2, 1); // task2 at priority 1
	os_tsk_create(task3, 1); // task3 at priority 1
 	os_tsk_create(task4, 1); // task4 at priority 1
	
	os_tsk_delete_self(); // must delete itself before exiting
}

int main ()
{
	SystemInit();
	uart0_init();
	os_sys_init(init);
}
