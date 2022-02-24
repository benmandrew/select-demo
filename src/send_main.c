
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#include "fd_event.h"

// How often we send the message in seconds
#define TIME_PERIOD 1
// Address of local loopback interface
#define IP_ADDR "127.0.0.1"
// Arbitrary port, consistent across sender and receiver
#define PORT 45000

// The message we're sending
const char buffer[] = "Hello!";

// Initialise the address structure
struct sockaddr_in init_addr(void) {
  struct sockaddr_in addr;
  // Make sure all fields are zero
  memset(&addr, 0, sizeof addr);
  // Specify IPv4
  addr.sin_family = AF_INET;
  // Set IP address
  addr.sin_addr.s_addr = inet_addr(IP_ADDR);
  // Set port
  addr.sin_port = htons(PORT);
  return addr;
}

int main(int argc, char *argv[]) {
  event_init();
  // Creating socket file descriptor
  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("Socket creation failed\n");
    exit(EXIT_FAILURE);
  }
  // Create heartbeat timer
  struct timer timer = event_timer_append(TIME_PERIOD, 0);
  struct sockaddr_in dest_addr = init_addr();
  // Event loop
  while (1) {
    int active_fd;
    // Wait for the timer to fire
    if ((active_fd = event_wait(&timer.fd, 1)) < 0) {
      continue;
    }
    // Make sure the active fd is our timer
    if (active_fd == timer.fd) {
      // Reset our timer so it will fire again
      event_timer_reset(&timer);
      // Send our message
      sendto(sockfd, buffer, sizeof buffer, MSG_CONFIRM,
             (const struct sockaddr *)&dest_addr, sizeof dest_addr);
      printf("Sent packet\n");
    }
  }
  // Close our file descriptors; this will never happen but it's good practice!
  close(sockfd);
  close(timer.fd);
  return 0;
}
