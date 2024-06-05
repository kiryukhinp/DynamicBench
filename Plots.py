import matplotlib.pyplot as plt
import os
os.chdir('build')
def WriteFromFile(filename):
    infile = open(filename, 'r')
    x = []
    y = []
    for line in infile:
        str = line.strip().split()
        #print(str)
        x.append(float(str[0]))
        y.append(float(str[1]))
    return (x,y)

t1 = []
n1 = []
t1 = WriteFromFile('W.txt')[0]
n1 = WriteFromFile('W.txt')[1]
t2 = WriteFromFile('../Data/Reference.txt')[0]
n2 = WriteFromFile('../Data/Reference.txt')[1]
plt.plot(t1,n1)
plt.plot(t2,n2)

plt.show()