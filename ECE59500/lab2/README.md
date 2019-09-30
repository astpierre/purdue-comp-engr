# [ECE595 Programming Project 2](https://engineering.purdue.edu/~ece595/labs_2018/lab2.html)

### Team members: Andrew St. Pierre + Eli Kern
### Date due: Sunday, September 23, 2018  


## Description
> The purpose of this lab is to become familiar with the problems of process synchronization and their solutions using OS-provided synchronization primitives. In particular, you will solve the classic producer-consumer problem using the following different combinations of synchronization primitives: locks, semaphores, and locks with conditional variables.  
> In addition to solving the producer-consumer problem, you will also implement one of the synchronization primitives inside the OS. In particular, for this lab, we will provide you with the implementation code for semaphores and locks in synch.c and synch.h, and you need to write the code to implement condition variables in synch.c and synch.h.  


## Getting started
1. Enter the lab2 directory.  
	``` $ cd  ~/ece595/lab2```
2. First we will compile the OS. This is made easy by make.  
	``` $ cd os/```  
	``` $ make```
3. Next, we will compile the user program. (NOTE: subdir of apps dependent on desired program)  
	``` $ cd  ~/ece595/lab2```  
	``` $ cd apps/<q1,q3,q4,q5>/```  
	``` $ make```  
4. Now we will run the program. (NOTE: subdir of apps dependent on desired program)  
	``` $ cd  ~/ece595/lab2/apps/<q1,q3,q4,q5>/```  
	``` $ make run```


## References
1. DLX Instruction Set
2. The DLX Architecture
3. The DLX Operating System (DLXOS) Design


## END README
