#include <stdio.h>

int main() {
	int i;
	int lscount;
	FILE *ls_output, *ls_count;
	char count_buf[8];
	char buf[256];
	char ls_buf[256][32];
	char *sick[32];

	system("/usr/bin/ls -a ~/dev/desk/weno > /tmp/weno");
	system("/usr/bin/ls -a ~/dev/desk/weno | /usr/bin/wc -l > /tmp/weno_count");

	ls_output = fopen("/tmp/weno", "r");
	fread(buf, 1, 256, ls_output);

	ls_count = fopen("/tmp/weno_count", "r");
	fread(count_buf, 8, 1, ls_count);
	lscount = atoi(count_buf);

	ls_output = fopen("/tmp/weno", "r");

	fread(buf, 256, 1, ls_output);
	printf("%s", buf);

	printf("count = %d\n", lscount);

	sick[0] = (char *)strtok(buf, "\n");
	for (i = 1; i < lscount; i++)
		sick[i] = (char *)strtok(NULL, "\n");
	for (i = 1; i < lscount; i++)
		printf("%s\n", sick[i]);
	return 0;
}

