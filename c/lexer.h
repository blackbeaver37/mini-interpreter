#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 🔹 토큰 타입 정의
typedef enum
{
    TOKEN_INT,        // 'int' 키워드
    TOKEN_IDENTIFIER, // 변수 이름 (예: x, y)
    TOKEN_NUMBER,     // 숫자 (예: 10, 42)
    TOKEN_ASSIGN,     // '=' (할당 연산자)
    TOKEN_PLUS,       // '+' (더하기 연산자)
    TOKEN_MINUS,      // '-' (빼기 연산자)
    TOKEN_TIMES,      // '*' (곱하기 연산자)
    TOKEN_DIVIDE,     // '/' (나누기 연산자)
    TOKEN_SEMICOLON,  // ';' (문장 종료)
    TOKEN_EOF         // 파일 끝 (End of File)
} TokenType;

// 🔹 토큰 구조체 정의
typedef struct
{
    TokenType type; // 토큰 타입
    char *value;    // 실제 문자열 값
} Token;

// 🔹 Lexer 구조체 정의
typedef struct
{
    char *input;  // 입력 코드
    int position; // 현재 읽고 있는 위치
} Lexer;

// 🔹 함수 선언
Lexer create_lexer(char *input);
Token get_next_token(Lexer *lexer);
void print_token(Token token);

#endif
