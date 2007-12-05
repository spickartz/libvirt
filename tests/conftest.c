#include "config.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "conf.h"

int main(int argc, char **argv) {
    int ret;
    virConfPtr conf;
    int len = 10000;
    char buffer[10000];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s conf_file\n", argv[0]);
	exit(1);
    }

    conf = virConfReadFile(argv[1]);
    if (conf == NULL) {
        fprintf(stderr, "Failed to process %s\n", argv[1]);
	exit(2);
    }
    ret = virConfWriteMem(&buffer[0], &len, conf);
    if (ret < 0) {
        fprintf(stderr, "Failed to serialize %s back\n", argv[1]);
	exit(3);
    }
    virConfFree(conf);
    if (fwrite(buffer, 1, len, stdout) != len) {
	fprintf(stderr, "Write failed: %s\n", strerror (errno));
	exit(1);
    }
    exit(0);
}
