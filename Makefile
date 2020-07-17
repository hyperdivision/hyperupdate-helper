ifeq ($(shell uname -s),Darwin)
	OUT := bin/darwin-x64
else
	OUT := bin/linux-x64
endif

$(OUT): helper.c
	$(CC) helper.c -Os -o $(OUT)
