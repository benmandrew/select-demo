
#include "fd_event.h"

fd_set s;

// Initialise fd_set to empty
void event_init(void) { FD_ZERO(&s); }

// Add file descriptor to the fd_set
void event_append(int fd) { FD_SET(fd, &s); }

void event_timer_reset(struct timer *t) {
  timerfd_settime(t->fd, 0, &(t->v), NULL);
}

// Arm our timer to go off after 'sec' seconds and 'nsec' nanoseconds
void event_timer_arm(struct timer *t, long sec, long nsec) {
  t->v = (struct itimerspec){
      .it_interval = {0, 0},
      .it_value = {sec, nsec},
  };
  event_timer_reset(t);
}

// Add a timer to our fd_set that will go off after 'sec' seconds and 'nsec' nanoseconds
struct timer event_timer_append(long sec, long nsec) {
  struct timer t;
  t.fd = timerfd_create(CLOCK_REALTIME, 0);
  event_timer_arm(&t, sec, nsec);
  event_timer_reset(&t);
  event_append(t.fd);
  return t;
}

// Wait on our set of file descriptors
int event_wait(int *fds, int n_fds) {
  // 'select' modifies the 'fd_set', so make a copy and pass that
  fd_set copy = s;
  int n_ready;
  if ((n_ready = select(FD_SETSIZE, &copy, NULL, NULL, NULL)) < 0) {
    exit(EXIT_FAILURE);
  } else if (n_ready == 0) {
    return -1;
  }
  // Find which file descriptor is active and return it
  for (int i = 0; i < n_fds; i++) {
    if (FD_ISSET(fds[i], &copy)) {
      return fds[i];
    }
  }
  return -1;
}
