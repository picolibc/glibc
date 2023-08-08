# 
#  SPDX-License-Identifier: BSD-3-Clause
# 
#  Copyright © 2022 Keith Packard
# 
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
# 
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 
#  2. Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
# 
#  3. Neither the name of the copyright holder nor the names of its
#     contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
# 
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
#  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
#  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
#  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
#  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
#  OF THE POSSIBILITY OF SUCH DAMAGE.
#
tests = [
  'test-fseek',
  'test-fwrite',
  'test_rdwr',
  'tst-fdopen',
  'tst-fgets',
  'tst-fphex',
  'tst-fphex-wide',
  'tst-fseek',
  'tst-fwrite',
  'tst-gets',
  'tst-long-dbl-fphex',
  'tst-printf',
  'tst-printf-fp-free',
  'tst-printf-fp-leak',
  'tst-put-error',
  'tst-rndseek',
  'tstscanf',
  'tst-scanf-round',
  'tst-setvbuf1',
  'tst-sprintf',
#  'tst-swprintf',
  'tst-swscanf',
  'tst-sscanf',
  'tst-tmpnam',
  'tst-ungetc',
  ]

tests_ldbl = [
  'tst-sprintf2',
  'tst-sprintf3',
]

if ldbl_eq_dbl
  tests += tests_ldbl
endif

tests_slow = [
  'tst-vfprintf-width-prec-alloc',
  ]

foreach test_name : tests

  args = []

  test_input = test_name + '.input'
  if fs.is_file(test_input)
    args += [meson.current_source_dir() / test_input]
  endif

  foreach target : targets

    value = get_variable('target_' + target)
    
    if target == '' or target == '_'
      _test_ext = ''
    else
      _test_ext = '_' + target
    endif

    _test_name = test_name + _test_ext
    _lib_support = get_variable('support' + _test_ext)
    _lib_posix = get_variable('posix' + _test_ext)
    
    _c_args = value[1] + ['-DOBJPFX="' + meson.current_source_dir() / _test_name + '_"']
    _link_args = value[2]

    test(_test_name,
	 executable(_test_name,
		    [test_name + '.c', '../picolibc/support_test_main.c'],
		    include_directories: inc,
		    c_args: _c_args,
		    link_args: _link_args,
		    link_with: [_lib_support, _lib_posix]
		   ),
	 args: args,
	 env: ['MESON_SOURCE_ROOT=' + meson.source_root()]
	)
  endforeach
endforeach
