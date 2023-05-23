/* semaphore.c --- simple illustration of dijkstra's semaphore analogy
 *
 *   We fork() a  child process so that we have two processes running:
 *   Each process communicates via a semaphore.
 *   The respective process can only do its work (not much here)
 *   When it notices that the semaphore track is free when it returns to 0
 *   Each process must modify the semaphore accordingly
 */
 
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <sys/sem.h>
 
 union semun {
               int val;
               struct semid_ds *buf;
               ushort *array;
          };

main()
{ int i,j; 
  int pid;
  int semid; /* semid of semaphore set */
  key_t key = 1234; /* key to pass to semget() */
  int semflg = IPC_CREAT | 0666; /* semflg to pass to semget() */
  int nsems = 1; /* nsems to pass to semget() */
  int nsops; /* number of operations to do */
  struct sembuf *sops = (struct sembuf *) malloc(2*sizeof(struct sembuf)); 
  /* ptr to operations to perform */

  /* set up semaphore */
  
  (void) fprintf(stderr, "\nsemget: Setting up seamaphore: semget(%#lx, %\
%#o)\n",key, nsems, semflg);
   if ((semid = semget(key, nsems, semflg)) == -1) {
	perror("semget: semget failed");
	exit(1);
      } else 
	(void) fprintf(stderr, "semget: semget succeeded: semid =\
%d\n", semid);


  /* get child process */
  
   if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    
if (pid == 0)
     { /* child */
       i = 0;
       
       
       while (i  < 3) {/* allow for 3 semaphore sets */
       
       nsops = 2;
       
       /* wait for semaphore to reach zero */
       
       sops[0].sem_num = 0; /* We only use one track */
       sops[0].sem_op = 0; /* wait for semaphore flag to become zero */
       sops[0].sem_flg = SEM_UNDO; /* take off semaphore asynchronous  */
       
       
       sops[1].sem_num = 0;
       sops[1].sem_op = 1; /* increment semaphore -- take control of track */
       sops[1].sem_flg = SEM_UNDO | IPC_NOWAIT; /* take off semaphore */
       
       /* Recap the call to be made. */
       
       (void) fprintf(stderr,"\nsemop:Child  Calling semop(%d, &sops, %d) with:", semid, nsops);
       for (j = 0; j < nsops; j++)
	{
	  (void) fprintf(stderr, "\n\tsops[%d].sem_num = %d, ", j, sops[j].sem_num);
	  (void) fprintf(stderr, "sem_op = %d, ", sops[j].sem_op);
	  (void) fprintf(stderr, "sem_flg = %#o\n", sops[j].sem_flg);
	}
	
       /* Make the semop() call and report the results. */
	if ((j = semop(semid, sops, nsops)) == -1) {
		perror("semop: semop failed");
		} 
	   else 
             {
		(void) fprintf(stderr, "\tsemop: semop returned %d\n", j);
	
		(void) fprintf(stderr, "\n\nChild Process Taking Control of Track: %d/3 times\n", i+1);
		sleep(5); /* DO Nothing for 5 seconds */

      		 nsops = 1;
       
       		/* wait for semaphore to reach zero */
       		sops[0].sem_num = 0;
                sops[0].sem_op = -1; /* Give UP COntrol of track */
       		sops[0].sem_flg = SEM_UNDO | IPC_NOWAIT; /* take off semaphore, asynchronous  */
       
       	      	
       	      	if ((j = semop(semid, sops, nsops)) == -1) {
			perror("semop: semop failed");
			} 
		   else
		      (void) fprintf(stderr, "Child Process Giving up Control of Track: %d/3 times\n", i+1);
       	      	sleep(5); /* halt process to allow parent to catch semaphor change first */
       	      }
        ++i;
      }
       
     }
  else /* parent */
     {  /* pid hold id of child */
        
        i = 0;
       
       
       while (i  < 3) { /* allow for 3 semaphore sets */
       
       nsops = 2;
       
       /* wait for semaphore to reach zero */
       sops[0].sem_num = 0;
       sops[0].sem_op = 0; /* wait for semaphore flag to become zero */
       sops[0].sem_flg = SEM_UNDO; /* take off semaphore asynchronous  */
       
       
       sops[1].sem_num = 0;
       sops[1].sem_op = 1; /* increment semaphore -- take control of track */
       sops[1].sem_flg = SEM_UNDO | IPC_NOWAIT; /* take off semaphore */
       
       /* Recap the call to be made. */
       
       (void) fprintf(stderr,"\nsemop:Parent Calling semop(%d, &sops, %d) with:", semid, nsops);
       for (j = 0; j < nsops; j++)
	{
	  (void) fprintf(stderr, "\n\tsops[%d].sem_num = %d, ", j, sops[j].sem_num);
	  (void) fprintf(stderr, "sem_op = %d, ", sops[j].sem_op);
	  (void) fprintf(stderr, "sem_flg = %#o\n", sops[j].sem_flg);
	}
	
       /* Make the semop() call and report the results. */
	if ((j = semop(semid, sops, nsops)) == -1) {
		perror("semop: semop failed");
		} 
	   else 
             {
		(void) fprintf(stderr, "semop: semop returned %d\n", j);
	
		(void) fprintf(stderr, "Parent Process Taking Control of Track: %d/3 times\n", i+1);
		sleep(5); /* Do nothing for 5 seconds */

      		 nsops = 1;
       
       		/* wait for semaphore to reach zero */
       		sops[0].sem_num = 0;
                sops[0].sem_op = -1; /* Give UP COntrol of track */
       		sops[0].sem_flg = SEM_UNDO | IPC_NOWAIT; /* take off semaphore, asynchronous  */
       
       		if ((j = semop(semid, sops, nsops)) == -1) {
			perror("semop: semop failed");
			} 
		   else
		      (void) fprintf(stderr, "Parent Process Giving up Control of Track: %d/3 times\n", i+1);
       	      	sleep(5); /* halt process to allow child to catch semaphor change first */
       	      }
        ++i;
        
      }
       
     }
}
