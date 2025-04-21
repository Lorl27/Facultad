int sockfd = socket(AF_INET, SOCK_STREAM, 0);
// lo bindés y ponés en listen()
int epoll_fd = epoll_create1(0);

event.events = EPOLLIN;
event.data.fd = sockfd;
epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event);

while (1) {
    int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
    for (int i = 0; i < nfds; i++) {
        if (events[i].data.fd == sockfd) {
            // nueva conexión entrante
            int cliente = accept(sockfd, ...);
            // agregar cliente a epoll
        } else {
            // hay datos en el socket cliente
            read(events[i].data.fd, ...);
        }
    }
}
