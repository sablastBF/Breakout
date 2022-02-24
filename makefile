CFLAGS = -std=c++17 -I. -I include
LDFLAGS = -ldl -lglfw -lassimp

a.out: shaders/* *.c *.cpp 
	g++ $(CFLAGS) -o a.out *.c *.cpp  $(LDFLAGS)


.PHONY: test clean

test: a.out
	./a.out

clean:
	rm -f a.out