// Ej. 1 (Pan y Manteca). Supongamos que tenemos un proceso A que quiere hacerse un pan con
// manteca. La presencia del pan en la mesa se simboliza con una variable booleana P, e ıdem para la manteca con M. Ambas variables estan protegidas por un mutex lk. 
//El proceso A, al haber observado
// que no habıa ninguna de las dos cosas, se puso a esperar en una variable de condici´on cv a que alguien lo despierte cuando ambas cosas existan sobre la mesa.
// Si se despierta a A con un solo ingrediente (un
// estado inaceptable), A destruye la casa en un ataque de furia.
// Ahora, el proceso B, habiendo obtenido ambos ingredientes, intenta despertar a A vıa la siguiente secuencia:
pthread_mutex_lock(&lk);
P = true;
pthread_cond_signal(&cv);
M = true;
pthread_mutex_unlock(&lk);
//¿Es esto correcto? ¿Qu´e problema puede haber?

//NO. no estamos usando el mètodo MESA . no existe un while entonces si otro proceso viene y roba los ingredientes , el proceso A se despertara y se enojara porque no los tendra a todos -- rompiendo toda la casa --.
