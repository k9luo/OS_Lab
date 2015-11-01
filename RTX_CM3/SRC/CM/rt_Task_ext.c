/**
* @file: rt_Task_ext.c
*/
#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_MemBox.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"

int rt_tsk_count_get (void) {
	int activeTaskAmount;
	int counter;
	
	activeTaskAmount = 0;
	
	for (counter = 1; counter <= os_maxtaskrun; counter++) {
    if (os_active_TCB[counter-1] != NULL) {
      activeTaskAmount++;
    }
  }
	
	if(os_idle_TCB.state != INACTIVE){
		activeTaskAmount++;
	}
	
	return activeTaskAmount;
}
/* end of file */
