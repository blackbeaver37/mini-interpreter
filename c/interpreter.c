#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 간단한 변수 저장소
typedef struct
{
    char name[64];
    int value;
} Variable;

Variable variables[100]; // 최대 100개의 변수를 저장할 수 있음
int var_count = 0;       // 현재 변수 개수

/**
 * @brief 변수 값을 저장하는 함수
 * @param name 변수 이름
 * @param value 저장할 값
 */
void set_variable(const char *name, int value)
{
    for (int i = 0; i < var_count; i++)
    {
        if (strcmp(variables[i].name, name) == 0)
        {
            variables[i].value = value;
            return;
        }
    }
    // 새로운 변수 추가
    strcpy(variables[var_count].name, name);
    variables[var_count].value = value;
    var_count++;
}

/**
 * @brief 변수 값을 가져오는 함수
 * @param name 변수 이름
 * @return 변수의 값
 */
int get_variable(const char *name)
{
    for (int i = 0; i < var_count; i++)
    {
        if (strcmp(variables[i].name, name) == 0)
        {
            return variables[i].value;
        }
    }
    printf("Error: Undefined variable %s\n", name);
    exit(1);
}

/**
 * @brief AST를 실행하는 함수
 * @param node 실행할 AST 노드
 * @return 실행 결과 (최종 반환값)
 */
int interpret(ASTNode *node)
{
    if (!node)
        return 0;

    switch (node->type)
    {
    case NODE_NUMBER:
        return atoi(node->value); // 숫자 노드 → 정수 변환 후 반환

    case NODE_IDENTIFIER:
        return get_variable(node->value); // 변수 노드 → 저장된 변수 값 반환

    case NODE_BINARY_OP:
    {
        int left_value = interpret(node->left);
        int right_value = interpret(node->right);

        if (strcmp(node->value, "+") == 0)
            return left_value + right_value;
        if (strcmp(node->value, "-") == 0)
            return left_value - right_value;
        if (strcmp(node->value, "*") == 0)
            return left_value * right_value;
        if (strcmp(node->value, "/") == 0)
        {
            if (right_value == 0)
            {
                printf("Error: Division by zero\n");
                exit(1);
            }
            return left_value / right_value;
        }

        printf("Error: Unknown operator %s\n", node->value);
        exit(1);
    }

    case NODE_ASSIGN:
        // 변수 할당 → 오른쪽 값 계산 후 저장
        set_variable(node->value, interpret(node->right));
        return get_variable(node->value);

    case NODE_RETURN:
        return interpret(node->right); // return 문 → 오른쪽 값 반환

    default:
        printf("Error: Unknown AST node type\n");
        exit(1);
    }
}
