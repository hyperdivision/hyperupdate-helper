ifeq ($(shell uname -s),Darwin)
	OUT := bin/darwin
else
	OUT := bin/linux
endif

$(OUT): helper.c
	mkdir -p bin
	$(CC) helper.c -Os -o $(OUT)
