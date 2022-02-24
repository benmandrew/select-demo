
#ifndef FD_EVENT_H
#define FD_EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <unistd.h>

struct timer {
  // File descriptor
  int fd;
  // Cached copy of the timer's starting time,
  // so that we can reset it
  struct itimerspec v;
};

void event_init(void);

void event_append(int fd);

void event_timer_reset(struct timer *t);

struct timer event_timer_append(long sec, long nsec);

int event_wait(int *fds, int n_fds);

#endif
