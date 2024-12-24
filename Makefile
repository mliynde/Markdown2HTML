# Makefile for USTCCSExp_Md2HTML project

# 编译器
CC = gcc

# 编译选项
CFLAGS = -I./include -Wall -Wextra -std=c11

# 目标文件
TARGET = md2html

# 源文件
SRCS = src/main.c src/convert.c src/m2h_utils.c src/gettime.c styles.c

# 目标文件
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 编译源文件生成目标文件
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
    rm -f $(OBJS) $(TARGET)

# 伪目标
.PHONY: all clean