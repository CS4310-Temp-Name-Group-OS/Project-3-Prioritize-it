
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

#ifndef __LIBPOSIX_RENICE_H
#define __LIBPOSIX_RENICE_H

#include <Macros.h>
#include "types.h"

/**
 * @addtogroup lib
 * @{
 *
 * @addtogroup libposix
 * @{
 */

/**
 * @brief Change process priority.
 *
 * The renicepid() function will change the priority of a specified
 * process.
 *
 * @param pid Process ID of specified process to change.
 * @param prio Newly specified priority.
 *
 * @return Process ID of the child on success or -1 on error
 */

extern C pid_t renicepid(pid_t pid, PriorityNumber * prio);

/**
 * @}
 * @}
 */

#endif /* __LIBPOSIX_RENICE_H */
