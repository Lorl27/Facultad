import pytest

def fmaximo(x:int, y:int)-> int:
    if x > y:
        return x
    else:
        return y

def test_fmaximo():
    assert fmaximo(3,4) == 4
    assert fmaximo(-4,92) == 92
    assert fmaximo(-10,2) == 2
    assert fmaximo(-5,72) == 72
    assert fmaximo(-5,72) == -5
    
test_fmaximo()

