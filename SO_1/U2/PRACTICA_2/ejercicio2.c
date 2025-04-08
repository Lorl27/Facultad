// j. 2. ¿C´uales de los siguientes componentes del estado de un programa se comparten entre los threads
// de un proceso?
// a) Valores de registros
// b) Heap
// c) Variables globales
// d) Stack


//TODO MENOS EL STACK + valores de registros , ya que cada hilo tiene so propio contexto de ejecución y éstos forman parte del mismo.
// Con cada contexto switch, cambian.