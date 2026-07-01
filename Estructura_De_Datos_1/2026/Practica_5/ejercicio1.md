

**f(X) = X mod 11**

## Inserción de elementos


| Elemento | Cálculo | Resultado | Estado |
|----------|---------|-----------|--------|
| 10 | 10 mod 11 | = 10 | ✓ Insertado en posición 10 |
| 20 | 20 mod 11 | = 9 | ✓ Insertado en posición 9 |
| 15 | 15 mod 11 | = 4 | ✓ Insertado en posición 4 |
| 25 | 25 mod 11 | = 3 | ✓ Insertado en posición 3 |
| 30 | 30 mod 11 | = 8 | ✓ Insertado en posición 8 |

##### Inserción de 3 (requiere Linear Probing):
- **3 mod 11 = 3** → Posición 3 **ocupada**
- Linear Probing: h₂(3) = (3+1) mod 11 = 4 → Posición 4 **ocupada**
- Linear Probing: h₃(4) = (4+1) mod 11 = 5 → **Libre** ✓ Insertado en posición 5


| Elemento | Cálculo | Resultado | Estado |
|----------|---------|-----------|--------|
| 18 | 18 mod 11 | = 7 | ✓ Insertado en posición 7 |

##### Inserción de 19 (requiere Linear Probing):
- **19 mod 11 = 8** → Posición 8 **ocupada**
- Linear Probing: h₂(8) = (8+1) mod 11 = 9 → Posición 9 **ocupada**
- Linear Probing: h₃(9) = (9+1) mod 11 = 10 → Posición 10 **ocupada**
- Linear Probing: h₄(10) = (10+1) mod 11 = 0 → **Libre** ✓ Insertado en posición 0

## Tabla Hash Final

| Posición | Elemento |
|----------|----------|
| 00 | 19 |
| 01 | — |
| 02 | — |
| 03 | 25 |
| 04 | 15 |
| 05 | 3 |
| 06 | — |
| 07 | 18 |
| 08 | 30 |
| 09 | 20 |
| 10 | 10 |