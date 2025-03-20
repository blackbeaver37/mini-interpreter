#include "parser.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Token current_token; // 현재 처리 중인 토큰
FILE *source_file;   // 입력 파일

/**
 * @brief 다음 토큰을 가져오는 함수
 */
void next_token()
{
    current_token = get_next_token(source_file);
}

/**
 * @brief 숫자 노드를 생성하는 함수
 * @return AST 노드 포인터
 */
ASTNode *parse_number()
{
    ASTNode *node = create_node(NODE_NUMBER, current_token.value);
    next_token(); // 다음 토큰으로 이동
    return node;
}

/**
 * @brief 변수 노드를 생성하는 함수
 * @return AST 노드 포인터
 */
ASTNode *parse_identifier()
{
    ASTNode *node = create_node(NODE_IDENTIFIER, current_token.value);
    next_token(); // 다음 토큰으로 이동
    return node;
}

/**
 * @brief 연산자를 처리하는 함수
 * @return AST 노드 포인터
 */
ASTNode *parse_expression()
{
    ASTNode *left = parse_number(); // 첫 번째 숫자 가져오기

    while (current_token.type == TOKEN_OPERATOR)
    {
        char op[2] = {current_token.value[0], '\0'};
        next_token();                    // 연산자 다음 토큰으로 이동
        ASTNode *right = parse_number(); // 두 번째 숫자 가져오기
        left = create_binary_op_node(op, left, right);
    }

    return left;
}

/**
 * @brief 변수 할당을 처리하는 함수
 * @return AST 노드 포인터
 */
ASTNode *parse_assignment()
{
    ASTNode *identifier = parse_identifier(); // 변수 이름 가져오기

    if (current_token.type == TOKEN_OPERATOR && strcmp(current_token.value, "=") == 0)
    {
        next_token();                       // '=' 건너뛰기
        ASTNode *expr = parse_expression(); // 표현식 파싱
        return create_assignment_node(identifier->value, expr);
    }

    return identifier;
}

/**
 * @brief return 문을 처리하는 함수
 * @return AST 노드 포인터
 */
ASTNode *parse_return()
{
    next_token(); // "return" 건너뛰기
    ASTNode *expr = parse_expression();
    return create_return_node(expr);
}

/**
 * @brief 전체 프로그램을 파싱하는 함수
 * @return AST 루트 노드
 */
ASTNode *parse_program(FILE *file)
{
    source_file = file;
    next_token(); // 첫 번째 토큰 가져오기

    ASTNode *root = NULL;

    while (current_token.type != TOKEN_EOF)
    {
        if (current_token.type == TOKEN_KEYWORD && strcmp(current_token.value, "return") == 0)
        {
            root = parse_return();
        }
        else
        {
            root = parse_assignment();
        }

        if (current_token.type == TOKEN_SEMICOLON)
        {
            next_token(); // ';' 건너뛰기
        }
    }

    return root;
}

/**
 * @brief AST 노드를 생성하는 함수
 */
ASTNode *create_node(NodeType type, const char *value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    strcpy(node->value, value);
    node->left = node->right = NULL;
    return node;
}