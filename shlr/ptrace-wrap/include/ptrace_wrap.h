/*
 * This file is part of ptrace-wrap.
 *
 * ptrace-wrap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ptrace-wrap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with ptrace-wrap.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PTRACE_WRAP_H
#define PTRACE_WRAP_H

#include <pthread.h>
#include <semaphore.h>
#include <sys/ptrace.h>

typedef struct ptrace_wrap_request_t {
	enum __ptrace_request request;
	pid_t pid;
	void *addr;
	void *data;
	int *_errno;
	int stop;
} ptrace_wrap_request;

typedef struct ptrace_wrap_instance_t {
	pthread_t th;
	sem_t request_sem;
	ptrace_wrap_request request;
	sem_t result_sem;
	long result;
} ptrace_wrap_instance;

int ptrace_wrap_instance_start(ptrace_wrap_instance *inst);
void ptrace_wrap_instance_stop(ptrace_wrap_instance *inst);
long ptrace_wrap(ptrace_wrap_instance *inst, enum __ptrace_request request, pid_t pid, void *addr, void *data);

#endif //PTRACE_WRAP_H
