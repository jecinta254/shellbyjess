#include "shell.h"

char watho[1024];

int main(void){
        while (true)
        {
                jnj_prompt();
		jnj_readcmd(watho, sizeof(watho));
                jnj_execute(watho);

        }


        return 0;

}

