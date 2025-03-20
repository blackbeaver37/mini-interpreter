#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

/**
 * @brief AST를 실행하는 함수
 * @param node 실행할 AST 노드
 * @return 실행 결과 (최종 반환값)
 */
int interpret(ASTNode *node);

#endif // INTERPRETER_H
