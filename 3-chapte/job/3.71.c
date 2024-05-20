#include <stdio.h>
#include <string.h>


char *gets(char *s)
{
    unsigned int c;
    char *dest = s;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        printf("in while %d\n", c);
        *dest = c;
        dest++;
    }

    if (c == EOF && dest == s)
    {
        /* No characters read */
        return NULL;
    }

    printf("\n\ndao zhe li %d", c);
    *dest = '\0'; /* Terminate string */

    return s;
}


int good_echo()
{
    char buf[8];
    char *s =  fgets(buf, 8, stdin);

    if (s == NULL) {
        return 0;
    }

    printf("okok\n\n");
    puts(s);
    return 1;
}

void main() {

    good_echo();
}
