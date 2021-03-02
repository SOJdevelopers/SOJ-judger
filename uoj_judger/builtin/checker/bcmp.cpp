#include <cstdio>

inline const char *englishEnding(int x) {
	x %= 100;
	if (x / 10 == 1)
		return "th";
	if (x % 10 == 1)
		return "st";
	if (x % 10 == 2)
		return "nd";
	if (x % 10 == 3)
		return "rd";
	return "th";
}

int main(int argc, char * argv[]) {
	if (argc != 4)
		return 1;
	FILE *fout = fopen(argv[2], "r");
	FILE *fans = fopen(argv[3], "r");

	if (fout == NULL || fans == NULL)
		return 1;

	int n = 0, ch;
	for (; ; ) {
		int c = fgetc(fout), d = fgetc(fans);
		if (c == EOF && d == EOF) break;
		++n;
		if (c != d) {
			if (c == EOF)
				fprintf(stderr, "wrong output format Unexpected end of file - byte expected\n");
			else if (d == EOF)
				fprintf(stderr, "wrong output format Extra information in the output file\n");
			else
				fprintf(stderr, "wrong answer %d%s bytes differ - expected '%c', found '%c'\n", n, englishEnding(n), (char)d, (char)c);
			return 1;
		}
		ch = c;
	}

	if (n == 0)
		fprintf(stderr, "ok empty file\n");
	else if (n == 1)
		fprintf(stderr, "ok single byte: '%c'\n", ch);
	else
		fprintf(stderr, "ok %d bytes\n", n);
	return 0;
}
