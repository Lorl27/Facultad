1. Guardar la Altura Y el Factor de Balance
Hacer esto es redundante y un desperdicio de memoria.
Como el Factor de Balance (FB) se calcula simplemente haciendo altura(izq) - altura(der), si ya tienes la altura, calcular el FB cuesta apenas una resta. Guardar una variable extra en el struct para el FB solo te obliga a mantener dos valores sincronizados, arriesgándote a que queden desfasados por un error en el código, sin ganar velocidad real.

2. Guardar ÚNICAMENTE el Factor de Balance (El giro de tuerca)
Aquí es donde te doy la razón: es muy complicado de programar. Pero, ¡así es exactamente como se programan los Árboles AVL en el mundo real (por ejemplo, en sistemas operativos y bases de datos)!

¿Por qué lo hacen si es más difícil? ¡Por la memoria!
Si guardas un int altura, estás gastando 32 bits (4 bytes) de memoria por cada nodo.

Si guardas únicamente el Factor de Balance, recuerda que en un AVL válido este valor solo puede ser -1, 0 o 1 (y temporalmente -2 o 2 durante una inserción). ¡Puedes representar esos 5 valores usando apenas 2 bits!
En un árbol de 10 millones de usuarios, ahorrar 30 bits por nodo es una optimización colosal.

¿Cómo se actualiza sin saber las alturas? (La parte que "complica la vida")
Como ya no tienes la altura para recalcular, tienes que actualizar el FB basándote puramente en álgebra relativa (cómo cambió el hijo afecta al padre).

En Inserciones / Eliminaciones (La Propagación):
En lugar de recalcular alturas, miras las "transiciones" de estado:

Si insertas un nodo y el FB del padre pasa de 0 a 1, significa que esa rama se hizo más larga. ¡El padre creció en altura! Tienes que avisarle al abuelo para que actualice su propio FB.

Si insertas un nodo y el FB del padre pasa de -1 a 0, significa que el hueco que tenía se rellenó. El árbol ahora es más "sólido", pero su altura total no cambió. ¡Ahí detienes la propagación hacia arriba! El abuelo ni se entera.

En las Rotaciones:
Esta es la peor pesadilla matemática. Tienes que deducir los nuevos Factores de Balance de los nodos que rotaron usando fórmulas algebraicas basadas en los Factores de Balance viejos.
Por ejemplo, si rotas a la derecha sobre un nodo P con hijo izquierdo H, el nuevo balance de P se calcula con una fórmula parecida a esta:
NuevoFB_P = ViejoFB_P + 1 - min(ViejoFB_H, 0)

Resumen de estudio:
- No guardar altura y factor de balance al mismo tiempo evita redundancia y errores de sincronización.
- Guardar solo el factor de balance reduce el uso de memoria drásticamente en nodos AVL.
- En un AVL válido, el factor de balance solo puede ser -1, 0 o 1, y temporalmente puede llegar a -2 o 2 durante inserciones o eliminaciones.
- Las actualizaciones se basan en transiciones del factor de balance del hijo al padre.
- En rotaciones, el nuevo factor de balance se calcula con fórmulas algebraicas usando los valores anteriores.
