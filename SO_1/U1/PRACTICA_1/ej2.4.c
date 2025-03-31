
//  d) Al hacer fork(), como cambia el valor de getpid()? Y al hacer exec()?


//* Al realizar fork, el valor de getpid() varía dependiendo de si estamos en Parent o en Child
//* Al realizar exec(), no se cambia el valor de getpid().