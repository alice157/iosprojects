all : lib recognizer.o
	$(CXX) -o test test.cpp -L. -lprotractor
lib :
	$(CXX) -fPIC -c recognizer.cpp -o recognizer.o
	$(CXX) -shared  -Wl,-soname,libprotractor.so -o libprotractor.so recognizer.o
clean :
	rm *.o test 2>/dev/null
