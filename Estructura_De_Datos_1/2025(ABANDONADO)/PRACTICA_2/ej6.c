//? Listas generales
// 6. Las listas enlazadas presentadas hasta este punto guardan espec´ıficamente datos de tipo int. En
// consecuencia, para guardar otros tipos de datos es necesario modificar varias partes del c´odigo, haci´endolo
// poco reutilizable. Esto puede evitarse utilizando el tipo de dato general void* y abstrayendo del c´odigo
// aquellas partes que hac´ıan uso del tipo de dato espec´ıfico.
// Lea la implementaci´on provista de listas simplemente enlazadas generales y el ejemplo presentado en
// el archivo main.c. Comp´arelo con la implementaci´on de listas simplemente enlazadas de enteros ¿qu´e
// diferencias encuentra?

//* Al ser de tipo void, tenemos que tener precaución al agregar o eliminar, ya que justamente debe funcionar para cualquier tipo entonces, tenemos que usar si o sí funciones auxiliares que dsp castearemos para coincidir tipo  deseado.