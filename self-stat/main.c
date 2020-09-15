#include "self_stat.h"
#include <stdio.h>
#include <stdlib.h>

static void print_str(char * str, void * context)
{
	fputs(str, stdout);
}

static void equit(const char * which)
{
	fprintf(stderr, "error reading %s\n", which);
	exit(EXIT_FAILURE);
}

int main(void)
{
	sst_proc_stat ps = {0};
	
	if (sst_read_self_stat(&ps))
		sst_print_self_stat(&ps, stderr);
	else
		equit("/proc/self/stat");
	
	putchar('\n');
	sst_proc_statm psm = {0};
	if (sst_read_self_statm(&psm))
		sst_print_self_statm(&psm, stderr);
	else
		equit("/proc/self/statm");
		
	putchar('\n');
	if (!sst_read_self_status(print_str, NULL))
		equit("/proc/self/status");
	
	putchar('\n');
	if (!sst_read_self_smaps(print_str, NULL))
		equit("/proc/self/smaps");
		
	return 0;
}
