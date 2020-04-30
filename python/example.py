#!/usr/bin/env python3
import numpy as np
#import scipy.linalg
from scipy import linalg
from scipy import optimize
from sympy import symbols, Eq, solve

p1 = 8.4e-6;
p2 = 6.6667e-4;
p2opp = 66667;
p3 = 1.7778e-5;
p3opp = 177780;
p5 = 2;

def x2(p4, x1):
    return (x1 * x1 + p2 * p4 * x1 - x1) / (p1 - x1)
def x3(p4, x1):
    return x1 / (1 + p4)

def det11(p4, x1):
    return - x2(p4, x1) * p2opp + 1 * p2opp - 2 * x1 * p2opp - p4
def det12(p4, x1):
    return p1 * p2opp - x1 * p2opp
def det13(p4, x1):
    return 0
def det21(p4, x1):
    return - x2(p4, x1) * p3opp
def det22(p4, x1):
    return - p1 * p3opp - x1 * p3opp - p4
def det23(p4, x1):
    return p5*p3opp
def det31(p4, x1):
    return 1
def det32(p4, x1):
    return 0
def det33(p4, x1):
    return - 1 - p4


def p6(p4, x1, x2, x3):
    return (p1 * x2 + x1 * x2 - p5 * x3) / (p3 * p4) + x2

def Jacoby(p4, x1):
    return ([[det11(p4,x1), det12(p4,x1), det13(p4,x1)],
    [det21(p4,x1), det22(p4,x1), det23(p4,x1)],
    [det31(p4,x1), det32(p4,x1), det33(p4,x1)]])

def det(a11, a12, a13, a21, a22, a23, a31, a32, a33):
    return  a11*a22*a33 + a12*a23*a31 + a21*a32*a13 - a13*a22*a31 - a12*a21*a33 - a23*a32*a11

def detJacoby(p4, x1):
    a11 = det11(p4, x1)
    a12 = det12(p4, x1)
    a13 = det13(p4, x1)
    a21 = det21(p4, x1)
    a22 = det22(p4, x1)
    a23 = det23(p4, x1)
    a31 = det31(p4, x1)
    a32 = det32(p4, x1)
    a33 = det33(p4, x1)
    return det(a11, a12, a13, a21, a22, a23, a31, a32, a33)

def equation(p4):
    def subsp4(x1):
        return detJacoby(p4, x1)
    return subsp4

#def equation(x1):
#    p4 = 10
#    return linalg.det([[det11(p4,x1), det12(p4,x1), det13(p4,x1)],
#    [det21(p4,x1), det22(p4,x1), det23(p4,x1)],
#    [det31(p4,x1), det32(p4,x1), det33(p4,x1)]])



guess = -1
result1 = optimize.fsolve(equation(10), guess)
print(result1)
guess = 1000
result2 = optimize.fsolve(equation(10), guess)
print(result2)

result1 += 1e-14
x2res = x2(10, result2)
x3res = x3(10, result2)
p6res = p6(10, result2, x2res, x3res)
print("x2 =", x2res)
print("x3 =",x3res)
print("p6 =", p6res)

#p6res = 926.7271
#result2 = 0.40566
#x2res = 0.587685
#x3res = 0.036878
p4 = 10

eq1 = (p1*x2res - result2*x2res + result2 - result2*result2) / p2 - p4*result2;
eq2 = (-p1*x2res - result2*x2res + p5*x3res)/p3 + p4 * (p6res - x2res);
eq3 = result2 - x3res - p4*x3res;
print("eq1 =", eq1)
print("eq2 =",eq2)
print("eq3 =", eq3)

result2 -= 1e-14


#print(equation(10)(result1))
#print(equation(10)(result2))

#guess = (result1 + result2)/2
#result = optimize.bisect(equation(10), result1, result2)
#print(result)

#print(result)
#print(detJacoby(10, -47408725584.60649))
#print(determinant(Jacoby(1)(2)))
#linalg.det(a)
