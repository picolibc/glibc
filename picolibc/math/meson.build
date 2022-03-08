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
make_math_test = find_program('make-math-test')
gen_libm_test = find_program('../../math/gen-libm-test.py')

libm_test_ulps_h = custom_target('libm-test-ulps.h',
				 input: ['..' / cpu / 'libm-test-ulps'],
				 output: ['libm-test-ulps.h'],
				 command: [gen_libm_test, '-u', '@INPUT@', '-H', '@OUTPUT@'])

tests = [
  'acos',
  'acosh',
  'asin',
  'asinh',
  'atan',
  'atan2',
  'atanh',
  'cabs',
  'cbrt',
  'ceil',
  'copysign',
  'cos',
  'cosh',
  'erf',
  'erfc',
  'exp',
  'exp10',
  'exp2',
  'expm1',
  'fabs',
  'fdim',
  'floor',
  'fma',
  'fmax',
  'fmin',
  'fmod',
  'fpclassify',
  'frexp',
  'getpayload',
  'isfinite',
  'isinf',
  'isnan',
  'isnormal',
  'issubnormal',
  'isunordered',
  'hypot',
  'ilogb',
  'j0',
  'j1',
  'log',
  'log10',
  'log1p',
  'log2',
  'logb',
  'lrint',
  'lround',
  'modf',
  'nearbyint',
  'nextafter',
  'pow',
  'remainder',
  'remquo',
  'rint',
  'round',
  'scalb',
  'scalbn',
  'scalbln',
  'signbit',
  'significand',
  'sin',
  'sincos',
  'sinh',
  'sqrt',
  'tan',
  'tanh',
  'trunc',
  'y0',
  'y1',
]

tests_ldbl = [
  'nexttoward',
  ]

if ldbl_eq_dbl
  tests += tests_ldbl
endif

# picolibc has terrible implementations of these codes
# the poor accuracy also leads to missing boundary
# conditions for over/underflow
tests_broken = [
  'jn',
  'yn',
  'lgamma',
  'tgamma',
  ]

types = ['float', 'double']

foreach type : types

  support_src = 'libm-test-support-' + type + '.c'

  test_type_h = '../../math' / 'test-' + type + '.h'

  support_c = custom_target(support_src,
			    input: [test_type_h, '../../math/libm-test-support.c'],
			    output: [support_src],
			    command: [make_math_test, '@OUTPUT@', '@INPUT@'])

  foreach test : tests

    libm_test_head = 'libm-test-' + test

    libm_test_src = libm_test_head + '.c'

    libm_test_inc = '../../math' / libm_test_head + '.inc'

    gen_test_name = 'gen_test_' + test

    if type == types[0]
      auto_file = '../../math' / 'auto-libm-test-out-' + test
      if fs.is_file(auto_file)
	gen_test = custom_target(libm_test_src,
				 input: [libm_test_inc, auto_file],
				 output: [libm_test_src],
				 command : [gen_libm_test, '-c', '@INPUT0@', '-a', '@INPUT1@', '-C', '@OUTPUT@']
				)
      else
	gen_test = custom_target(libm_test_src,
				 input: [libm_test_inc],
				 output: [libm_test_src],
				 command : [gen_libm_test, '-c', '@INPUT0@', '-C', '@OUTPUT@']
				)
      endif
	
      set_variable(gen_test_name, gen_test)
    endif

    gen_test = get_variable(gen_test_name)

    test_name = 'test-' + type + '-' + test

    test_src = test_name + '.c'

    test_wrap = custom_target(test_src,
			      input: [test_type_h, '../../math/test-math-exceptions.h',
				      '../../math/test-math-errno.h', '../../math/test-math-scalar.h', gen_test],
			      output: [test_src],
			      command : [make_math_test, '@OUTPUT@', '@INPUT@'])

    foreach target : targets

      value = get_variable('target_' + target)
      
      _c_args = value[1] + c_args

      if target == ''
	_test_ext = ''
      else
	_test_ext = '_' + target
      endif

      _test_name = test_name + _test_ext
      _lib_argp = get_variable('argp' + _test_ext)
      
      test(_test_name,
	   executable(_test_name,
		      [test_wrap, support_c, libm_test_ulps_h],
		      include_directories: inc,
		      c_args: _c_args,
		      link_args: _c_args,
		      link_with: [_lib_argp]),
	   env: ['MESON_SOURCE_ROOT=' + meson.source_root()],
	  )
    endforeach
  endforeach
endforeach
