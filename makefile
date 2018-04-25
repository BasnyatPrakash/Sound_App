OBJ = main.o screen.o sound.o
APPNAME = soundApp

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

%.o : %.c
	gcc -c -o $@ $<

clean : 
	rm $(OBJ) $(APPNAME)
	
due : 
	tar -cvf sound.tar *.c *.h makefile README.txt 
	
	
	

