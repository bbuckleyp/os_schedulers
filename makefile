default:
	gcc -g -std=gnu99 -o project1 -Wall -Wextra -Wno-unused-parameter TestFile8.c threads.c threads.h my_scheduler.c
clean:
	rm project1
