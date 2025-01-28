# Versión no recomendable 
def numerosFaltantes_nr (l : list[int]) -> set[int]:
    l.sort()
    maximo = l[-1]

    res = set()
    for x in range(maximo):
        if x not in l:
            res.add(x)

    return res

def test_numerosFaltantes_nr ():
    assert(numerosFaltantes_nr([1,2,3,7,9,3]) == {0,4,5,6,8})
    assert(numerosFaltantes_nr([10,7,3,4,0]) == {1,2,5,6,8,9})
    assert(numerosFaltantes_nr([0,1,2,3,4,5,6,7]) == set())
    assert(numerosFaltantes_nr([3,1,6,0,7,5,2,4]) == set())
    assert(numerosFaltantes_nr([5]) == {0,1,2,3,4})


# Versión recomendable
def numerosFaltantes (l: list[int]) -> set[int]:
    maximo = max(l)
    universo = set(range(maximo))
    s = set(l)
    return universo - s 

def test_numerosFaltantes ():
    assert(numerosFaltantes([1,2,3,7,9,3]) == {0,4,5,6,8})
    assert(numerosFaltantes([10,7,3,4,0]) == {1,2,5,6,8,9})
    assert(numerosFaltantes([0,1,2,3,4,5,6,7]) == set())
    assert(numerosFaltantes([3,1,6,0,7,5,2,4]) == set())
    assert(numerosFaltantes([5]) == {0,1,2,3,4})