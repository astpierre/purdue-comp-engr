# Q3 NOTES

## TASK
> Repeat Problem 1 using semaphores and locks, rather than locks alone.   
> In other words, neither the producer nor the consumer need to check the empty/full conditions since the semaphores will handle this internally.   


## Hint
> You will need two semaphores...  
1. one named "s_fullslots" that indicates the number of full slots in the buffer  
2. one named "s_emptyslots" that indicates the number of empty slots in the buffer  

## END README
