Arbol23 arbol23_crear() {
    return NULL;
}


int cantidad_de_valores(Arbol23 t) {
    if (t == NULL) return 0;
    
    // Si su puntero derecho es la marca CENTINELA, solo tiene 1 valor (k1)
    if (t->right == CENTINELA) return 1;
    
    // De lo contrario, es un nodo lleno con 2 valores (k1 y k2)
    return 2;
}


Arbol23 crear_nodo_binario(int x, Arbol23 l, Arbol23 r) {
    Arbol23 nodo = malloc(sizeof(struct nodo_arbol23));
    nodo->k1 = x;
    nodo->left = l;
    nodo->middle = r;
    // Obligatorio por enunciado: marcar el 3er hijo como CENTINELA
    nodo->right = CENTINELA; 
    return nodo;
}


int insertar_impl(Arbol23 t, int x, int* out_x, Arbol23* out_l, Arbol23* out_r) {
    if (t == NULL) return 0;

    // 1. ¿SOY UNA HOJA? (Como es perfectamente balanceado, si left es NULL, todos son NULL)
    if (t->left == NULL) {
        if (cantidad_de_valores(t) == 1) {
            // CASO FÁCIL: Hay espacio. Lo acomodamos para que k1 < k2
            if (x < t->k1) {
                t->k2 = t->k1;
                t->k1 = x;
            } else {
                t->k2 = x;
            }
            t->right = NULL; // Ya no es binario, le quitamos el CENTINELA
            return 0; // 0 = No se saturó
        } else {
            // ¡OVERFLOW EN LA HOJA! Hay 3 valores (k1, k2, x).
            // Hay que ordenarlos para saber quién sube y quiénes se dividen.
            int min, med, max;
            if (x < t->k1) { min = x; med = t->k1; max = t->k2; }
            else if (x < t->k2) { min = t->k1; med = x; max = t->k2; }
            else { min = t->k1; med = t->k2; max = x; }

            // Llenamos las variables de salida para que el padre se arregle
            *out_x = med;
            *out_l = crear_nodo_binario(min, NULL, NULL);
            *out_r = crear_nodo_binario(max, NULL, NULL);
            return 1; // 1 = ¡Me saturé!
        }
    }

    // 2. SOY NODO INTERNO: Bajar buscando la hoja correspondiente
    int se_saturo_el_hijo;
    if (cantidad_de_valores(t) == 1) {
        if (x < t->k1) se_saturo_el_hijo = insertar_impl(t->left, x, out_x, out_l, out_r);
        else se_saturo_el_hijo = insertar_impl(t->middle, x, out_x, out_l, out_r);
    } else {
        if (x < t->k1) se_saturo_el_hijo = insertar_impl(t->left, x, out_x, out_l, out_r);
        else if (x < t->k2) se_saturo_el_hijo = insertar_impl(t->middle, x, out_x, out_l, out_r);
        else se_saturo_el_hijo = insertar_impl(t->right, x, out_x, out_l, out_r);
    }

    // 3. Si el hijo resolvió su problema solo, nosotros también terminamos
    if (se_saturo_el_hijo == 0) return 0;

    // 4. ¡OVERFLOW EN EL HIJO! Nos pateó un valor (*out_x) y dos ramas (*out_l y *out_r).
    int val = *out_x;
    Arbol23 sub_l = *out_l;
    Arbol23 sub_r = *out_r;

    if (cantidad_de_valores(t) == 1) {
        // Tenemos espacio, absorbemos al huérfano y sus ramas
        if (val < t->k1) {
            t->k2 = t->k1;
            t->k1 = val;
            t->right = t->middle; // Desplazamos hijos
            t->middle = sub_r;
            t->left = sub_l;
        } else {
            t->k2 = val;
            t->middle = sub_l;
            t->right = sub_r;
            // left queda igual
        }
        return 0; // Problema contenido. No saturamos a nuestro propio padre.
    } else {
        // ¡DOBLE OVERFLOW! Nosotros también estamos llenos. 
        // Armamos el desempate a 4 ramas y le pateamos el problema a nuestro padre.
        int min, med, max;
        Arbol23 l1, l2, l3, l4; // Las 4 ramas resultantes

        if (val < t->k1) {
            min = val; med = t->k1; max = t->k2;
            l1 = sub_l; l2 = sub_r; l3 = t->middle; l4 = t->right;
        } else if (val < t->k2) {
            min = t->k1; med = val; max = t->k2;
            l1 = t->left; l2 = sub_l; l3 = sub_r; l4 = t->right;
        } else {
            min = t->k1; med = t->k2; max = val;
            l1 = t->left; l2 = t->middle; l3 = sub_l; l4 = sub_r;
        }

        *out_x = med;
        *out_l = crear_nodo_binario(min, l1, l2);
        *out_r = crear_nodo_binario(max, l3, l4);
        return 1; // Le pasamos la bomba al padre
    }
}



