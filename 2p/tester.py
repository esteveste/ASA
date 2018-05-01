try:
    import matplotlib.pyplot as plt
    import seaborn as sns
    import numpy as np
    import tqdm
    import numpy.polynomial.polynomial as poly
except:
    import os
    print("\033[0;32m Installing needed packages \033[0m")
    install = "pip install numpy seaborn tqdm"
    print("\033[1;33m Running: {} \033[0m".format(install))
    os.system(install)
    print("\033[1;32m Please re-run the script\033[0m")
    exit(0)


import os
import subprocess
import sys
import time
from subprocess import Popen, PIPE

NR_TESTES=20
PASSOS=10

# Complexidade linha
# GRAU_MODO1=3
GRAU_MODO2=1

RED='\033[0;31m'
LRED='\033[1;31m'
BLUE='\033[0;34m'
LBLUE='\033[1;34m'
LGREEN="\033[1;32m"
LYELLOW='\033[1;33m'
NC='\033[0m'

def main(p):
    x = np.arange(2,NR_TESTES*PASSOS+1,PASSOS)
    x2=(x*2+1)*(x*2)
    print(f"\n{LBLUE} Nr of vertices",x2,f"{NC}")

    y1=np.zeros(NR_TESTES)
    y2=np.zeros(NR_TESTES)

    plt.suptitle('2 Projecto ASA', fontsize=16)
    plt.xlabel('N Vertices')
    plt.ylabel('Tempo em segundos')

    print(f"{LGREEN}Mode 1{NC}")
    # mode 1
    for i,n in enumerate(x):

        time.sleep(0.1)
        
        t0 = time.time()
        Popen(f"./gera {n} 0 | ./{p} > /dev/null", shell=True).communicate()
        t0= time.time() - t0

        time.sleep(0.1)

        t1 = time.time()
        Popen(f"./gera {n} 1 | ./{p} > /dev/null", shell=True).communicate()
        t1= time.time() - t1

        tavg = (t1+t0)/2

        print(f"n={n} took average {tavg} seconds, differance of {(t1-t0)}")
        y1[i]=tavg
    
    print(f"{LGREEN}Mode 2{NC}")

    # mode 2
    for i,n in enumerate(x):
        t0 = time.time()
        Popen(f"./gera {n} 2 | ./{p} > /dev/null", shell=True).communicate()
        t0= time.time() - t0

        time.sleep(0.1)

        t1 = time.time()
        Popen(f"./gera {n} 3 | ./{p} > /dev/null", shell=True).communicate()
        t1= time.time() - t1

        tavg = (t1+t0)/2

        print(f"n={n} took average {tavg} seconds, differance of {(t1-t0)}")
        y2[i]=tavg
    
    y = (y1+y2)/2

    f = plt.figure(1)
    l1,=plt.plot(x2,y1,sns.xkcd_rgb["blue"], linewidth=2)

    #curva n^2
    print("Curva N")
    coefs = poly.polyfit(x2, y1, [1,0])
    print(coefs)
    ffit1 = poly.polyval(x2, coefs)
    print("mse:{}".format(np.sum((y1-ffit1)**2)))
    # pline1,=plt.plot(x2,ffit1,sns.xkcd_rgb["black"],linestyle='-.',alpha=0.5)


    print("Curva N^2")
    coefs = poly.polyfit(x2, y1, [2,0])
    print(coefs)
    ffit2 = poly.polyval(x2, coefs)
    print("mse:{}".format(np.sum((y1-ffit2)**2)))
    # pline2,=plt.plot(x2,ffit2,sns.xkcd_rgb["red"],linestyle='-.',alpha=0.5)

    print("Curva N^3")
    coefs = poly.polyfit(x2, y1, [3,0])
    print(coefs)
    ffit3 = poly.polyval(x2, coefs)
    print("mse:{}".format(np.sum((y1-ffit3)**2)))
    
    ffit = np.array([ffit1,ffit2,ffit3])
    i = np.argmin([np.sum((y1-ffit1)**2),np.sum((y1-ffit2)**2),np.sum((y1-ffit3)**2)])
    print(f"{LYELLOW}N^{i+1} Choosed{NC}")

    pline,=plt.plot(x2,ffit[i],sns.xkcd_rgb["green"],linestyle='-.',alpha=0.5)

    plt.legend([l1,pline], ['Gerador Modo 1',f"N^{i+1}"])
    plt.show()

    g = plt.figure(2)
    l2,=plt.plot(x2,y2,sns.xkcd_rgb["red"], linewidth=2)

    coefs = poly.polyfit(x2, y2, [GRAU_MODO2,0])
    print(coefs)
    ffit = poly.polyval(x2, coefs)
    pline,=plt.plot(x2,ffit,sns.xkcd_rgb["black"],linestyle='-.',alpha=0.5)

    plt.legend([l2,pline], ['Gerador Modo 2',"N"])
    plt.show()

if __name__=="__main__":
    print(f"{LYELLOW}2 Projecto ASA{NC}")
    if(len(sys.argv)<2):
        print("\nGive me your project filename (example: proj)")
        exit(0)
    elif(os.path.exists(sys.argv[1])):
        main(sys.argv[1])
    else:
        print(f"\n{LRED}Filename '{sys.argv[1]}' not found{NC}")
    