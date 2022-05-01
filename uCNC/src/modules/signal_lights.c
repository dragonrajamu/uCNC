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

#ifdef ENABLE_MAIN_LOOP_MODULES

#define HOLD_LIGHT DOUT5
#define RESUME_LIGHT DOUT6

// this is the recommended way of creating a listener that gets executed when an event is fired
// in this case this listener executes on every call of cnc_dotasks_hook inside the main loop
// this works as long as the cnc_dotask_hook event handler is not overriden
// pid module does this for this hook event handler so if any pid is enabled this will never get executed
// to allow both pid and this module to work, pid must be modified to use a listener instead of overriding the hook event handler

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

// this is an example on who to override an hook event handler
// this will only work if no other module tries to override the same hook
// also by doing this this will bypass the default event handler and all listeners that are listening to this event will not be eexcuted
// the advantage of this is that it gets executed directly when called without having to pass through the default event handler (better performance)

//the following code should be deleted if other modules use the cnc_dotasks event listener
void mod_cnc_dotasks_hook(void)
{
    control_signal_lights();
}

#endif
