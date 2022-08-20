#include "test-tool.h"
#include "trace.h"

int cmd__random_port(int argc, const char **argv)
{
	int min, max, port;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <min> <max>\n", argv[0]);
		return 1;
	}

	min = atoi(argv[1]);
	max = atoi(argv[2]);

	srand(getnanotime());
	port = (rand() % (max - min + 1)) + min;

	printf("%d\n", port);

	return 0;
}
