#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


//return -1 if a has higher precedence
//1 if b does
//0 if tied
int compOp(char a, char b);

int main(int argc, char *argv[]){


	int expLength;//length of expression string
	int i,postIdx;
	char *post;//postfix string
	Stack *s;


	if(argc != 2){
		fprintf(stderr,"must type infix expression between ' '\n");
		return 0;
	}



	expLength = strlen(argv[1]);
	post = calloc(expLength+1, sizeof(char));
	if(post == NULL){
		perror("error allocating string");
		return 1;
	}
	s = init();

	

	postIdx = 0;

	for(i = 0; i < expLength; i++){

        if(argv[1][i] == ' ' || argv[1][i] == '\t'){
            continue;
        }

        // If operand, add to post
        if (isdigit(argv[1][i])) {
            post[postIdx++] = argv[1][i];
        } 
        else {
            // operator encountered
            while(!isEmpty(s) && compOp(argv[1][i], peek(s)) >= 0) {
                post[postIdx++] = pop(s);
            }
            push(s, argv[1][i]);
        }
    }

    // pop any remaining elements from the stack
    while(!isEmpty(s)) {
        post[postIdx++] = pop(s);
    }

	print("%s\n", post);


	destroy(s);


}




int compOp(char a, char b){
    int weightA;
    int weightB;

    switch(a) {
        case '-':
        case '+':
            weightA = 1;
            break;
        case '*':
        case '/':
            weightA = 2;
            break;
        default :
            weightA = 0;
    }

    switch(b) {
        case '-':
        case '+':
            weightB = 1;
            break;
        case '*':
        case '/':
            weightB = 2;
            break;
        default :
            weightB = 0;
    }

    return weightA > weightB ? -1 : (weightA < weightB ? 1 : 0);
}
