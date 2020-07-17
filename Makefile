ifeq ($(shell uname -s),Darwin)
	OUT := prebuilds/darwin-x64
else
	OUT := prebuilds/linux-x64
endif

$(OUT): helper.c
	$(CC) helper.c -Os -o $(OUT)
