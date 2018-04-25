import subprocess
import matplotlib.pyplot as plt
import seaborn
import time

time.s

a = subprocess.getoutput("/usr/bin/time -v ./projV2 < 1.in > temp")
a=a.split("\n")
t = a[4].split(" ")[-1]
m = int(a[9].split(" ")[-1])
print(t,m)


