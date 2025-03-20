#include "lexer.h"

// 🔹 Lexer 생성 함수
Lexer create_lexer(char *input)
{
    Lexer lexer;         // 새로운 Lexer 구조체 생성
    lexer.input = input; // 입력 문자열 저장
    lexer.position = 0;  // 시작 위치를 0으로 설정
    return lexer;        // 초기화된 Lexer 반환
}

// 🔹 다음 문자를 가져오는 함수 (한 글자씩 읽고 위치 이동)
char next_char(Lexer *lexer)
{
    if (lexer->position < strlen(lexer->input)) // 입력 문자열 범위 내인지 확인
    {
        return lexer->input[lexer->position++]; // 현재 문자를 반환 후 위치 증가
    }
    return '\0'; // 문자열 끝(EOF)인 경우 NULL 문자 반환
}

// 🔹 현재 위치의 다음 문자를 확인하는 함수 (소비하지 않음)
char peek_char(Lexer *lexer)
{
    if (lexer->position < strlen(lexer->input)) // 입력 문자열 범위 내인지 확인
    {
        return lexer->input[lexer->position]; // 현재 위치의 문자 반환 (소비하지 않음)
    }
    return '\0'; // 문자열 끝(EOF)인 경우 NULL 문자 반환
}
