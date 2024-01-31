#ifndef __SMTASK_H__
#define __SMTASK_H__

struct SMTask {
	signed char state; 		//Task's current state
	unsigned long period; 		//Task period
	unsigned long elapsedTime; 	//Time elapsed since last task tick
	int (*TickFct)(int); 		//Task tick function
};

#endif
