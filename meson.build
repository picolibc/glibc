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

inc_dirs = ['sysdeps/wordsize-32', 'support', '.', 'picolibc', 'sysdeps/generic']

c_args = ['-include', '@0@/@1@'.format(meson.current_source_dir(), 'picolibc/hacks.h')]

c_args += cc.get_supported_arguments(['-frounding-math', '-fsignaling-nans', '-fno-builtin'])

inc = include_directories(inc_dirs)

cpu_family = host_machine.cpu_family()
cpu = host_machine.cpu()

subdir('picolibc')
subdir('support')
subdir('argp')
subdir('malloc')
subdir('math')
subdir('picolibc/misc')
subdir('stdio-common')
