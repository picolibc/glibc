project('glibc-test', 'c',
	default_options: [
	  'buildtype=debug',
	  'debug=true',
	],
	license : 'LGPL',
	version: '0.1'
       )
	  
cc = meson.get_compiler('c')
fs = import('fs')

inc_dirs = ['test-include', 'sysdeps/wordsize-32', 'support', '.', 'picolibc', 'sysdeps/generic']

c_args = ['-include', '@0@/@1@'.format(meson.current_source_dir(), 'picolibc/hacks.h')]

inc = include_directories(inc_dirs)

subdir('picolibc')
subdir('support')
subdir('argp')
subdir('math')
subdir('stdio-common')
