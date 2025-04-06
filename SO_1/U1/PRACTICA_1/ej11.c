// Ej. 11 (Servidor de turnos). El archivo skel
//  server.c implementa un pequeno servidor que recibe
//  conexiones por un puerto TCP (4040) y responde a cada pedido con un entero unico. Los pedidos, enviados
//  por los clientes, son simplemente una lnea NUEVO terminada por \n. Para cerrar una conexion, el cliente
//  enva CHAU.
//  Como esta escrito, el servidor solo puede atender a un cliente a la vez, dejando en espera a todo el resto
//  hasta que se cierre la conexion con el primer cliente.
//  Para recibir conexiones TCP, el proceso debe:
//  Llamar a socket(AF_INET, SOCK_STREAM, 0) para conseguir un socket (un fd)
//  Usar bind para asociarlo a un puerto.
//  Usar listen para permitir que acepte conexiones
//  Llamar a accept ahora bloquea hasta que se reciba una conexion. accept devuelve un fd represen
// tando a la conexion, y puede usar read/write sobre el mismo.
//  Tareas:
//  a) Modi que el servidor para atender concurrentemente a todas las conexiones abiertas levantando un
//  nuevo proceso por cada conexion. Nota: todos los clientes deberan poder hacer pedidos sin esperar a
//  otros, y siempre debe poder conectarse un nuevo cliente.
//  b) Use memoria compartida entre los procesos para mantener el ultimo entero enviado a un cliente.
//  Que necesita tener en cuenta para garantizar que dos pedidos nunca reciben el mismo entero?