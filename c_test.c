#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static char buf[128];
static int pos;

void crash() {
    *((unsigned int *)1) = 1;
}

void read_file(char *path, char *_buf) {
    FILE *fp;
    if ((fp = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Failed to open %s\n", path);
        exit(EXIT_FAILURE);
    }
    fread(_buf, sizeof(char), 16, fp);
    fclose(fp);
}

/*
<expression> ::= <term> [ ('+'|'-') <term> ]*
<term>   ::= <factor> [ ('*'|'/') <factor> ]*
<factor> ::= <number> | '(' <expression> ')'
*/
static inline int is_num(char c) {
    return '0' <= c && c <= '9';
}

static int number() {
    int res = 0;
    while (is_num(buf[pos])) {
        res *= 10;
        res += buf[pos] - '0';
        pos++;
    }
    return res;
}

static int express();
static int fact() {
    if (buf[pos] == '(') {
        int res;
        pos++;
        res = express();
        pos++; // ')'
        return res;
    } else if(is_num(buf[pos])) {
        int num = number();
        //printf("number: %d\n", num);
        return num;
    }
    fprintf(stderr, "Unexpected char %c(%d)\n",buf[pos], pos);
    exit(0);
}

static int term() {
    int res = fact();
    while (buf[pos] == '*' || buf[pos] == '/') {
        char op = buf[pos];
        pos++;
        if (op == '*') {
            res *= fact();
        } else if (op == '/') {
            int f = fact();
            if (f == 0) {
                fprintf(stderr, "Divided by zero(%d)\n",pos); 
                exit(0);
            }
            res /= f;
        }
    }
    return res;
}

static int express() {
    int res = term();
    while (buf[pos] == '+' || buf[pos] == '-') {
        char op = buf[pos];
        pos++;
        if (op == '+') {
            res += term();
        } else if (op == '-') {
            res -= term();
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage ./c_test <input-file>\n");
        exit(EXIT_FAILURE);
    }

    read_file(argv[1], buf);
    printf("Read %s\n", buf);
    return 0;
}