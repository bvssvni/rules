#if 0
#!/bin/bash
clear
gcc -o test-rules *.c -Wall -Wfatal-errors -O3
if [ "$?" = "0" ]; then
	time ./test-rules
fi
exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "rules.h"

int main(int argc, char *argv[])
{
	return 0;
}