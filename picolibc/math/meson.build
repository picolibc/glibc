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

libm_tests = [
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
]

libm_tests_float_double = [
  'j0',
  'j1',
  'y0',
  'y1',
  ]

libm_tests_ldbl = [
  'nexttoward',
  ]

libm_tests += libm_tests_ldbl

# picolibc has terrible implementations of these codes
# the poor accuracy also leads to missing boundary
# conditions for over/underflow
libm_tests_broken = [
  'jn',
  'yn',
  'lgamma',
  'tgamma',
  ]

fenv_tests = [
  'test-femode',
  'test-femode-traps',
  'test-fenv-clear',
  'test-fenv-preserve',
  'test-fenv-return',
  'test-fesetexcept',
  'test-fesetexcept-traps',
  'test-fexcept',
  'test-fexcept-traps',
  ]

bare_tests = [
  'test-flt-eval-method',
  'test-fp-ilogb-constants',
  'test-fpucw',
  'test-fpucw-ieee',
  'test-fpucw-ieee-static',
  'test-fpucw-static',
  'test-iseqsig-excess-precision',
  'test-iszero-excess-precision',
  'test-nan-overflow',
  'test-narrow-macros',
  'test-nearbyint-except-2',
  'test-nearbyint-except',
  'test-signgam-uchar',
  'test-signgam-uchar-init',
  'test-signgam-uchar-static',
  'test-signgam-uint',
  'test-signgam-uint-init',
  'test-signgam-uint-static',
  'test-signgam-ullong',
  'test-signgam-ullong-init',
  'test-signgam-ullong-static',
  'test-snan',
  ] + fenv_tests

broken_bare_tests = [
  'test-nan-const', # expects nanf to do something with the payload
  'test-nan-payload', # expects strtof to also do something with payload
  ]
  
extra_c_flags = {
		  'test-signgam-uchar' : ['-std=c99', '-DNO_GNU_SOURCE'],
		  'test-signgam-uchar-init' : ['-std=c99', '-DNO_GNU_SOURCE'],
		  'test-signgam-uchar-static' : ['-std=c99', '-DNO_GNU_SOURCE'],
		  'test-signgam-uint' : ['-std=c99', '-DNO_GNU_SOURCE'],
		  'test-signgam-uint-init' : ['-std=c99', '-DNO_GNU_SOURCE'],
		  'test-signgam-uint-static' : ['-std=c99', '-DNO_GNU_SOURCE'],
		  'test-signgam-ullong' : ['-std=c99', '-DNO_GNU_SOURCE'],
		  'test-signgam-ullong-init' : ['-std=c99', '-DNO_GNU_SOURCE'],
		  'test-signgam-ullong-static' : ['-std=c99', '-DNO_GNU_SOURCE'],
		}


foreach test_name : bare_tests

  test_src = '../../math' / test_name + '.c'

  foreach target : targets

    value = get_variable('target_' + target)
    
    _c_args = value[1]
    _link_args = value[2]

    if target == '' or target == '_'
      _test_ext = ''
    else
      _test_ext = '_' + target
    endif

    _type = ''

    if fenv_tests.contains(test_name)
      _type = '_fenvtest'
    endif

    _test_name = test_name + _type + _test_ext

    _lib_argp = get_variable('argp' + _test_ext)
    
    _test_c_args = []

    if test_name in extra_c_flags
      _test_c_args = extra_c_flags[test_name]
    endif

    support_name = 'support_test_main' + test_name + _test_ext

    support_test_main_lib = static_library(support_name,
					   '../support_test_main.c',
					   include_directories: inc,
					   c_args: _c_args)

    support_test_main_o = support_test_main_lib.extract_all_objects(recursive: true)

    test(_test_name,
	 executable(_test_name,
		    [test_src],
		    objects: support_test_main_o,
		    include_directories: inc,
		    c_args: _c_args + _test_c_args,
		    link_args: _link_args + _test_c_args),
	 env: ['MESON_SOURCE_ROOT=' + meson.source_root()]
	)
  endforeach
endforeach

types = ['float', 'double', 'ldouble']

foreach type : types

  support_src = 'libm-test-support-' + type + '.c'

  test_type_h = '../../math' / 'test-' + type + '.h'

  support_c = custom_target(support_src,
			    input: [test_type_h, '../../math/libm-test-support.c'],
			    output: [support_src],
			    command: [make_math_test, '@OUTPUT@', '@INPUT@'])

  tests = libm_tests

  if type != 'ldouble'
    tests += libm_tests_float_double
  endif

  foreach libm_test : tests

    libm_test_head = 'libm-test-' + libm_test

    libm_test_src = libm_test_head + '.c'

    libm_test_inc = '../../math' / libm_test_head + '.inc'

    gen_test_name = 'gen_test_' + libm_test

    if type == types[0]
      auto_file = '../../math' / 'auto-libm-test-out-' + libm_test
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

    test_name = 'test-' + type + '-' + libm_test

    test_src = test_name + '.c'

    test_wrap = custom_target(test_src,
			      input: [test_type_h, '../../math/test-math-exceptions.h',
				      '../../math/test-math-errno.h', '../../math/test-math-scalar.h', gen_test],
			      output: [test_src],
			      command : [make_math_test, '@OUTPUT@', '@INPUT@'])

    foreach target : targets

      value = get_variable('target_' + target)
      
      _c_args = value[1]
      _link_args = value[2]

      if target == '' or target == '_'
	_test_ext = ''
      else
	_test_ext = '_' + target
      endif

      _test_name = test_name + _test_ext
      _lib_argp = get_variable('argp' + _test_ext)
      _lib_posix = get_variable('posix' + _test_ext)
      
      test(_test_name,
	   executable(_test_name,
		      [test_wrap, support_c, libm_test_ulps_h],
		      include_directories: inc,
		      c_args: _c_args,
		      link_args: _link_args,
		      link_with: [_lib_argp, _lib_posix]),
	   env: ['MESON_SOURCE_ROOT=' + meson.source_root()],
	   suite: 'math'
	  )
    endforeach
  endforeach

endforeach
