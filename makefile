objs = hw2.o
flags+=-c -Wall -g
all:$(objs)
	gcc $^ -o $@
%.o:%.c
	gcc $^ $(flags) -o $@

clean: 
	rm *.o all -f
