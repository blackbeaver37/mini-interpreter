#include "lexer.h"

int main()
{
    char *code = "int x = 10 + 5;";   // 테스트할 소스 코드
    Lexer lexer = create_lexer(code); // Lexer 생성

    // 🔹 next_char() 테스트
    printf("Next char: %c\n", next_char(&lexer)); // 'i' 출력
    printf("Next char: %c\n", next_char(&lexer)); // 'n' 출력
    printf("Next char: %c\n", next_char(&lexer)); // 't' 출력

    // 🔹 peek_char() 테스트
    printf("Peek char: %c\n", peek_char(&lexer)); // ' ' (공백 문자)

    return 0;
}
