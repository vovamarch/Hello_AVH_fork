/*---------------------------------------------------------------------------
 * Copyright (c) 2020-2021 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include CMSIS_device_header
#include "cmsis_os2.h"
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif

#include "app.h"

extern void stdout_init(void);

#ifdef __USE_GUI

#include "platform.h"
#include "arm_2d_helper.h"
#include "example_gui.h"

#endif

int main(void)
{

#ifdef __USE_GUI
    arm_irq_safe
    {
        arm_2d_init();
        example_gui_init();
    }
#endif

    // System Initialization
    SystemCoreClockUpdate();
    
    // Initialize STDOUT
    stdout_init();

#if defined(RTE_Compiler_EventRecorder) && \
    (defined(__MICROLIB) ||                \
     !(defined(RTE_CMSIS_RTOS2_RTX5) || defined(RTE_CMSIS_RTOS2_FreeRTOS)))
    EventRecorderInitialize(EventRecordAll, 1U);
#endif

    osKernelInitialize();   // Initialize CMSIS-RTOS2
    initialize_threads();       // Initialize application
    osKernelStart();        // Start thread execution

    for (;;) {}
}
