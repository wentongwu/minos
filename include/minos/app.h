#ifndef __MINOS_APP_H__
#define __MINOS_APP_H__

#include <minos/types.h>
#include <minos/string.h>
#include <minos/list.h>
#include <config/config.h>
#include <minos/errno.h>
#include <minos/init.h>
#include <minos/time.h>
#include <minos/current.h>
#include <minos/mutex.h>
#include <minos/mbox.h>
#include <minos/flag.h>
#include <minos/sem.h>
#include <minos/queue.h>

struct task_desc {
	char *name;
	task_func_t func;
	void *arg;
	prio_t prio;
	uint16_t aff;
	size_t size;
	unsigned long flags;
};

#define DEFINE_TASK(nn, f, a, p, af, ss, fl) \
	static const struct task_desc __used \
	task_desc_##f __section(.__task_desc) = { \
		.name = nn,		\
		.func = f,		\
		.arg = a,		\
		.prio = p,		\
		.aff = af,		\
		.size = ss,		\
		.flags = fl		\
	}

#define DEFINE_PERCPU_TASK(nn, f, a, ss, fl) \
	static const struct task_desc __used \
	task_desc_##f __section(.__task_desc) = { \
		.name = nn,		\
		.func = f,		\
		.arg = a,		\
		.prio = OS_PRIO_PCPU,	\
		.aff = PCPU_AFF_PERCPU,	\
		.size = ss,		\
		.flags = fl		\
	}

#define DEFINE_REALTIME_TASK(nn, f, a, p, ss, fl) \
	static const struct task_desc __used \
	task_desc_##f __section(.__task_desc) = { \
		.name = nn,		\
		.func = f,		\
		.arg = a,		\
		.prio = p,		\
		.aff = PCPU_AFF_NONE,	\
		.size = ss,		\
		.flags = fl		\
	}

#endif
