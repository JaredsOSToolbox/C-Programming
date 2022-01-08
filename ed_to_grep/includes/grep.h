#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

const int BLKSIZE = 4096, LBSIZE = 4096;
const int CBACK = 14;
const int CBRA = 1;
const int CCHR = 2;
const int CCIRC = 15;
const int CCL = 6;
const int CDOL = 10;
const int CDOT = 4;
const int CEOF = 11;
const int CKET = 12;
const int ESIZE = 256, GBSIZE = 256;
const int FNSIZE = 128;
const int KSIZE = 9;
const int NBLK = 2047;
const int NBRA = 5;
const int NCCL = 8;
const int READ = 0;
const int STAR = 01;
const int WRITE = 1;

char Q[] = "", T[] = "TMP";
char savedfile[FNSIZE], file[FNSIZE], linebuf[LBSIZE], rhsbuf[LBSIZE / 2],
    expbuf[ESIZE + 4], file_contents[LBSIZE], our_expression_buffer[BUFSIZ],
    buf[BUFSIZ], input[BUFSIZ], ibuff[BLKSIZE], obuff[BLKSIZE];
unsigned int *addr1, *addr2, *dot, *dol, *zero;
long count;
char *nextip, *linebp, *globp, *tfname, *loc1, *loc2;
int ninbuf, io, pflag, vflag = 1, oflag, listf, listn, col, tfile = -1, tline,
                       buffer_pointer;
int names[26];
int iblock = -1, oblock = -1, ichanged, nleft, anymarks, nbra, subnewa, subolda,
    fchange, wrapp, bpagesize = 20, peekc, lastc, given,
    current_line_number = 0;
char *braslist[NBRA], *braelist[NBRA];
unsigned nlall = 10000;

char *getblock(unsigned int atl, int iof);
char *getline_(unsigned int tl);
int advance(char *lp, char *ep);
int append(int (*f)(void), unsigned int *a);
int backref(int i, char *lp);
int cclass(char *set, int c, int af);
int execute(unsigned int *addr);
int getchr(void);
int getfile(void);
int getnum(void);
int putline(void);
unsigned int *address(void);
void blkio(int b, char *buf, int (*iofcn)(int, char *, int));
void commands(void);
void compile(int eof);
void detach_file(void);
void error(char *s);
void filename(int comm);
void global(int k);
void grepping();
void init(void);
void newline(void);
void nonzero(void);
void onhup(int n);
void print(void);
void putfile(void);
void quit(int n);
void read_in_file(char *input);
void search_file(char *file_name);
void searchdir(const char *name);
void setnoaddr(void);
void setwide(void);
void squeeze(int i);
void zero_squeeze(void) { squeeze(0); }
