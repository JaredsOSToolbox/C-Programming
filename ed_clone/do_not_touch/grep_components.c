#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define	CBRA	1
#define	CCHR	2
#define	CDOT	4
#define	CCL	6
#define	NCCL	8
#define	CDOL	10
#define	CEOF	11
#define	CKET	12
#define	CBACK	14
#define	CCIRC	15

#define	FNSIZE	128
#define	LBSIZE	4096
#define	ESIZE	256
#define	GBSIZE	256
#define	NBRA	5
#define	KSIZE	9
#define	STAR	01

char expression_buffer[BUFSIZ];
char	Q[]	= "";
void error(int e){ fprintf(stderr, "got an error: %d\n", e); }
void string_error(char e[]){ fprintf(stderr, "got an error: %s\n", e); }

int	nbra, subnewa, subolda, fchange, wrapp, bpagesize = 20;
unsigned nlall = 128;

int	peekc;
int	lastc;

void compile(const char* string) {
  // this seems to be the REGEX engine
  printf("got the string: %s\n", string);
  if(strlen(string) == 0){ return; }
	int c, cclcnt;
	char *ep, *lastep;
	char bracket[NBRA];
  char *bracketp;
  while(*string != '\0'){
    if(*string == '\n'){
      peekc = *string;
      c = EOF;
    }
    if(*string == EOF){
      if(strlen(string) == 0){ string_error("string empty"); }
      return;
    }

    return;
  }

	ep = expression_buffer;
	bracketp = bracket;
	if ((c = getchar()) == '\n') {
		peekc = c;
		c = EOF;
	}
	if (c == EOF) {
		if (*ep==0) {string_error(Q);}
		return;
	}
	nbra = 0;
	if (c=='^') {
		c = getchar();
		*ep++ = CCIRC;
	}
	peekc = c;
	lastep = 0;

  // whlie true loop

	for (;;) {
		if (ep >= &expression_buffer[ESIZE])
			goto cerror;
		c = getchar();
		if (c == '\n') {
			peekc = c;
			c = EOF;
		}
		if (c==EOF) {
			if (bracketp != bracket) {goto cerror;}
			*ep++ = CEOF;
			return;
		}

		if (c!='*') {lastep = ep;}

		switch (c) {

		case '\\':
			if ((c = getchar())=='(') {
				if (nbra >= NBRA) {goto cerror;}
				*bracketp++ = nbra;
				*ep++ = CBRA;
				*ep++ = nbra++;
				continue;
			}
			if (c == ')') {
				if (bracketp <= bracket) {goto cerror;}
				*ep++ = CKET;
				*ep++ = *--bracketp;
				continue;
			}
			if (c>='1' && c<'1'+NBRA) {
				*ep++ = CBACK;
				*ep++ = c-'1';
				continue;
			}
			*ep++ = CCHR;
			if (c=='\n') {goto cerror;}
			*ep++ = c;
			continue;

		case '.': *ep++ = CDOT; continue;

		case '\n': goto cerror;

		case '*':
			if (lastep==0 || *lastep==CBRA || *lastep==CKET) {goto defchar;}
			*lastep |= STAR;
			continue;

		case '$':
			if ((peekc=getchar()) != EOF && peekc!='\n') {goto defchar;}
			*ep++ = CDOL;
			continue;

		case '[':
			*ep++ = CCL;
			*ep++ = 0;
			cclcnt = 1;
			if ((c=getchar()) == '^') {
				c = getchar();
				ep[-2] = NCCL;
			}
			do {
				if (c=='\n') {goto cerror;}

				if (c=='-' && ep[-1]!=0) {
					if ((c=getchar())==']') {
						*ep++ = '-';
						cclcnt++;
						break;
					}
					while (ep[-1]<c) {
						*ep = ep[-1]+1;
						ep++;
						cclcnt++;
						if (ep>=&expression_buffer[ESIZE]) {goto cerror;}
					}
				}
				*ep++ = c;
				cclcnt++;
				if (ep >= &expression_buffer[ESIZE]) {goto cerror;}

			} while ((c = getchar()) != ']');
			lastep[1] = cclcnt;
			continue;

		defchar:
		default:
			*ep++ = CCHR;
			*ep++ = c;
		}
	}
   cerror:
	expression_buffer[0] = 0;
	nbra = 0;
	string_error(Q);
}

int main(int argc, const char* argv[]){
  /*strcpy(expression_buffer, "Hello");*/
  compile("^Hello");
  return 0;
}
