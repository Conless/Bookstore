from random import *
mode = ["insert","delete","find"]

n = 80000
a = open("test1.txt","w")
a.write(str(n))
a.write("\n")
for i in range(n):
    m = randint(2,2)
    a.write(mode[m])
    a.write(" ")
    a.write(str(randint(1,1000)))
    a.write(" ")
    if m!= 2:
        a.write(str(randint(1,1000)))
    a.write("\n")
a.flush()
