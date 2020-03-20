// the ed editor stripped
// Jared Dyreson

#include "edder.h"

const int	NBLK = 2047; const int	FNSIZE = 128; const int	ESIZE	= 256, GBSIZE = 256; const int	BLKSIZE	= 4096, LBSIZE = 4096;
const int	CBRA = 1; const int	CCHR = 2; const int	CDOT = 4; const int	NBRA = 5; const int	CCL	= 6; const int	CCIRC	= 15; const int	STAR	= 01; const int WRITE = 1;
const int	NCCL = 8; const int	KSIZE = 9; const int	CDOL = 10; const int	CEOF = 11; const int	CKET	= 12; const int	CBACK	= 14; const int READ = 0;

char	Q[]	= "", T[]	= "TMP";

int	peekc, lastc, given;

char	savedfile[FNSIZE], file[FNSIZE], linebuf[LBSIZE], rhsbuf[LBSIZE/2], expbuf[ESIZE+4], file_contents[LBSIZE], our_expression_buffer[BUFSIZ], buf[BUFSIZ], input[BUFSIZ];
unsigned int	*addr1, *addr2, *dot, *dol, *zero;
long	count;
char	*nextip, *linebp, *globp, *tfname, *loc1, *loc2;
int	ninbuf, io, pflag, vflag	= 1, oflag, listf, listn, col, tfile	= -1, tline, buffer_pointer;

char	ibuff[BLKSIZE];
char	obuff[BLKSIZE];

int	names[26];
int	iblock	= -1, oblock	= -1, ichanged, nleft, anymarks, nbra, subnewa, subolda, fchange, wrapp, bpagesize = 20;
char	*braslist[NBRA], *braelist[NBRA];
unsigned nlall = 128;


void cerror_(){ expbuf[0] = 0; nbra = 0; error(Q); }

int main(int argc, char *argv[]){
  if(argc != 3){
    fprintf(stderr, "Usage: %s [pattern] [file path]\n", *argv);
    exit(1);
  }
	zero = (unsigned *)malloc(nlall*sizeof(unsigned));
	tfname = mkstemp("/tmp/ed_temp_file.txt");
	argv++; strcpy(our_expression_buffer, *argv);
  argv++; strcpy(savedfile, *argv); strcpy(file, *argv);
  init();
  read_in_file(savedfile);
  grepping();
	return 0;
}

int getch_(void) { 
  return (buffer_pointer > 0) ? buf[--buffer_pointer] : getchar() & 0177;
}
void ungetch_(int c) {
  if (buffer_pointer >= BUFSIZ) { fprintf(stderr, "ungetch: too many characters\n");  return; }
  buf[buffer_pointer++] = c;
}

void read_in_file(char* input){
  setnoaddr();
  init();
  addr2 = zero;
  if ((io = open(file, 0)) < 0) { lastc = '\n'; error(file); }
  setwide();
  zero_squeeze();
  ninbuf = 0;
  append(getfile, addr2);
  exfile();
  printf("Read in: %s\n", input);
  printf("\nContent of file: \n%s\n", file_contents);
  file_contents[strlen(file_contents)+1] = '\n';
}

void grepping(){
   /*contents of the file*/
  /*printf("Content: %s\n", file_contents);*/
  char b[GBSIZE];
  snprintf(b, sizeof(b), "/%s", our_expression_buffer);
  const char* p = b + strlen(b) - 1;
  while (p >= b) { ungetch_(*p--); }  
  global(1);
  /*ungetch_('\n');*/
  /*char temp[BUFSIZ] = "/"; strcat(temp, our_expression_buffer);*/
  /*size_t size_ = strlen(temp);*/
  /*while(size_ > 0){ putc(temp[size_], stdout); ungetch_(temp[size_--]); }*/
  /*ungetch_('/');*/
  /*global(1);*/
}


void print(void)
{
	unsigned int *a1;

	nonzero();
	a1 = addr1;
	do {
		if (listn) {
			count = a1-zero;
			
			putchar('\t');
		}
		puts(getline_(*a1++));
	} while (a1 <= addr2);
	dot = addr2;
	listf = 0;
	listn = 0;
	pflag = 0;
}

unsigned int *
address(void)
{
	int sign;
	unsigned int *a, *b;
	int opcnt, nextopand;
	int c;

	nextopand = -1;
	sign = 1;
	opcnt = 0;
	a = dot;
	do {
		do c = getchr(); while (c==' ' || c=='\t');
		if ('0'<=c && c<='9') {
			peekc = c;
			if (!opcnt)
				a = zero;
			a += sign*getnum();
		} else switch (c) {
		case '$':
			a = dol;
			/* fall through */
		case '.':
			if (opcnt)
				error(Q);
			break;
		case '\'':
			c = getchr();
			if (opcnt || c<'a' || 'z'<c)
				error(Q);
			a = zero;
			do a++; while (a<=dol && names[c-'a']!=(*a&~01));
			break;
		case '?':
			sign = -sign;
			/* fall through */
		case '/':
      printf("leading \/\n");
			compile(c);
			b = a;
			for (;;) {
				a += sign;
				if (a<=zero)
					a = dol;
				if (a>dol)
					a = zero;
				if (execute(a))
					break;
        if (a==b){
          printf("error here!\n");
					error(Q);
        }
			}
			break;
		default:
			if (nextopand == opcnt) {
				a += sign;
				if (a<zero || dol<a)
					continue;       /* error(Q); */
			}
			if (c!='+' && c!='-' && c!='^') {
				peekc = c;
				if (opcnt==0)
					a = 0;
				return (a);
			}
			sign = 1;
			if (c!='+')
				sign = -sign;
			nextopand = ++opcnt;
			continue;
		}
		sign = 1;
		opcnt++;
	} while (zero<=a && a<=dol);
	error(Q);
	/*NOTREACHED*/
	return 0;
}

int getnum(void){ int r = 0, c;
  while ((c=getchr())>='0' && c<='9') { r = r*10 + c - '0'; } peekc = c; return (r);
}

void setwide(void)
{
	if (!given) {
		addr1 = zero + (dol>zero);
		addr2 = dol;
	}
}

void setnoaddr(void){ {if (given) { error(Q); }} }

void nonzero(void){ squeeze(1); }

void squeeze(int i)
{
	if (addr1<zero+i || addr2>dol || addr1>addr2)
		error(Q);
}

void newline(void){ int c;
	if ((c = getchr()) == '\n' || c == EOF) { return; }
	if (c=='p' || c=='l' || c=='n') {
		pflag++;
		if (c=='l') { listf++; } else if (c=='n') { listn++; }
		if ((c=getchr())=='\n') { return; }
	} error(Q);
}


void exfile(void){ close(io); io = -1; if (vflag) { putchar('\n'); } }

void onhup(int n)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	if (dol > zero) {
		addr1 = zero+1;
		addr2 = dol;
		io = creat("ed.hup", 0600);
		if (io > 0)
			putfile();
	}
	fchange = 0;
	quit(0);
}

void error(char *s){
	int c;

	wrapp = 0, listf = 0, listn = 0;
  printf("? %s\n", s);
	count = 0;
	lseek(0, (long)0, 2);
	pflag = 0;
	if (globp) {lastc = '\n';}
	globp = 0;
	peekc = lastc;
	if(lastc){ while ((c = getchr()) != '\n' && c != EOF){} }
	if (io > 0) { close(io); io = -1; }
  quit(-1);
}

int getchr(void){ char c;
	if (lastc=peekc) { peekc = 0; return(lastc); }
	if (globp) {
		if ((lastc = *globp++) != 0) { return(lastc); }
		globp = 0;
		return(EOF);
	}
	return getch_();
}


int getfile(void){
	int c;
	char *lp, *fp;
	lp = linebuf; fp = nextip;
	do {
		if (--ninbuf < 0) {
			if ((ninbuf = read(io, file_contents, LBSIZE)-1) < 0)
				if (lp>linebuf) {
					puts("'\\n' appended");
					*file_contents = '\n';
				}
        else{
          printf("got to eof\n");
          return(EOF);
        }
			fp = file_contents;
			while(fp < &file_contents[ninbuf]) {
				if (*fp++ & 0200)
					break;
			}
			fp = file_contents;
		}
		c = *fp++;
		if (c=='\0')
			continue;
		if (c&0200 || lp >= &linebuf[LBSIZE]) {
			lastc = '\n';
			error(Q);
		}
		*lp++ = c;
		count++;
	} while (c != '\n');
	*--lp = 0;
	nextip = fp;
	return(0);
}

void putfile(void)
{
	unsigned int *a1;
	int n;
	char *fp, *lp;
	int nib;

	nib = BLKSIZE;
	fp = file_contents;
	a1 = addr1;
	do {
		lp = getline_(*a1++);
		for (;;) {
			if (--nib < 0) {
				n = fp-file_contents;
				if(write(io, file_contents, n) != n) {
          printf("WRITE ERROR\n");
					error(Q);
				}
				nib = BLKSIZE-1;
				fp = file_contents;
			}
			count++;
			if ((*fp++ = *lp++) == 0) {
				fp[-1] = '\n';
				break;
			}
		}
	} while (a1 <= addr2);
	n = fp-file_contents;
	if(write(io, file_contents, n) != n) {
		printf("WRITE ERROR\n");
		error(Q);
	}
}

int append(int (*f)(void), unsigned int *a)
{
	unsigned int *a1, *a2, *rdot;
	int nline, tl;

	nline = 0;
	dot = a;
	while ((*f)() == 0) {
		if ((dol-zero)+1 >= nlall) {
			unsigned *ozero = zero;

			nlall += 1024;
			if ((zero = (unsigned *)realloc((char *)zero, nlall*sizeof(unsigned)))==NULL) {
				error("MEM?");
				onhup(0);
			}
			dot += zero - ozero;
			dol += zero - ozero;
		}
		tl = putline();
		nline++;
		a1 = ++dol;
		a2 = a1+1;
		rdot = ++dot;
		while (a1 > rdot)
			*--a2 = *--a1;
		*rdot = tl;
	}
	return(nline);
}

void quit(int n)
{
	if (vflag && fchange && dol!=zero) {
		fchange = 0;
		error(Q);
	}
	unlink(tfname);
	exit(0);
}

void rdelete(unsigned int *ad1, unsigned int *ad2)
{
	unsigned int *a1, *a2, *a3;

	a1 = ad1;
	a2 = ad2+1;
	a3 = dol;
	dol -= a2 - a1;
	do {
		*a1++ = *a2++;
	} while (a2 <= a3);
	a1 = ad1;
	if (a1 > dol)
		a1 = dol;
	dot = a1;
	fchange = 1;
}

char *
getline_(unsigned int tl)
{
	char *bp, *lp;
	int nl;

	lp = linebuf;
	bp = getblock(tl, READ);
	nl = nleft;
	tl &= ~((BLKSIZE/2)-1);
	while (*lp++ = *bp++)
		if (--nl == 0) {
			bp = getblock(tl+=(BLKSIZE/2), READ);
			nl = nleft;
		}
	return(linebuf);
}

int putline(void)
{
	char *bp, *lp;
	int nl;
	unsigned int tl;

	fchange = 1;
	lp = linebuf;
	tl = tline;
	bp = getblock(tl, WRITE);
	nl = nleft;
	tl &= ~((BLKSIZE/2)-1);
	while (*bp = *lp++) {
		if (*bp++ == '\n') {
			*--bp = 0;
			linebp = lp;
			break;
		}
		if (--nl == 0) {
			bp = getblock(tl+=(BLKSIZE/2), WRITE);
			nl = nleft;
		}
	}
	nl = tline;
	tline += (((lp-linebuf)+03)>>1)&077776;
	return(nl);
}

char *
getblock(unsigned int atl, int iof)
{
	int bno, off;
	
	bno = (atl/(BLKSIZE/2));
	off = (atl<<1) & (BLKSIZE-1) & ~03;
	if (bno >= NBLK) {
		lastc = '\n';
		error(T);
	}
	nleft = BLKSIZE - off;
	if (bno==iblock) {
		ichanged |= iof;
		return(ibuff+off);
	}
	if (bno==oblock)
		return(obuff+off);
	if (iof==READ) {
		if (ichanged)
			blkio(iblock, ibuff, write);
		ichanged = 0;
		iblock = bno;
		blkio(bno, ibuff, read);
		return(ibuff+off);
	}
	if (oblock>=0)
		blkio(oblock, obuff, write);
	oblock = bno;
	return(obuff+off);
}

void blkio(int b, char *buf, int (*iofcn)(int, char*, int))
{
	lseek(tfile, (long)b*BLKSIZE, 0);
	if ((*iofcn)(tfile, buf, BLKSIZE) != BLKSIZE) {
		error(T);
	}
}

void init(void)
{
	int *markp;

	close(tfile);
	tline = 2;
	for (markp = names; markp < &names[26]; )
		*markp++ = 0;
	subnewa = 0;
	anymarks = 0;
	iblock = -1;
	oblock = -1;
	ichanged = 0;
	close(creat(tfname, 0600));
	tfile = open(tfname, 2);
	dot = dol = zero;
}

void global(int k)
{
	char *gp;
	int c;
	unsigned int *a1;
	char globuf[GBSIZE];

  if (globp){
    printf("globp error!\n");
		error(Q);
  }
	setwide();
	squeeze(dol>zero);
  printf("our expression: %s\n", our_expression_buffer);
  if ((c=getchr())=='\n'){ error(Q);} printf("compiling......\n"); compile(c); printf("done compiling....\n"); gp = globuf;
	while ((c = getchr()) != '\n') {
    if (c==EOF){
      printf("reached EOF!\n");
      error(Q);
      quit(-1);
    }
		if (c=='\\') {
			c = getchr();
			if (c!='\n')
				*gp++ = '\\';
		}
		*gp++ = c;
    if (gp >= &globuf[GBSIZE-2]){
			error(Q);
    }
	}
	if (gp == globuf)
		*gp++ = 'p';
	*gp++ = '\n';
	*gp++ = 0;
	for (a1=zero; a1<=dol; a1++) {
		*a1 &= ~01;
		if (a1>=addr1 && a1<=addr2 && execute(a1)==k)
			*a1 |= 01;
	}
	for (a1=zero; a1<=dol; a1++) {
		if (*a1 & 01) {
			*a1 &= ~01;
			dot = a1;
			globp = globuf;
			a1 = zero;
		}
	}
}


void substitute(int inglob)
{
	int *mp, nl;
	unsigned int *a1;
	int gsubf;
	int n;

	n = getnum();	/* OK even if n==0 */
	gsubf = compsub();
	for (a1 = addr1; a1 <= addr2; a1++) {
		if (execute(a1)){
			unsigned *ozero;
			int m = n;
			do {
				int span = loc2-loc1;
				if (--m <= 0) {
					dosub();
					if (!gsubf)
						break;
					if (span==0) {	/* null RE match */
						if (*loc2=='\0')
							break;
						loc2++;
					}
				}
			} while (execute((unsigned *)0));
			if (m <= 0) {
				inglob |= 01;
				subnewa = putline();
				*a1 &= ~01;
				if (anymarks) {
					for (mp = names; mp < &names[26]; mp++)
						if (*mp == *a1)
							*mp = subnewa;
				}
				subolda = *a1;
				*a1 = subnewa;
				ozero = zero;
				nl = append(getsub, a1);
				nl += zero-ozero;
				a1 += nl;
				addr2 += nl;
			}
		}
	}
	if (inglob==0)
		error(Q);
}

int compsub(void)
{
	int seof, c;
	char *p;

	if ((seof = getchr()) == '\n' || seof == ' ')
		error(Q);
	compile(seof);
	p = rhsbuf;
	for (;;) {
		c = getchr();
		if (c=='\\')
			c = getchr() | 0200;
		if (c=='\n') {
			if (globp && globp[0])	/* last '\n' does not count */
				c |= 0200;
			else {
				peekc = c;
				pflag++;
				break;
			}
		}
		if (c==seof)
			break;
		*p++ = c;
		if (p >= &rhsbuf[LBSIZE/2])
			error(Q);
	}
	*p++ = 0;
	if ((peekc = getchr()) == 'g') {
		peekc = 0;
		newline();
		return(1);
	}
	newline();
	return(0);
}

int getsub(void)
{
	char *current_line_content, *current_regular_expression_text;

	current_line_content = linebuf;
	if ((current_regular_expression_text = linebp) == 0)
		return(EOF);
	while (*current_line_content++ = *current_regular_expression_text++)
		;
	linebp = 0;
	return(0);
}

void dosub(void)
{
	char *lp, *sp, *rp;
	int c;

	lp = linebuf;
	sp = file_contents;
	rp = rhsbuf;
	while (lp < loc1)
		*sp++ = *lp++;
	while (c = *rp++&0377) {
		if (c=='&') {
			sp = place(sp, loc1, loc2);
			continue;
		} else if (c&0200 && (c &= 0177) >='1' && c < nbra+'1') {
			sp = place(sp, braslist[c-'1'], braelist[c-'1']);
			continue;
		}
		*sp++ = c&0177;
		if (sp >= &file_contents[LBSIZE])
			error(Q);
	}
	lp = loc2;
	loc2 = sp - file_contents + linebuf;
	while (*sp++ = *lp++)
		if (sp >= &file_contents[LBSIZE])
			error(Q);
	lp = linebuf;
	sp = file_contents;
	while (*lp++ = *sp++)
		;
}

char *
place(char *sp, char *l1, char *l2)
{

	while (l1 < l2) {
		*sp++ = *l1++;
		if (sp >= &file_contents[LBSIZE])
			error(Q);
	}
	return(sp);
}

void move(int cflag)
{
	unsigned int *adt, *ad1, *ad2;

	nonzero();
	if ((adt = address())==0)	/* address() guarantees addr is in range */
		error(Q);
	newline();
	if (cflag) {
		unsigned int *ozero;
		int delta;

		ad1 = dol;
		ozero = zero;
		append(getcopy, ad1++);
		ad2 = dol;
		delta = zero - ozero;
		ad1 += delta;
		adt += delta;
	} else {
		ad2 = addr2;
		for (ad1 = addr1; ad1 <= ad2;)
			*ad1++ &= ~01;
		ad1 = addr1;
	}
	ad2++;
	if (adt<ad1) {
		dot = adt + (ad2-ad1);
		if ((++adt)==ad1)
			return;
		reverse(adt, ad1);
		reverse(ad1, ad2);
		reverse(adt, ad2);
	} else if (adt >= ad2) {
		dot = adt++;
		reverse(ad1, ad2);
		reverse(ad2, adt);
		reverse(ad1, adt);
	} else
		error(Q);
	fchange = 1;
}

void reverse(unsigned int *a1, unsigned int *a2)
{
	int t;

	for (;;) {
		t = *--a2;
		if (a2 <= a1)
			return;
		*a2 = *a1;
		*a1++ = t;
	}
}

int getcopy(void)
{
	if (addr1 > addr2)
		return(EOF);
	getline_(*addr1++);
	return(0);
}

void compile(int eof)
{
  printf("top of the compile function!\n");
	int c;
	char *ep = expbuf;
	char *lastep;
	char bracket[NBRA], *bracketp = bracket;
	int cclcnt;
	if ((c = getchr()) == '\n') { printf("newline!\n"); peekc = c; c = eof; }
  printf("current contents of c: %c\n", c);
  if(c == '\0'){ printf("null terminating byte!\n"); }
	if (c == eof) { if (*ep==0){ error(Q); } return; }
	nbra = 0;
	if (c=='^') { c = getchr(); printf("after get char\n"); *ep++ = CCIRC; }; peekc = c; lastep = 0;
	for (;;) {
    if (ep >= &expbuf[ESIZE]){ cerror_(); }
		c = getchr();
		if (c == '\n') {
			peekc = c;
			c = eof;
		}
		if (c==eof) {
			if (bracketp != bracket)
				cerror_();
			*ep++ = CEOF;
			return;
		}
		if (c!='*')
			lastep = ep;
		switch (c) {

		case '\\':
			if ((c = getchr())=='(') {
				if (nbra >= NBRA)
					cerror_();
				*bracketp++ = nbra;
				*ep++ = CBRA;
				*ep++ = nbra++;
				continue;
			}
			if (c == ')') {
				if (bracketp <= bracket)
					cerror_();
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
			if (c=='\n')
				cerror_();
			*ep++ = c;
			continue;

		case '.':
			*ep++ = CDOT;
			continue;

		case '\n': cerror_();

		case '*':
			if (lastep==0 || *lastep==CBRA || *lastep==CKET){ break; }
				/*goto defchar;*/
			*lastep |= STAR;
			continue;

		case '$':
			if ((peekc=getchr()) != eof && peekc!='\n'){ break; }
				/*goto defchar;*/
			*ep++ = CDOL;
			continue;
    case '\0':
      printf("got to the end of the string");
      break;

		case '[':
			*ep++ = CCL;
			*ep++ = 0;
			cclcnt = 1;
			if ((c=getchr()) == '^') {
				c = getchr();
				ep[-2] = NCCL;
			}
			do {
				if (c=='\n')
					cerror_();
				if (c=='-' && ep[-1]!=0) {
					if ((c=getchr())==']') {
						*ep++ = '-';
						cclcnt++;
						break;
					}
					while (ep[-1]<c) {
						*ep = ep[-1]+1;
						ep++;
						cclcnt++;
						if (ep>=&expbuf[ESIZE])
							cerror_();
					}
				}
				*ep++ = c;
				cclcnt++;
				if (ep >= &expbuf[ESIZE])
					cerror_();
			} while ((c = getchr()) != ']');
			lastep[1] = cclcnt;
			continue;

		default:
			*ep++ = CCHR;
			*ep++ = c;
      printf("current contents of: %c\n", c);
		}
	}
  printf("end of the compile function!\n");
}


int execute(unsigned int *addr)
{
  printf("got inside execute!\n");
  printf("contens of expbuf: %s\n", expbuf);
	char *current_line_content, *current_regular_expression_text;
	int c;

	for (c=0; c<NBRA; c++) {
		braslist[c] = 0;
		braelist[c] = 0;
	}
	current_regular_expression_text = expbuf;
	if (addr == (unsigned *)0) {
		if (*current_regular_expression_text==CCIRC)
			return(0);
		current_line_content = loc2;
	} else if (addr==zero)
		return(0);
  else{
		current_line_content = getline_(*addr);
    printf("contents of current_line_content: %s\n", current_line_content);
    printf("contents of current_regular_expression_text: %s\n", current_regular_expression_text);
  }
	if (*current_regular_expression_text==CCIRC) {
		loc1 = current_line_content;
		return(advance(current_line_content, current_regular_expression_text+1));
	}
	/* fast check for first character */
	if (*current_regular_expression_text==CCHR) {
		c = current_regular_expression_text[1];
		do {
			if (*current_line_content!=c)
				continue;
			if (advance(current_line_content, current_regular_expression_text)) {
				loc1 = current_line_content;
				return(1);
			}
		} while (*current_line_content++);
		return(0);
	}
	/* regular algorithm */
	do {
		if (advance(current_line_content, current_regular_expression_text)) {
			loc1 = current_line_content;
			return(1);
		}
	} while (*current_line_content++);
	return(0);
}

int advance(char *lp, char *ep){ char *curlp; int i;
	for (;;) switch (*ep++) {
	case CCHR: if (*ep++ == *lp++) { continue; }; return(0);
	case CDOT: if (*lp++) { continue; }; return(0);
	case CDOL: if (*lp==0) { continue; }; return(0);
	case CEOF: loc2 = lp; return(1);
	case CCL: if (cclass(ep, *lp++, 1)) { ep += *ep; continue; } return(0);
	case NCCL: if (cclass(ep, *lp++, 0)) { ep += *ep; continue; } return(0);
	case CBRA: braslist[*ep++] = lp; continue;
	case CKET: braelist[*ep++] = lp; continue;
	case CBACK:
		if (braelist[i = *ep++]==0)
			error(Q);
		if (backref(i, lp)) {
			lp += braelist[i] - braslist[i];
			continue;
		}
		return(0);

	case CBACK|STAR:
		if (braelist[i = *ep++] == 0)
			error(Q);
		curlp = lp;
		while (backref(i, lp))
			lp += braelist[i] - braslist[i];
		while (lp >= curlp) {
			if (advance(lp, ep))
				return(1);
			lp -= braelist[i] - braslist[i];
		}
		continue;

	case CDOT|STAR: curlp = lp; while (*lp++){}; goto star;
	case CCHR|STAR: curlp = lp; while (*lp++ == *ep){}; ep++; goto star;

	case CCL|STAR:
	case NCCL|STAR:
		curlp = lp;
		while (cclass(ep, *lp++, ep[-1]==(CCL|STAR)))
			;
		ep += *ep;
		goto star;

	star: do { lp--; if (advance(lp, ep)) { return(1); } } while (lp > curlp);
		return(0);

	default: error(Q);
	}
}

int backref(int i, char *lp){
	char *bp = braslist[i];
	while (*bp++ == *lp++){ if (bp >= braelist[i]){	{ return(1); } } }
	return(0);
}

int cclass(char *set, int c, int af){ int n;
	if (c==0) { return(0); }
	n = *set++;
	while (--n) { if (*set++ == c) { return(af); } }
	return(!af);
}

void commands(void)
{
	unsigned int *a1;
	int c;
	int temp;
	char lastsep;

	for (;;) {
	if (pflag) {
		pflag = 0;
		addr1 = addr2 = dot;
		print();
	}
	c = '\n';
	for (addr1 = 0;;) {
		lastsep = c;
		a1 = address();
		c = getchr();
		if (c!=',' && c!=';')
			break;
		if (lastsep==',')
			error(Q);
		if (a1==0) {
			a1 = zero+1;
			if (a1>dol)
				a1--;
		}
		addr1 = a1;
		if (c==';')
			dot = a1;
	}
	if (lastsep!='\n' && a1==0)
		a1 = dol;
	if ((addr2=a1)==0) {
		given = 0;
		addr2 = dot;	
	}
	else
		given = 1;
	if (addr1==0)
		addr1 = addr2;
  switch(c){
    case 'p': case 'P': newline(); print(); continue;
    case EOF: return;
  }

  }
}
