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
//#include "lib/libposix/sys/wait/waitpid.cpp"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Suspend thread until a child terminates");
    parser().registerPositional("PID", "PID of Process to wait");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{   // parse for PID
    int pid = atoi(arguments().get("PID"));
    // allocate int for status
    int status;

    pid_t result = waitpid(pid, &status, 0);
    
    if ((status >> 16) == 0) {
        return Success;
    } else {
        return NotFound;
    }
    // Done
}
