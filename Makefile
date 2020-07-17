ifeq ($(shell uname -s),Darwin)
	OUT := bin/darwin
else
	OUT := bin/linux
endif

$(OUT): helper.c
	$(CC) helper.c -Os -o $(OUT)
