def dicotomica_R (l : list, e : str) -> bool:
    if l == []:
        return False
    m = len(l)//2
    if (e > l[m]):
        return dicotomica_R(l[m+1:],e)
    elif (e < l[m]):
        return dicotomica_R(l[:m],e)
    else:
        return True


def dicotomica_I (l : list, e : str) -> bool:
    m = len(l) // 2
    while (l != [] and l[m] != e):
        if (e < l[m]):
            l = l[:m]
        else: 
            l = l[m+1:]
        m = len(l) // 2
    return l != []


def dicotomica_R2 (l : list, e : str, i : int, f : int) -> bool:
    if i == f:
        return False 
    m = (i + f) // 2
    if (e > l[m]):
        return dicotomica_R2(l,e,m+1,f) 
    elif (e < l[m]):
        return dicotomica_R2(l,e,i,m)
    else:
        return True
    
def dicotomica_I2 (l : list, e : str) -> bool:
    i = 0
    f = len(l)
    m = (i + f) // 2
    while (i != f and l[m] != e):
        if (e > l[m]):
            i = m+1
        else:
            f = m
        m = (i + f) // 2
    return l[m] == e

