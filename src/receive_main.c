
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#include "fd_event.h"

#define IP_ADDR "127.0.0.1"
#define PORT 45000

// Make sure this is big enough for your message!
const char buffer[7];

int init_sock(void) {
  // Creating socket file descriptor
  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("Socket creation failed\n");
    exit(EXIT_FAILURE);
  }
  struct sockaddr_in rec_addr;
  // Make sure all fields are zero
  memset(&rec_addr, 0, sizeof rec_addr);
  // Specify IPv4
  rec_addr.sin_family = AF_INET;
  // Set IP address
  rec_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
  // Set port
  rec_addr.sin_port = htons(PORT);
  // Binding our socket to an address so it will start listening
  if (bind(sockfd, (struct sockaddr *)&rec_addr, sizeof rec_addr) < 0) {
    printf("Bind failed\n");
    exit(EXIT_FAILURE);
  }
  return sockfd;
}

int main(int argc, char *argv[]) {
  event_init();
  // Creating socket file descriptor
  int sockfd = init_sock();
  event_append(sockfd);
  // Event loop
  while (1) {
    int active_fd;
    // Wait for the socket to receive data
    if ((active_fd = event_wait(&sockfd, 1)) < 0) {
      continue;
    }
    // Make sure the active fd is our listening socket
    if (active_fd == sockfd) {
      // Receive the message into the buffer
      recvfrom(sockfd, (void *)buffer, sizeof buffer, MSG_WAITALL, NULL, NULL);
      printf("%s\n", (char *)buffer);
    }
  }
  // Close our file descriptors; this will never happen but it's good practice!
  close(sockfd);
  return 0;
}
