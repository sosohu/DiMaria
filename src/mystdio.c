#include "unix/mystdio.h"

void cat_buf(int buffersize)
{
	int n;
	char buf[buffersize];

	while((n = read(STDIN_FILENO, buf, buffersize)) > 0)
		if(write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");
	
	if(n < 0)
		err_sys("read error");
	
}

void cat(void)
{
	int c;
	while(( c = getc(stdin) != EOF))
		if((EOF == putc(c, stdout)))
			err_sys("output eeror");
	if(ferror(stdin))
		err_sys("input error");
}
