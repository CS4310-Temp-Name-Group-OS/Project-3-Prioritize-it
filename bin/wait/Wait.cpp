/*
 * Copyright (C) 2009 Niek Linnenbank
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
#include <sys/wait.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Suspend thread until specified process terminates");
    parser().registerPositional("PID", "PID of Process to wait");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{   // parse for PID
    int pid = atoi(arguments().get("PID"));
    
    if (pid <= 0)
    {
        printf("Invalid argument.\n");
        return InvalidArgument;
    }

    // Initialize status location
    int status;

    // Call waitpid and check result
    pid_t result = waitpid((pid_t)pid, &status, 0);

    if (result == (pid_t) pid)
    {
        return Success;
    }
    else if (errno == ESRCH)
    {
        ERROR("Errno: " << errno << "\n\r" << strerror(errno));
        return NotFound;
    }
    else
    {
        ERROR("Errno: " << errno << "\n\r" << strerror(errno));
        return IOError;
    }
    // Done
}
