/**
 * Version of software
 */

#ifndef _VERSION_H
#define _VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#define _VERSION "v0.0.1"

#ifdef GIT_HEAD
#define _VERSION_WRAPPER     \
    "commit hash: " GIT_HEAD \
    "\r\n"                   \
    "version: " _VERSION
#else
#define _VERSION_WRAPPER "version: " _VERSION
#endif

#define VERSION                    \
    ("        R       C      \r\n" \
     "      _____            \r\n" \
     "   __|     |___| |___  \r\n" \
     "     |_____|   | |     \r\n" \
     "\r\n" _VERSION_WRAPPER "\r\n")

#ifdef __cplusplus
}
#endif

#endif  // _VERSION_H
