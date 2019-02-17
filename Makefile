COMMON = \
	-Iinclude/ \
	-O2 \
	-std=c++11 \
	-Wall \
	-Werror \
	-Weverything \
	-Wextra \
	-Wno-covered-switch-default \

PROTOBUF = \
	-Ibuild/ \
	`find build/ -type f -name "*.cc"` \
	-lprotobuf \
	-lpthread \
	-Wno-c++98-compat \
	-Wno-global-constructors \
	-Wno-missing-prototypes \
	-Wno-missing-variable-declarations \
	-Wno-padded \
	-Wno-zero-as-null-pointer-constant \

all:
	rm -rf bin/ build/
	mkdir -p bin/ build/
	protoc `find src/ -type f -name "*.proto"` --cpp_out build/ \
		--proto_path src/
	clang++ src/string_func_test.cpp $(COMMON) $(PROTOBUF) \
		-o bin/string_func_test
