// the ed editor stripped
// Jared Dyreson

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <setjmp.h>

#define	BLKSIZE	4096
#define	NBLK	2047

#define	FNSIZE	128
#define	LBSIZE	4096
#define	ESIZE	256
#define	GBSIZE	256
#define	NBRA	5
#define	KSIZE	9

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

#define	STAR	01

char	Q[]	= "";
char	T[]	= "TMP";
#define	READ	0
#define	WRITE	1

int	peekc;
int	lastc;
char	savedfile[FNSIZE];
char	file[FNSIZE];
char	linebuf[LBSIZE];
char	rhsbuf[LBSIZE/2];
char	expbuf[ESIZE+4];
int	given;
unsigned int	*addr1, *addr2;
unsigned int	*dot, *dol, *zero;
char	genbuf[LBSIZE];
long	count;
char	*nextip;
char	*linebp;
int	ninbuf;
int	io;
int	pflag;

int	vflag	= 1;
int	oflag;
int	listf;
int	listn;
int	col;
char	*globp;
int	tfile	= -1;
int	tline;
char	*tfname;
char	*loc1;
char	*loc2;
char	ibuff[BLKSIZE];
int	iblock	= -1;
char	obuff[BLKSIZE];
int	oblock	= -1;
int	ichanged;
int	nleft;
char	WRERR[]	= "WRITE ERROR";
int	names[26];
int	anymarks;
char	*braslist[NBRA];
char	*braelist[NBRA];
int	nbra;
int	subnewa;
int	subolda;
int	fchange;
int	wrapp;
int	bpagesize = 20;
unsigned nlall = 128;

char *getblock(unsigned int atl, int iof);
char *getline_(unsigned int tl);
char *place(char *sp, char *l1, char *l2);
void add(int i);
int advance(char *lp, char *ep);
int append(int (*f)(void), unsigned int *a);
int backref(int i, char *lp);
void blkio(int b, char *buf, int (*iofcn)(int, char*, int));
void callunix(void);
int cclass(char *set, int c, int af);
void compile(int eof);
int compsub(void);
void dosub(void);
void error(char *s);
int execute(unsigned int *addr);
void exfile(void);
void filename(int comm);
void gdelete(void);
int getcopy(void);
int getfile(void);
int getnum(void);
int getsub(void);
int gettty(void);
int gety(void);
void global(int k);
unsigned int *address(void);
void join(void);
void move(int cflag);
void newline(void);
void nonzero(void);
void onhup(int n);
void onintr(int n);
void print(void);
void putfile(void);
int putline(void);
void quit(int n);
void rdelete(unsigned int *ad1, unsigned int *ad2);
void reverse(unsigned int *a1, unsigned int *a2);
void setwide(void);
void setnoaddr(void);
void squeeze(int i);
void substitute(int inglob);

jmp_buf	savej;

typedef void	(*SIG_TYP)(int);

SIG_TYP	oldhup;
SIG_TYP	oldquit;

/* these two are not in ansi, but we need them */
#define	SIGHUP	1	/* hangup */
#define	SIGQUIT	3	/* quit (ASCII FS) */

size_t NUMBER_OF_LINES = 1000;
#define MAX_LINE_SIZE 50

char** read_lines(char* path_){
  char * line = NULL;
  size_t len = 0, index_ = 0, t_ = 0;
  ssize_t read;
  char **lines;
  lines = malloc(NUMBER_OF_LINES * sizeof(char*));
  for (int i = 0; i < NUMBER_OF_LINES; i++){ lines[i] = malloc((MAX_LINE_SIZE+1) * sizeof(char)); }
  FILE* input = fopen(path_, "r");
  while((read = getline(&line, &len, input)) != EOF && (index_++ < NUMBER_OF_LINES)){ strcpy(lines[index_], line); } 
  t_ = index_;
  while(t_++ < NUMBER_OF_LINES){ free(lines[t_]); }
  NUMBER_OF_LINES = index_;
  fclose(input);
  return lines;
}
int main(int argc, char *argv[]){
  if(argc < 2){ fprintf(stderr, "Usage: %s [pattern] [file(s)]\n", argv[0]); exit(1); }
  argv++;
  while (argc-- > 1 && **argv =='-') { argv++; }

  char expression_[50]; strcpy(expression_, *argv++);
  printf("[+] Processing: %s\nExpression captured: %s\n", *argv, expression_);
  if(access(*argv, F_OK) == EOF){ fprintf(stderr, "Cowardly refusing to open %s, it does not exist\n", *argv); exit(1); }
  char** content = read_lines(*argv);
  for(int i = 0; i < NUMBER_OF_LINES; ++i){ printf("%s", content[i]); }
  free(content);
  return 0;












	char *p1, *p2;
	SIG_TYP oldintr;

	oldquit = signal(SIGQUIT, SIG_IGN);
	oldhup = signal(SIGHUP, SIG_IGN);
	oldintr = signal(SIGINT, SIG_IGN);
  if (signal(SIGTERM, SIG_IGN) == SIG_DFL){ signal(SIGTERM, quit); }
	argv++;
	if (oflag) {
    // print this to the console
		p1 = "/dev/stdout";
		p2 = savedfile;
		while (*p2++ = *p1++){}
	}
	if (argc>1) {
		p1 = *argv;
		p2 = savedfile;
		while (*p2++ = *p1++)
			if (p2 >= &savedfile[sizeof(savedfile)])
				p2--;
		globp = "r";
	}
	zero = (unsigned *)malloc(nlall*sizeof(unsigned));
	tfname = mkstemp("/tmp/ed_temp_file.txt");

  if (oldintr!=SIG_IGN) {signal(SIGINT, onintr);}
  if (oldhup!=SIG_IGN) {signal(SIGHUP, onhup);}
  setjmp(savej);
  /*commands();*/
  /*printf("goodbye from main!\n");*/
	/*quit(0);*/
	return 0;
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
		do c = getchar(); while (c==' ' || c=='\t');
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
			c = getchar();
			if (opcnt || c<'a' || 'z'<c)
				error(Q);
			a = zero;
			do a++; while (a<=dol && names[c-'a']!=(*a&~01));
			break;
		case '?':
			sign = -sign;
			/* fall through */
		case '/':
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
				if (a==b)
					error(Q);
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

int getnum(void)
{
	int r, c;

	r = 0;
	while ((c=getchar())>='0' && c<='9')
		r = r*10 + c - '0';
	peekc = c;
	return (r);
}

void setwide(void)
{
	if (!given) {
		addr1 = zero + (dol>zero);
		addr2 = dol;
	}
}

void setnoaddr(void)
{
	if (given)
		error(Q);
}

void nonzero(void)
{
	squeeze(1);
}

void squeeze(int i)
{
	if (addr1<zero+i || addr2>dol || addr1>addr2)
		error(Q);
}

void newline(void)
{
	int c;

	if ((c = getchar()) == '\n' || c == EOF)
		return;
	if (c=='p' || c=='l' || c=='n') {
		pflag++;
		if (c=='l')
			listf++;
		else if (c=='n')
			listn++;
		if ((c=getchar())=='\n')
			return;
	}
	error(Q);
}

void filename(int comm)
{
	char *p1, *p2;
	int c;

	count = 0;
	c = getchar();
	if (c=='\n' || c==EOF) {
		p1 = savedfile;
		if (*p1==0 && comm!='f')
			error(Q);
		p2 = file;
		while (*p2++ = *p1++)
			;
		return;
	}
	if (c!=' ')
		error(Q);
	while ((c = getchar()) == ' ')
		;
	if (c=='\n')
		error(Q);
	p1 = file;
	do {
		if (p1 >= &file[sizeof(file)-1] || c==' ' || c==EOF)
			error(Q);
		*p1++ = c;
	} while ((c = getchar()) != '\n');
	*p1++ = 0;
	if (savedfile[0]==0 || comm=='e' || comm=='f') {
		p1 = savedfile;
		p2 = file;
		while (*p1++ = *p2++)
			;
	}
}

void exfile(void)
{
	close(io);
	io = -1;
	if (vflag) {
		
		putchar('\n');
	}
}

void onintr(int n)
{
	signal(SIGINT, onintr);
	putchar('\n');
	lastc = '\n';
	error(Q);
}

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

void error(char *s)
{
	int c;

	wrapp = 0;
	listf = 0;
	listn = 0;
	putchar('?');
	puts(s);
	count = 0;
	lseek(0, (long)0, 2);
	pflag = 0;
	if (globp)
		lastc = '\n';
	globp = 0;
	peekc = lastc;
	if(lastc)
		while ((c = getchar()) != '\n' && c != EOF)
			;
	if (io > 0) {
		close(io);
		io = -1;
	}
	longjmp(savej, 1);
}


int gettty(void)
{
	int rc;

	if (rc = gety())
		return(rc);
	if (linebuf[0]=='.' && linebuf[1]==0)
		return(EOF);
	return(0);
}

int gety(void)
{
	int c;
	char *gf;
	char *p;

	p = linebuf;
	gf = globp;
	while ((c = getchar()) != '\n') {
		if (c==EOF) {
			if (gf)
				peekc = c;
			return(c);
		}
		if ((c &= 0177) == 0)
			continue;
		*p++ = c;
		if (p >= &linebuf[LBSIZE-2])
			error(Q);
	}

	*p++ = 0;
	return(0);
}

int getfile(void)
{
	int c;
	char *lp, *fp;

	lp = linebuf;
	fp = nextip;
	do {
		if (--ninbuf < 0) {
			if ((ninbuf = read(io, genbuf, LBSIZE)-1) < 0)
				if (lp>linebuf) {
					puts("'\\n' appended");
					*genbuf = '\n';
				}
				else return(EOF);
			fp = genbuf;
			while(fp < &genbuf[ninbuf]) {
				if (*fp++ & 0200)
					break;
			}
			fp = genbuf;
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
	fp = genbuf;
	a1 = addr1;
	do {
		lp = getline_(*a1++);
		for (;;) {
			if (--nib < 0) {
				n = fp-genbuf;
				if(write(io, genbuf, n) != n) {
					puts(WRERR);
					error(Q);
				}
				nib = BLKSIZE-1;
				fp = genbuf;
			}
			count++;
			if ((*fp++ = *lp++) == 0) {
				fp[-1] = '\n';
				break;
			}
		}
	} while (a1 <= addr2);
	n = fp-genbuf;
	if(write(io, genbuf, n) != n) {
		puts(WRERR);
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

void add(int i)
{
	if (i && (given || dol>zero)) {
		addr1--;
		addr2--;
	}
	squeeze(0);
	newline();
	append(gettty, addr2);
}

void callunix(void)
{
	SIG_TYP savint;
	int pid, rpid;
	int retcode;

	setnoaddr();
	if ((pid = fork()) == 0) {
		signal(SIGHUP, oldhup);
		signal(SIGQUIT, oldquit);
		execl("/bin/sh", "sh", "-t", 0);
		exit(0100);
	}
	savint = signal(SIGINT, SIG_IGN);
	while ((rpid = wait(&retcode)) != pid && rpid != -1)
		;
	signal(SIGINT, savint);
	if (vflag) {
		puts("!");
	}
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

void gdelete(void)
{
	unsigned int *a1, *a2, *a3;

	a3 = dol;
	for (a1=zero; (*a1&01)==0; a1++)
		if (a1>=a3)
			return;
	for (a2=a1+1; a2<=a3;) {
		if (*a2&01) {
			a2++;
			dot = a1;
		} else
			*a1++ = *a2++;
	}
	dol = a1-1;
	if (dot>dol)
		dot = dol;
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


void global(int k)
{
	char *gp;
	int c;
	unsigned int *a1;
	char globuf[GBSIZE];

	if (globp)
		error(Q);
	setwide();
	squeeze(dol>zero);
	if ((c=getchar())=='\n')
		error(Q);
	compile(c);
	gp = globuf;
	while ((c = getchar()) != '\n') {
		if (c==EOF)
			error(Q);
		if (c=='\\') {
			c = getchar();
			if (c!='\n')
				*gp++ = '\\';
		}
		*gp++ = c;
		if (gp >= &globuf[GBSIZE-2])
			error(Q);
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
	/*
	 * Special case: g/.../d (avoid n^2 algorithm)
	 */
	if (globuf[0]=='d' && globuf[1]=='\n' && globuf[2]=='\0') {
		gdelete();
		return;
	}
	for (a1=zero; a1<=dol; a1++) {
		if (*a1 & 01) {
			*a1 &= ~01;
			dot = a1;
			globp = globuf;
			/*commands();*/
			a1 = zero;
		}
	}
}

void join(void)
{
	char *gp, *lp;
	unsigned int *a1;

	nonzero();
	gp = genbuf;
	for (a1=addr1; a1<=addr2; a1++) {
		lp = getline_(*a1);
		while (*gp = *lp++)
			if (gp++ >= &genbuf[LBSIZE-2])
				error(Q);
	}
	lp = linebuf;
	gp = genbuf;
	while (*lp++ = *gp++)
		;
	*addr1 = putline();
	if (addr1<addr2)
		rdelete(addr1+1, addr2);
	dot = addr1;
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

	if ((seof = getchar()) == '\n' || seof == ' ')
		error(Q);
	compile(seof);
	p = rhsbuf;
	for (;;) {
		c = getchar();
		if (c=='\\')
			c = getchar() | 0200;
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
	if ((peekc = getchar()) == 'g') {
		peekc = 0;
		newline();
		return(1);
	}
	newline();
	return(0);
}

int getsub(void)
{
	char *p1, *p2;

	p1 = linebuf;
	if ((p2 = linebp) == 0)
		return(EOF);
	while (*p1++ = *p2++)
		;
	linebp = 0;
	return(0);
}

void dosub(void)
{
	char *lp, *sp, *rp;
	int c;

	lp = linebuf;
	sp = genbuf;
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
		if (sp >= &genbuf[LBSIZE])
			error(Q);
	}
	lp = loc2;
	loc2 = sp - genbuf + linebuf;
	while (*sp++ = *lp++)
		if (sp >= &genbuf[LBSIZE])
			error(Q);
	lp = linebuf;
	sp = genbuf;
	while (*lp++ = *sp++)
		;
}

char *
place(char *sp, char *l1, char *l2)
{

	while (l1 < l2) {
		*sp++ = *l1++;
		if (sp >= &genbuf[LBSIZE])
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
	int c;
	char *ep;
	char *lastep;
	char bracket[NBRA], *bracketp;
	int cclcnt;

	ep = expbuf;
	bracketp = bracket;
	if ((c = getchar()) == '\n') {
		peekc = c;
		c = eof;
	}
	if (c == eof) {
		if (*ep==0)
			error(Q);
		return;
	}
	nbra = 0;
	if (c=='^') {
		c = getchar();
		*ep++ = CCIRC;
	}
	peekc = c;
	lastep = 0;
	for (;;) {
		if (ep >= &expbuf[ESIZE])
			goto cerror;
		c = getchar();
		if (c == '\n') {
			peekc = c;
			c = eof;
		}
		if (c==eof) {
			if (bracketp != bracket)
				goto cerror;
			*ep++ = CEOF;
			return;
		}
		if (c!='*')
			lastep = ep;
		switch (c) {

		case '\\':
			if ((c = getchar())=='(') {
				if (nbra >= NBRA)
					goto cerror;
				*bracketp++ = nbra;
				*ep++ = CBRA;
				*ep++ = nbra++;
				continue;
			}
			if (c == ')') {
				if (bracketp <= bracket)
					goto cerror;
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
				goto cerror;
			*ep++ = c;
			continue;

		case '.':
			*ep++ = CDOT;
			continue;

		case '\n':
			goto cerror;

		case '*':
			if (lastep==0 || *lastep==CBRA || *lastep==CKET)
				goto defchar;
			*lastep |= STAR;
			continue;

		case '$':
			if ((peekc=getchar()) != eof && peekc!='\n')
				goto defchar;
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
				if (c=='\n')
					goto cerror;
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
						if (ep>=&expbuf[ESIZE])
							goto cerror;
					}
				}
				*ep++ = c;
				cclcnt++;
				if (ep >= &expbuf[ESIZE])
					goto cerror;
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
	expbuf[0] = 0;
	nbra = 0;
	error(Q);
}

int execute(unsigned int *addr)
{
	char *p1, *p2;
	int c;

	for (c=0; c<NBRA; c++) {
		braslist[c] = 0;
		braelist[c] = 0;
	}
	p2 = expbuf;
	if (addr == (unsigned *)0) {
		if (*p2==CCIRC)
			return(0);
		p1 = loc2;
	} else if (addr==zero)
		return(0);
	else
		p1 = getline_(*addr);
	if (*p2==CCIRC) {
		loc1 = p1;
		return(advance(p1, p2+1));
	}
	/* fast check for first character */
	if (*p2==CCHR) {
		c = p2[1];
		do {
			if (*p1!=c)
				continue;
			if (advance(p1, p2)) {
				loc1 = p1;
				return(1);
			}
		} while (*p1++);
		return(0);
	}
	/* regular algorithm */
	do {
		if (advance(p1, p2)) {
			loc1 = p1;
			return(1);
		}
	} while (*p1++);
	return(0);
}

int advance(char *lp, char *ep)
{
	char *curlp;
	int i;

	for (;;) switch (*ep++) {

	case CCHR:
		if (*ep++ == *lp++)
			continue;
		return(0);

	case CDOT:
		if (*lp++)
			continue;
		return(0);

	case CDOL:
		if (*lp==0)
			continue;
		return(0);

	case CEOF:
		loc2 = lp;
		return(1);

	case CCL:
		if (cclass(ep, *lp++, 1)) {
			ep += *ep;
			continue;
		}
		return(0);

	case NCCL:
		if (cclass(ep, *lp++, 0)) {
			ep += *ep;
			continue;
		}
		return(0);

	case CBRA:
		braslist[*ep++] = lp;
		continue;

	case CKET:
		braelist[*ep++] = lp;
		continue;

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

	case CDOT|STAR:
		curlp = lp;
		while (*lp++)
			;
		goto star;

	case CCHR|STAR:
		curlp = lp;
		while (*lp++ == *ep)
			;
		ep++;
		goto star;

	case CCL|STAR:
	case NCCL|STAR:
		curlp = lp;
		while (cclass(ep, *lp++, ep[-1]==(CCL|STAR)))
			;
		ep += *ep;
		goto star;

	star:
		do {
			lp--;
			if (advance(lp, ep))
				return(1);
		} while (lp > curlp);
		return(0);

	default:
		error(Q);
	}
}

int backref(int i, char *lp)
{
	char *bp;

	bp = braslist[i];
	while (*bp++ == *lp++)
		if (bp >= braelist[i])
			return(1);
	return(0);
}

int cclass(char *set, int c, int af)
{
	int n;

	if (c==0)
		return(0);
	n = *set++;
	while (--n)
		if (*set++ == c)
			return(af);
	return(!af);
}

char	line[70];
char	*linp	= line;
