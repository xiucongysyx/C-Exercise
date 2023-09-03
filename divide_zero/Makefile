# 编译器
CC = gcc
# 编译选项
CFLAGS= -g -w
# 目标文件
TARGET = out 
# 源代码文件
SRCS =	*.c 
# 默认目标
default: $(TARGET)
# 目标文件生成规则
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^
# 清理目标文件和可执行文件
clean:
	rm $(TARGET) 

run:
	./$(TARGET)
