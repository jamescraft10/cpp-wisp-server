all:
	g++ -o build/main src/main.cpp -lcurl
	build/main