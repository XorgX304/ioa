#!/usr/bin/env python
import os, subprocess

def runcommand(c):
  pipe = subprocess.Popen(c, shell=True,stdout=subprocess.PIPE, stderr=subprocess.PIPE,preexec_fn=os.setsid)
  
d = os.path.abspath(os.getcwd()).split('/wd')[0] + '/wd/wda/Resources/WebDriverAgent.bundle'
cd = os.path.abspath(os.getcwd()).split('/wd')[0] + '/wd/wda'

os.chdir(os.path.abspath(cd))

commands = ['bash Scripts/bootstrap.sh -d', 'mkdir -p XXX']

for cmd in commands:
  runcommand(cmd.replace('XXX',os.path.abspath(d)))
  
exit(0)
