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
    parser().setDescription("Suspend execution of calling thread until specified process terminates");
    parser().registerPositional("PID", "Process ID of the process to wait");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{   // Parse for PID
    int pid = atoi(arguments().get("PID"));
    
    // User input validation
    if (pid <= 0)
    {
        errno = EINVAL;
        ERROR("Errno: " << errno << "\n" << strerror(errno));
        return InvalidArgument;
    }

    // Initialize space for stat_loc
    int status;

    // Call waitpid, check result, and display error if neccessary
    pid_t result = waitpid((pid_t)pid, &status, 0);

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
    // Done
}
