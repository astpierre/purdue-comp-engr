# [ECE595 Programming Project 1](https://engineering.purdue.edu/~ece595/labs_2018/lab1.html)

### Student: Andrew St. Pierre  
### PUID: 0027901932  
### Date: Thursday, August 30, 2018  

## Description
> This first project first sets up the DLXOS directory structure and dev environment on an ECN Linux machine. Then, a new user trap called "Getpid" is implemented. This trap returns an integer representing the ID of the current process. When DLXOS is run on the hardware simulator, the integer PID is printed.

## Getting started
1. Enter the lab1 directory.  
	``` $ cd  ~/ece595/lab1```
2. First we will compile the OS. This is made easy by make.  
	``` $ cd os/```  
	``` $ make```
3. Next, we will compile the user program. This is made easy by make.  
	``` $ cd  ~/ece595/lab1```  
	``` $ cd apps/```  
	``` $ make```  
4. Now we will run the program.  
	``` $ cd  ~/ece595/lab1```  
	``` $ dlxsim -x ~/ece595/lab1/os/work/os.dlx.obj -a -u ~/ece595/lab1/apps/work/userprog.dlx.obj```

## Expected
The last three printed lines upon execution of the program should be:  
``` Hello World!```  
``` LAB01: Implementing User Trap Getpid()```  
``` PID: 31```  

## References
1. DLX Instruction Set
2. The DLX Architecture
3. The DLX Operating System (DLXOS) Design


## END README

