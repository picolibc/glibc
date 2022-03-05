tests = [
  'tst-calloc',
  'tst-free-errno',
  'tst-malloc',
  'tst-malloc-too-large',
  'tst-mcheck',
  'tst-memalign',
  'tst-posix_memalign',
  'tst-pvalloc',
  'tst-pvalloc-fortify',
  'tst-valloc',
  ]

tests_broken = [
  'tst-malloc-usable', # malloc_usable_size may return more than malloc was given
]
foreach t : tests
  test(t,
       executable(t,
		  [t + '.c', '../picolibc/support_test_main.c'],
		  include_directories: inc,
		  c_args: c_args + ['-Wno-alloc-size-larger-than'],
		  link_with: [lib_support, lib_posix]
		 ),
       env: ['MESON_SOURCE_ROOT=' + meson.source_root()]
      )
endforeach
