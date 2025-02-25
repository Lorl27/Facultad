def aux_R (l : list, e : int, i : int, f : int) -> int:
    if i == f:
        #l.insert(i,e)
        l[i:f] = [e]
        return i
    m = (i + f) // 2
    if e > l[m]:
        return aux_R(l,e,m+1,f) 
    elif e < l[m]:
        return aux_R(l,e,i,m)
    else:
        return m

def insercion_dicotomica_R (l : list, e:int) -> int :
    return aux_R(l, e, 0, len(l))

def test_insercion_dicotomica_R () :
    lista = [1,2,4,5,6]
    assert(insercion_dicotomica_R(lista,4) == 2)
    assert(insercion_dicotomica_R(lista,1) == 0)
    assert(insercion_dicotomica_R(lista,6) == 4)
    assert(insercion_dicotomica_R(lista,3) == 2)
    assert(lista == [1,2,3,4,5,6])
    assert(insercion_dicotomica_R(lista,0) == 0)
    assert(lista == [0,1,2,3,4,5,6])
    assert(insercion_dicotomica_R(lista,10) == 7)
    assert(lista == [0,1,2,3,4,5,6,10])
    
def insercion_dicotomica_I (l : list, e : int) -> int:
    i = 0
    f = len(l)
    m = (i + f) // 2
    while i != f and l[m] != e:
        if (e > l[m]):
            i = m+1
        else:
            f = m
        m = (i + f) // 2
    if i == f:
        #l.insert(i,e)
        l[i:f] = [e]
    return m


def test_insercion_dicotomica_I () :
    lista = [1,2,4,5,6]
    assert(insercion_dicotomica_I(lista,4) == 2)
    assert(insercion_dicotomica_I(lista,1) == 0)
    assert(insercion_dicotomica_I(lista,6) == 4)
    assert(insercion_dicotomica_I(lista,3) == 2)
    assert(lista == [1,2,3,4,5,6])
    assert(insercion_dicotomica_I(lista,0) == 0)
    assert(lista == [0,1,2,3,4,5,6])
    assert(insercion_dicotomica_I(lista,10) == 7)
    assert(lista == [0,1,2,3,4,5,6,10])
    

#19-sept: ej 3, p4.