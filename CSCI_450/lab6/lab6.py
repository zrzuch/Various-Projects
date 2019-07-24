from z3 import *
"""

people = Int('people')
committees = Int('committees')




x = Int('x')
y = Int('y')
z = Int('z')
s = z3.Solver()
s.push()
s.add(x == 1, y >= 0, z >= 0, x != y, x != z)
if s.check() == z3.sat:
	print ("Satisfiable!")
	print ("Here is the model: ", s.model())
s.pop()
"""
"""
(p V q) ^ ~(p ^ q) == XOR
"""


n = 5
m = 2
people = [[1, 2], [1, 3]]


a = Int('a')
b = Int('b')
c = Int('c')
d = Int('d')
e = Int('e')
f = Int('f')
X = [[Int("x_%s_%s" % (a+1, b+1)) for a in range(n)] for b in range(m)]
"""
assign = Function('assign', )
"""
solve(X[a][b] == people[c][d], X[e][f] == people[c][d+1], a != e)