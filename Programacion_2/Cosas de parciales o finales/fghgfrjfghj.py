# Given dictionary list, extract dictionary with maximum keys.

def asad(l):
    cont=0
    res=0
    for x in l:
        if len(x)>cont:
            res = x 
            cont = len(x)
    return res

p=[ {"gfg": 2, "best" : 4}, {"gfg": 2, "is" : 3, "best" : 4, "CS" : 9}, {"gfg": 2}]
#4

# print(asad(p))

# Give a dictionary with value lists, sort the keys by summation of values in value list.

# Input : test_dict = {‘Gfg" : [6, 7, 4], ‘best" : [7, 6, 5]} 
# Output : {‘Gfg": 17, ‘best": 18} 
# Explanation : Sorted by sum, and replaced. 

def dicvalue(d):
    for x in d.keys():
        d[x]=sum(d[x])
    print(d)

# dicvalue({"Gfg" : [6, 7, 4], "best" : [7, 6, 5]} )

# Given list of dictionaries, sort dictionaries on basis of Key’s index value.

# Input : [{"Gfg" : [6, 7, 8], "is" : 9, "best" : 10}, {"Gfg" : [2, 0, 3], "is" : 11, "best" : 19}, {"Gfg" : [4, 6, 9], "is" : 16, "best" : 1}], K = "Gfg", idx = 0 
# Output : [{‘Gfg’: [2, 0, 3], ‘is’: 11, ‘best’: 19}, {‘Gfg’: [4, 6, 9], ‘is’: 16, ‘best’: 1}, {‘Gfg’: [6, 7, 8], ‘is’: 9, ‘best’: 10}] 
# Explanation : 2<4<6, hence dictionary ordered in that way by 0th index of Key. 

def chuchas(lost,key,indice):
    basura=[]
    nuevo=[]
    for x in lost:
        for y in x.keys():
            if y == key:
                p=x[y][indice]
                basura.append(p)
    basura=sorted(basura)
    print(basura)
    

h=[{"Gfg" : [6, 7, 8], "is" : 9, "best" : 10}, {"Gfg" : [2, 0, 3], "is" : 11, "best" : 19}, {"Gfg" : [4, 6, 9], "is" : 16, "best" : 1}]

# chuchas(h,"Gfg",0 )

# Given a dictionary, perform append of keys followed by values in list.

# Input : test_dict = {“Gfg” : 1, “is” : 2, “Best” : 3} 
# Output : [‘Gfg’, ‘is’, ‘Best’, 1, 2, 3] 
# Explanation : All the keys before all the values in list. 

# Input : test_dict = {“Gfg” : 1, “Best” : 3} 
# Output : [‘Gfg’, ‘Best’, 1, 3] 
# Explanation : All the keys before all the values in list.

def pal(dicc:dict)->list:
    l=[]
    a,b=list(dicc.keys()),list(dicc.values())
    l=a+b
    print(l)

def shfhfgv(oo):
    return len(oo)

print(shfhfgv ({1,1,1,29,2,2,2,2,2}))

