#include "lexer.h"

// C 언어 키워드 목록
const char *keywords[] = {
    "int", "return", "if", "else", "for", "while", "void",
    "char", "double", "float", "break", "continue", "struct"};

/**
 * @brief 주어진 단어가 C 언어 키워드인지 검사
 * @param word 검사할 문자열
 * @return 키워드이면 1, 아니면 0
 */
int is_keyword(const char *word)
{
    for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief 입력 파일에서 다음 토큰을 가져옴
 * @param source 입력 파일 포인터
 * @return 분석된 토큰
 */
Token get_next_token(FILE *source)
{
    Token token;
    int ch;

    // 공백 및 개행 문자 건너뛰기
    while ((ch = fgetc(source)) != EOF && isspace(ch))
        ;

    // 파일 끝(EOF) 처리
    if (ch == EOF)
    {
        token.type = TOKEN_EOF;
        strcpy(token.value, "EOF");
        return token;
    }

    // 숫자 토큰 처리 (정수)
    if (isdigit(ch))
    {
        token.type = TOKEN_NUMBER;
        int index = 0;
        do
        {
            token.value[index++] = ch;
            ch = fgetc(source);
        } while (isdigit(ch) && index < 63);
        token.value[index] = '\0';
        ungetc(ch, source);
        return token;
    }

    // 식별자(변수명 또는 키워드) 처리
    if (isalpha(ch) || ch == '_')
    {
        token.type = TOKEN_IDENTIFIER;
        int index = 0;
        do
        {
            token.value[index++] = ch;
            ch = fgetc(source);
        } while ((isalnum(ch) || ch == '_') && index < 63);
        token.value[index] = '\0';
        ungetc(ch, source);

        // 만약 키워드라면 키워드 토큰으로 변경
        if (is_keyword(token.value))
        {
            token.type = TOKEN_KEYWORD;
        }
        return token;
    }

    // 연산자 처리 (+, -, *, /, =, <, >)
    if (strchr("+-*/=<>", ch))
    {
        token.type = TOKEN_OPERATOR;
        token.value[0] = ch;
        token.value[1] = '\0';
        return token;
    }

    // 괄호 처리 ((), {})
    if (ch == '(' || ch == ')')
    {
        token.type = TOKEN_PAREN;
    }
    else if (ch == '{' || ch == '}')
    {
        token.type = TOKEN_BRACE;
    }
    else if (ch == ';')
    {
        token.type = TOKEN_SEMICOLON;
    }
    else
    {
        token.type = TOKEN_UNKNOWN;
    }
    token.value[0] = ch;
    token.value[1] = '\0';
    return token;
}

/**
 * @brief 토큰 정보를 출력하는 함수
 * @param token 출력할 토큰
 */
void print_token(Token token)
{
    // 토큰 타입을 문자열로 변환하여 가독성을 높임
    const char *token_names[] = {
        "EOF", "IDENTIFIER", "NUMBER", "OPERATOR", "PARENTHESIS",
        "BRACE", "SEMICOLON", "KEYWORD", "UNKNOWN"};

    // 토큰 유형과 값을 정렬하여 출력
    printf("Token Type: %-12s | Value: %s\n", token_names[token.type], token.value);
}