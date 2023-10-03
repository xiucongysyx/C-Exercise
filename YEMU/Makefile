# 编译器
CC = gcc
# 编译选项
CFLAGS=-Wall -g
# 目标文件
TARGET = yemu
# 源代码文件
SRCS = yemu.c
# 默认目标
all:$(TARGET)
# 目标文件生成规则
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^
# 清理目标文件和可执行文件
clean:
	rm -f $(TARGET) 
