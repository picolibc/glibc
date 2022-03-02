tests = [
  'tst-dbl-efgcvt',
  'tst-dirname',
  'tst-hsearch',
  ]

foreach t : tests
  test(t,
       executable(t,
		  [t + '.c', '../../picolibc/support_test_main.c'],
		  include_directories: inc,
		  c_args: c_args,
		  link_with: [lib_support, lib_posix]
		 ),
       env: ['MESON_SOURCE_ROOT=' + meson.source_root()]
      )
endforeach
