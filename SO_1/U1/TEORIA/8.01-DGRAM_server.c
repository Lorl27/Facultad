#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "8.0-socket_server_configuration.h"

// socket server echo datagram

/* NOTITAS:
          dominio socket
          local: AF_UNIX v AF_LOCAL (adress Family)
         red: AF_INET v AF_INET6

/         types:_
/         :)  udp , paquetes a dir no trust (no verifico si llego) cartas
/          stream: tel fijo like

/         protocol x default:0 - en redes, + info.

// struct sockaddr_un{
//     sa_family_t sun_family;  //af_unix : local
//     char sun_path[108]; //donde vive
// };

// struct sockaddr_in{
//     sa_family_t son_family;  //af_inex  :red
//     in_port_t sin_port;  //puerto
//     struct in_addr sin_addr;   //byte 
// };


*/


//SRV_NAME "./SRV_NAME"

/* Servidor Echo */

int main(){

  int sock_srv;
  struct sockaddr_un srv_name;
  struct sockaddr_un cli_name;
  socklen_t cli_size = sizeof(cli_name);

  ssize_t nbytes;
  char buff[MAXMSG+1];

  /* Creación del socket */
  sock_srv = socket(AF_UNIX, SOCK_DGRAM, 0);
  if(sock_srv < 0){
    perror("Falló la creación del socket ");
    exit(EXIT_FAILURE);
  }

  printf("[DIAG-SV] socket creado\n");


  /* Creamos la estructura de la dirección del socket */
  srv_name.sun_family = AF_UNIX;
  strncpy(srv_name.sun_path, SRV_NOMBRE, sizeof(srv_name.sun_path)); //man sockdrr

  // remove socket address path if it is under usage (https://gavv.github.io/articles/unix-socket-reuse/)
  unlink(srv_name.sun_path);

  /* Asignación del nombre */
  if( (bind(sock_srv, (struct sockaddr*) & srv_name , sizeof(srv_name))) < 0 ) {
    perror("Falló la asignación de nombre");
    exit(EXIT_FAILURE);
  }

  printf("[DIAG] SOCKET: %s\n", SRV_NOMBRE);

  /* El servidor se queda a la espera de un mensaje por el socket */
  nbytes = recvfrom(sock_srv, buff, MAXMSG, 0, (struct sockaddr *) &cli_name, &cli_size);  //donde recibo info.
  if(nbytes < 0) {
    perror("Falló el recvfrom");
    exit(EXIT_FAILURE);
  }

  printf("[DIAG] RECV: >%s<\n", buff);

  /* Responder el echo! */
  nbytes = sendto(sock_srv, buff, nbytes, 0, (struct sockaddr *) & cli_name, cli_size); //donde mando info
  if(nbytes < 0) {
    perror("Falló el sendto");
    exit(EXIT_FAILURE);
  }

  printf("[DIAG] SEND: OK\n");

  /*****************************************/
  close(sock_srv);
  remove(SRV_NOMBRE);

  return EXIT_SUCCESS;
}
