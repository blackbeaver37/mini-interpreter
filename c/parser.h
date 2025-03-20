#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

/**
 * @brief AST(추상 구문 트리)에서 사용될 노드 유형
 */
typedef enum
{
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_BINARY_OP,
    NODE_ASSIGN,
    NODE_RETURN
} NodeType;

/**
 * @struct ASTNode
 * @brief AST(추상 구문 트리) 노드 구조체
 */
typedef struct ASTNode
{
    NodeType type;
    char value[64];
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

/**
 * @brief AST 노드를 생성하는 함수
 */
ASTNode *create_node(NodeType type, const char *value);
ASTNode *create_assignment_node(const char *identifier, ASTNode *expr);
ASTNode *create_binary_op_node(const char *op, ASTNode *left, ASTNode *right);
ASTNode *create_return_node(ASTNode *expr);

/**
 * @brief AST 출력 및 해제 함수
 */
void print_ast(ASTNode *node, int depth);
void free_ast(ASTNode *node);

/**
 * @brief 프로그램을 파싱하는 함수 (Parser)
 * @param file 소스 파일 포인터
 * @return AST 루트 노드 포인터
 */
ASTNode *parse_program(FILE *file);

#endif // PARSER_H
