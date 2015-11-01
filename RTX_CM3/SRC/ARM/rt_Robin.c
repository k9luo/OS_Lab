/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    RT_ROBIN.C
 *      Purpose: Round Robin Task switching
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2012 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_List.h"
#include "rt_Task.h"
#include "rt_Time.h"
#include "rt_Robin.h"

/*----------------------------------------------------------------------------
 *      Global Variables
 *---------------------------------------------------------------------------*/

struct OS_ROBIN os_robin;

/*----------------------------------------------------------------------------
 *      Global Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- os_init_robin ---------------------------------*/

__weak void os_init_robin (void) {
  /* Initialize Round Robin variables. */
  os_robin.task = NULL;
  os_robin.tout = (U16)os_rrobin - 1;
}

/*--------------------------- os_chk_robin ----------------------------------*/

__weak void os_chk_robin (void) {
  /* Check if Round Robin timeout expired and switch to the next ready task. */
  P_TCB p_new;

  if (os_robin.task != os_rdy.p_lnk) {
    /* New task was suspended, reset Round Robin timeout. */
    os_robin.task = os_rdy.p_lnk;
    os_robin.time = (U16)os_time + os_robin.tout;
  }
  if (os_robin.time == (U16)os_time) {
    /* Round Robin timeout has expired, swap Robin tasks. */
    os_robin.task = NULL;
    p_new = os_get_first (&os_rdy);
    os_put_prio ((P_XCB)&os_rdy, p_new);
  }
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/

