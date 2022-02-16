output: main.o triangle.o face.o mesh.o meshfile.o
	g++ -o output main.o triangle.o face.o mesh.o meshfile.o

main.o: main.cpp
	g++ -c main.cpp

triangle.o: triangle.cpp triangle.h
	g++ -c triangle.cpp

face.o: face.cpp face.h
	g++ -c face.cpp

mesh.o: mesh.cpp mesh.h
	g++ -c mesh.cpp
	
meshfile.o: meshfile.cpp meshfile.h
	g++ -c meshfile.cpp

clean:
	rm *.o output