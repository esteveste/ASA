import os
import subprocess

NOME_EXECUTAVEL = "a.out"
in_file = "st0{}.in"
out_file = "st0{}.out"
file_output = "output"

for i in range(5):
    os.system("./{0} < {1} > {2}".format(NOME_EXECUTAVEL,in_file.format(i+1),file_output))
    r = os.system("diff {} {}".format(file_output,out_file.format(i+1)))
    if(r!=0):
        print("Error on: {}".format(in_file.format(i+1)))