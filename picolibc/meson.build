srcs_posix = [
  '../posix/getopt.c',
  '../posix/getopt1.c',
  'error.c',
]

lib_posix = static_library('posix',
			  srcs_posix,
			  pic: false,
			  include_directories: inc,
			  c_args: c_args)
