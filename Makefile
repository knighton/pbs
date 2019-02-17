all:
	rm -rf bin/ build/
	mkdir -p bin/ build/
	protoc `find src/ -type f -name "*.proto"` --cpp_out build/ \
		--proto_path src/
	clang++ src/string_func_test.cpp -Iinclude/ -Ibuild/ -O2 -std=c++11 \
		-lprotobuf -lpthread `find build/ -type f -name "*.cc"` -o bin/string_func_test
