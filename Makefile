CC = g++ -O3
CFLAGS = -std=c++11 -Wall -framework OpenGL -framework Cocoa
MKFLAGS = mkdir -p


All:  main.cpp
	$(CC) -c fssimplewindowobjc.m
	$(CC) -c yssimplesound_macosx_objc.m
	$(CC) $(CFLAGS) main.cpp ysglfontdata.cpp yssimplesound_macosx_cpp.cpp yssimplesound_macosx_objc.o yssimplesound.cpp yspng.cpp yspngenc.cpp fssimplewindowcpp.cpp fssimplewindowobjc.o -o exe.o
	$(MKFLAGS) exe.app/Contents/MacOS
	mv exe.o exe.app/Contents/MacOS/.
	exe.app/Contents/MacOS/exe.o
	
run:
	exe.app/Contents/MacOS/exe.o


clean:
	rm -f *.o
	rm -rf *.dSYM
	(cd traces; rm -f *~)

