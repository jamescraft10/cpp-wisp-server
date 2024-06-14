all:
	g++ -o build/server src/server.cpp -lssl -lcrypto -Iusr/include/openssl
	build/server