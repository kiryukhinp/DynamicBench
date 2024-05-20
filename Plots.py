import matplotlib.pyplot as plt
import os
os.chdir('build\Debug')
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

t = []
n1 = []
t = WriteFromFile('Test.txt')[0]
n1 = WriteFromFile('Test.txt')[1]
plt.plot(t,n1)

plt.show()