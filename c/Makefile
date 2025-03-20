# 컴파일러 및 옵션 설정
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = interpreter

# 소스 파일 목록
SRCS = interpreter.c parser.c lexer.c main.c
OBJS = $(SRCS:.c=.o)

# 기본 실행 규칙
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 개별 소스 파일 컴파일 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 실행
run: $(TARGET)
	./$(TARGET) test.c

# 실행 (기본 경로에서 입력 파일 읽기)
test: $(TARGET)
	./$(TARGET) test.c

# 정리 (컴파일된 파일 제거)
clean:
	rm -f $(OBJS) $(TARGET)
