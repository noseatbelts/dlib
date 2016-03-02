#ifndef O_IO_UTIL_H
#define O_IO_UTIL_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <zlib.h>
#include "logging_util.h"


#ifdef __cplusplus
extern "C" {
#endif
// FUNCTIONS
// Function Declarations
int isfile(char *fname); // True if file exists.
int bash_system(const char *command); // Call command with bash instead of sh
#ifdef __cplusplus
int my_system (const char *command, const char *executable="/bin/bash");
#else
int my_system (const char *command, const char *executable);
#endif

FILE *open_ofp(char *infname);
FILE *open_ifp(char *infname);
int file_has_ext(char *fn, const char *ext);
int is_bgzipped_vcf(char *fn);

// Inline Function Definitions
static inline gzFile open_gzfile(char *infname) {
    if(strcmp(infname, "-") == 0 || strcmp(infname, "stdin") == 0) {
        LOG_DEBUG("Reading from standard in because infname is %s.\n", infname);
        return gzdopen(STDIN_FILENO, "r"); // Opens stdin.
    } else {
        LOG_DEBUG("Reading from %s.\n", infname);
        return gzopen(infname, "r");
    }
}

/* check_popen
 * Executes cmd with popen and exits if it returns a non-zero exit status.
 * cmd [arg/char *] Command to execute via popen
 */
static void check_popen(const char *cmd) {
    LOG_DEBUG("Now check popen-ing command '%s'.\n", cmd);
    int ret;
    if((ret = pclose(popen(cmd, "w"))) != 0) {
        LOG_EXIT("System call failed. Command: '%s'. Return code: %i.\n", cmd, ret);
    }
}

/* check_call
 * Executes cmd with system and exits if it returns a non-zero exit status.
 * cmd [arg/char *] Command to execute via popen
 */
static void check_call(const char *cmd) {
    LOG_DEBUG("Now check calling command '%s'.\n", cmd);
    int ret;
    if((ret = system(cmd)) != 0) {
        LOG_EXIT("System call failed. Command: '%s'. Return code: %i.\n", cmd, ret);
    }
}

int count_lines(char *fname);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
