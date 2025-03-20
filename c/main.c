#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 메인 함수 - AST 실행 및 결과 출력
 * @return 실행 결과 (0: 성공, 1: 실패)
 */
int main(int argc, char *argv[])
{
    // 사용자가 파일명을 입력하지 않은 경우 오류 출력
    if (argc < 2)
    {
        printf("Usage: %s <source_filename>\n", argv[0]);
        return 1;
    }

    // 기본 경로 설정: ../test/
    char filepath[256] = "../test/";
    strcat(filepath, argv[1]); // 파일명을 기본 경로에 추가

    // 입력 파일 열기
    FILE *source = fopen(filepath, "r");
    if (!source)
    {
        perror("Failed to open file");
        return 1;
    }

    printf("Processing file: %s\n", filepath);

    // **✅ 1. Lexer 실행 → 토큰 분석**
    printf("\nStarting Lexical Analysis...\n");
    Token token;
    do
    {
        token = get_next_token(source);
        print_token(token);
    } while (token.type != TOKEN_EOF);

    // **✅ 2. Parser 실행 → AST 생성**
    rewind(source); // 파일을 다시 처음으로 되돌림
    printf("\nParsing Program...\n");
    ASTNode *root = parse_program(source);

    // **✅ 3. AST 출력**
    printf("\nAbstract Syntax Tree (AST):\n");
    print_ast(root, 0);

    // **✅ 4. AST 실행**
    printf("\nExecuting AST...\n");
    int result = interpret(root);
    printf("Execution Result: %d\n", result);

    // **✅ 5. 메모리 정리**
    free_ast(root);
    fclose(source);

    return 0;
}
