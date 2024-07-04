all:
	g++ -o build/server src/server.cpp -Iinclude -lpthread
	build/server
	rm build/server

build:
	g++ -o build/server src/server.cpp -O3