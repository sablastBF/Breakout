CFLAGS = -std=c++17 -I. -I include
LDFLAGS = -ldl -lglfw -L"/usr/lib" ./bin/linux-gcc-64/*.so -pthread -lfreetype


a.out: shaders/* *.c *.cpp *.hpp
	g++ $(CFLAGS) -o a.out *.c *.cpp  $(LDFLAGS)


.PHONY: test clean

test: a.out
	./a.out

clean:
	rm -f a.out