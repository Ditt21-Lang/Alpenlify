#include "stack.h"

void SetTop (Stack *S, Stack NewTop )

{
	*S = NewTop;
}

void CreateEmpty (Stack *S)
{
	*S = NULL;
}

bool IsEmpty (Stack S)
{
	return (S == NULL);
}

void Push (Stack *S, infotype X)
{
	List l;
	l.First = *S;

	InsVFirst(&l, X);
	*S = l.First;
}


void Pop (Stack *S, infotype *X)
{
	List l;
	address popped;
	l.First = *S;
	DelFirst(&l, &popped);
	*X = popped->info;
	*S = l.First;
	
}

