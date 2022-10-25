/*
 * Copyright (C) 2015 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/renice.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Output system process list");
    parser().registerFlag('n', "priority", "specify scheduling priority to be used for the process");
    parser().registerPositional("PRIO", "specified priority level for process");
    parser().registerPositional("PID", "PID of specified process.");
}

Renice::~Renice(){

}

Renice::Result Renice::exec()
{
    int pid = atoi(arguments().get("PID"));
    int prio = atoi(arguments().get("PRIO"));

    //check user input validation
    if (pid <= 0 || prio < 1 || prio > 5)
    {
        errno = EINVAL;
        ERROR("Errno: " << errno << "\n" << strerror(errno));
        return InvalidArgument;
    }

    pid_t result = renicepid((pid_t)pid, (PriorityNumber*) &prio);

    if (result == (pid_t)pid)
    {
        return Success;
    }
    else if (errno == ESRCH)
    {
        ERROR("Errno: " << errno << "\n" << strerror(errno));
        return NotFound;
    }
    else
    {
        ERROR("Errno: " << errno << "\n" << strerror(errno));
        return IOError;
    }

}