/*
    Name: signal_lights.c
    Description: A signal light module for µCNC.

    Copyright: Copyright (c) João Martins
    Author: João Martins
    Date: 01-05-2022

    µCNC is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version. Please see <http://www.gnu.org/licenses/>

    µCNC is distributed WITHOUT ANY WARRANTY;
    Also without the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the	GNU General Public License for more details.
*/

#include "../cnc.h"

#define HOLD_LIGHT DOUT5
#define RESUME_LIGHT DOUT6

void control_signal_lights(void);

CREATE_LISTENER(cnc_dotasks_delegate, control_signal_lights);

void control_signal_lights(void)
{
    if (cnc_get_exec_state(EXEC_HOLD))
    {
        io_set_output(HOLD_LIGHT, true);
        io_set_output(RESUME_LIGHT, false);
    }
    else
    {
        io_set_output(HOLD_LIGHT, false);
        io_set_output(RESUME_LIGHT, true);
    }
}