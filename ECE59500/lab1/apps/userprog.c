#include "usertraps.h"

void main (int x)
{
	Printf("Hello World!\n");
	Printf("LAB01: Implementing User Trap Getpid()\n");

	/*********************************************************
	 * Getpid() is a system call to the OS to print the 
	 * current process ID. 
	 ********************************************************/
	Getpid(); /* Show current process ID */

	
	while(1); // Use CTRL-C to exit the simulator
}
