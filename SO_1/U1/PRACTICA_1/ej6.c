// Ej. 6. Es getchar() una llamada al sistema? Por que s o por que no? Como funciona ungetc()?

// No, no es ya que al igual que free() , forma parte de una biblioteca éstandar. Aunque puede realizar una llamada al sistema (como read ) para obtener datos del sistema operativo, esto generalmente ocurre a través de un búfer.

// unget() lo que hace es devolver el último caracter al stdin , es decir, lo "des-lee".

