make_math_test = find_program('make-math-test')
gen_libm_test = find_program('gen-libm-test.py')

libm_test_ulps_h = custom_target('libm-test-ulps.h',
				 input: ['../picolibc/arm/libm-test-ulps'],
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
  'cos',
  'cosh',
  'erf',
  'erfc',
  'exp',
  'exp10',
  'exp2',
  'expm1',
  'fma',
  'hypot',
  'log',
  'log10',
  'log1p',
  'log2',
  'pow',
  'sin',
  'sincos',
  'sinh',
  'sqrt',
  'tan',
  'tanh',
]

# picolibc has terrible implementations of these codes
# the poor accuracy also leads to missing boundary
# conditions for over/underflow
tests_broken = [
  'j0',
  'j1',
  'jn',
  'lgamma',
  'tgamma',
  'y0',
  'y1',
  'yn',
  ]

types = ['float', 'double']

foreach type : types

  support_src = 'libm-test-support-' + type + '.c'

  test_type_h = 'test-' + type + '.h'

  support_c = custom_target(support_src,
			    input: [test_type_h, 'libm-test-support.c'],
			    output: [support_src],
			    command: [make_math_test, '@OUTPUT@', '@INPUT@'])

  foreach test : tests

    libm_test_head = 'libm-test-' + test

    libm_test_src = libm_test_head + '.c'

    libm_test_inc = libm_test_head + '.inc'

    gen_test_name = 'gen_test_' + test

    if type == types[0]
      auto_file = 'auto-libm-test-out-' + test
      gen_test = custom_target(libm_test_src,
			       input: [libm_test_inc, auto_file],
			       output: [libm_test_src],
			       command : [gen_libm_test, '-c', '@INPUT0@', '-a', '@INPUT1@', '-C', '@OUTPUT@']
			      )
      set_variable(gen_test_name, gen_test)
    endif

    gen_test = get_variable(gen_test_name)

    test_name = 'test-' + type + '-' + test

    test_src = test_name + '.c'

    test_wrap = custom_target(test_src,
			      input: [test_type_h, 'test-math-exceptions.h',
				      'test-math-errno.h', 'test-math-scalar.h', gen_test],
			      output: [test_src],
			      command : [make_math_test, '@OUTPUT@', '@INPUT@'])

    test(test_name,
	 executable(test_name,
		    [test_wrap, support_c, libm_test_ulps_h],
		    include_directories: inc,
		    c_args: c_args,
		    link_with: [lib_argp, lib_posix]),
	 env: ['MESON_SOURCE_ROOT=' + meson.source_root()],
	)
  endforeach
endforeach
