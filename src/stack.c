#include "stack.h"

void SetTop (Stack *S, Node *NewTop )

{
	S->Top = NewTop;
}

void CreateEmpty (Stack *S)
{
	S->Top = NULL;
}

bool IsEmpty (Stack S)
{
	return (S.Top == NULL);
}

void Push (Stack *S, infotype X)
{
	List l;
	l.First = S->Top;

	InsVFirst(&l, X);
	S->Top = l.First;
}


void Pop (Stack *S, infotype *X)
{
	List l;
	address popped;
	l.First = S->Top;
	DelFirst(&l, &popped);
	*X = popped->info;
	S->Top = l.First;
	
}

