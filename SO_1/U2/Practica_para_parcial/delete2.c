//blablabla ... cliente

#define MAX_EVENTS 5

int main(){
    int sock_cli;
    struct sockadrr_un srv_name,cli_name;
    ssize_t nbytes;
    buff[MAXMSG+1];
    socklen_t srv_size;

    //1
    sock_cli=sock(AF_UNIX,SOCK_STREAM,0);

    //2
    cli_name.sun_family=AF_UNIX;
    strncpy(cli_name.sun_path,CLI_NOMBRE,sizeof(cli_name.sun_path));
    unlink(cli_name.sun_path);

    //3 bind!
    bind(sock_cli,(struct sockaddr *)&cli_name,sizeof(cli_name));

    //4 conex con srv + epoll + connect!

    srv_name.sun_family=AF_UNIX;
    strncpy(srv_name.sun_path,SRV_NOMBRE,sizeof(srv.sun_path));
    srv_size=sizeof(struct sockaddr_un);

     connect(sock_cli,(struct sockaddr_un *)&srv_name,srv_size);

    int fde=epoll_create1(0);
    struct epoll_event ev,events[MAX_EVENTS];
    
    // para sdtin y para cli:
    ev.events=EPOLLIN;
    ev.data.fd=STDIN_FILENO;
    epoll_ctl(fde,EPOLL_CTL_ADD,STDIN_FILENO,&ev);

    ev.events=EPOLLIN;
    ev.data.fd=sock_cli;
    epoll_ctl(fde,EPOLL_CTL_ADD,sock_cli,&ev);

   

    printf("[CLIENTE] conectado al srv %s",SRV_NOMBRE);

    while(1){
        int n=epoll_wait(fde,events,MAX_EVENTS,-1);

        for(int x=0;x<n;x++){
            if(events[x].data.fd==STDIN_FILENO){
                
                if (fgets(buff, MAXMSG, stdin) == NULL) continue;
                buff[strcspn(buff, "\n")] = '\0';

                send(sock_cli, buff, strlen(buff), 0);


                if(strncmp(buff,"salir",5)==0){
                    printf("cleinte pidio salir...\n");
                    close(fde);
                    close(sock_cli);
                    unlink(SRV_NOMBRE);
              
                }
                
            }
            else if(events[x].data.fd==sock_cli){
                nbytes=recv(sock_cli,buff,MAX_MSG,0);

                if(nbytes<=0){
                    printf("cerrando cli side..\n");
                    close(fde);
                    close(sock_cli);
                     unlink(SRV_NOMBRE);
                }

                buff[nbytes]='\0';
                printf("[CLI] msg enviando al srv: %s",buff);

                
            }
        }
    }










    return 0;
}