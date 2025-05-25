#ifndef stack_H
#define stack_H
#include "linked.h"
#include <stdbool.h>
#include "player.h"

void SetTop (Stack *S, Node *NewTop );

void CreateEmpty (Stack *S);

bool IsEmpty (Stack S);

void Push (Stack *S, infotype X);

void Pop (Stack *S, infotype *X);

/*
    IS: Stack ada
    FS: Stack hancur boyyyy

    Creator: 
*/
void destroy_stack(Stack *S);



#endif

