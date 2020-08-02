build:
	g++ -w -std=c++14 \
	./*.cpp \
	-o bin/space_snake \
	-lSDL2 \

clean:
	rm ./bin/space_snake;

run:
	./bin/space_snake;
