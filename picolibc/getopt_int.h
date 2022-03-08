/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright © 2022 Keith Packard
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GETOPT_INT_H
#define GETOPT_INT_H

/* macros defined by this include file */
#define NO_ARG          	no_argument
#define REQUIRED_ARG    	required_argument
#define OPTIONAL_ARG    	optional_argument

/* The GETOPT_DATA_INITIALIZER macro is used to initialize a statically-
   allocated variable of type struct getopt_data.  */
#define _GETOPT_DATA_INITIALIZER	{0,0,0,0,0,0,0}

/* The getopt_data structure is for reentrancy. Its members are similar to
   the externally-defined variables.  */

struct _getopt_data
{
    char *optarg;
    int optind, opterr, optopt, optwhere;
    int permute_from, num_nonopts;
};

int __getopt_r (int __argc, char *const __argv[], const char *__optstring,
                struct _getopt_data * __data);

int __getopt_long_r (int __argc, char *const __argv[], const char *__shortopts,
                     const struct option * __longopts, int *__longind,
                     struct _getopt_data * __data);

int __getopt_long_only_r (int __argc, char *const __argv[], const char *__shortopts,
                          const struct option * __longopts, int *__longind,
                          struct _getopt_data * __data);

#define _getopt_r __getopt_r
#define _getopt_long_r __getopt_long_r
#define _getopt_long_only_r __getopt_long_only_r

#define _getopt_initialize(a, b, c, d, e)	(c)

#endif /* GETOPT_INT_H */
