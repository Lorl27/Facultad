def palabraMasLarga (texto: str) -> dict:
    res = {} # Es un diccionario
    for palabra in texto.split():
        n = len(palabra)
        palabra = palabra.lower()
        for l in palabra:
            if (l not in res) or (len(res[l]) < n) :
                res[l] = palabra
    return res

def test_palabraMasLarga():
    texto = "Hoy es un hermoso dia de primavera"
    d = palabraMasLarga(texto)
    assert(d['h'] == "hermoso")
    assert(d['o'] == "hermoso")
    assert(d['y'] == "hoy")
    assert(d['e'] == "primavera")
    assert(d['s'] == "hermoso")
    assert(d['u'] == "un")
    assert(d['n'] == "un")
    assert(d['r'] == "primavera")
    assert(d['m'] == "primavera")
    assert(d['d'] == "dia")
    assert(d['i'] == "primavera")
    assert(d['a'] == "primavera")
    assert(d['p'] == "primavera")
    assert(d['v'] == "primavera")

def palabraMasLarga2 (texto: str) -> dict:
    res = {}
    for palabra in texto.split():
        n = len(palabra)
        palabra = palabra.lower()
        for l in palabra:
            if (l not in res) or (res[l][1] < n) :
                res[l] = (palabra,n)
    
    for c in res:
        res[c] = res[c][0]

    return res


#26-sept ej6,p4.