#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>  // 파일 입출력
#include <stdlib.h> // 메모리 할당 및 표준 라이브러리 함수
#include <ctype.h>  // 문자 판별 함수 (isdigit, isalpha 등)
#include <string.h> // 문자열 처리 함수

/**
 * @enum TokenType
 * @brief C 언어의 다양한 토큰을 표현
 */
typedef enum
{
    TOKEN_EOF,        // 파일 끝
    TOKEN_IDENTIFIER, // 변수명 또는 키워드
    TOKEN_NUMBER,     // 숫자
    TOKEN_OPERATOR,   // 연산자 (+, -, *, / 등)
    TOKEN_PAREN,      // 괄호 (, )
    TOKEN_BRACE,      // 중괄호 { }
    TOKEN_SEMICOLON,  // 세미콜론 ;
    TOKEN_KEYWORD,    // C 키워드 (예: int, return)
    TOKEN_UNKNOWN     // 알 수 없는 토큰 (에러 처리용)
} TokenType;

/**
 * @struct Token
 * @brief 개별 토큰을 표현하는 구조체
 */
typedef struct
{
    TokenType type; // 토큰 유형
    char value[64]; // 토큰 값 (최대 64바이트 저장)
} Token;

// 함수 선언
Token get_next_token(FILE *source);
void print_token(Token token);
int is_keyword(const char *word);

#endif // LEXER_H
