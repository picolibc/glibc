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

enable_multilib = get_option('multilib')
multilib_list = get_option('multilib-list')

ldbl_eq_dbl = cc.sizeof('double') == cc.sizeof('long double')

inc_dirs = ['sysdeps/wordsize-32', 'support', '.', 'picolibc', 'sysdeps/generic']

c_args = ['-include', '@0@/@1@'.format(meson.current_source_dir(), 'picolibc/hacks.h')]

c_args += cc.get_supported_arguments(['-frounding-math', '-fsignaling-nans', '-fno-builtin'])

inc = include_directories(inc_dirs)

cpu_family = host_machine.cpu_family()
cpu = host_machine.cpu()

targets = []

if enable_multilib
  used_libs = []

  # Ask the compiler for the set of available multilib configurations,
  # set up the build system to compile for all desired ones
  foreach target : run_command(cc, '--print-multi-lib', check : true).stdout().strip().split('\n')
    tmp = target.split(';')
    flags = c_args

    # Let the user specify a subset of the possible multilib
    # configurations to build for
    if multilib_list == [] or tmp[0] in multilib_list
      used_libs += tmp[0]
      if tmp.length() > 1
	foreach flag : tmp[1].strip('@').split('@')
	  if flag != ''
	    flags += '-' + flag
	  endif
	endforeach
	if tmp[0] == '.'
	  name = ''
	else
	  name = tmp[0].underscorify()
	endif
      else
	name = ''
      endif
      targets += name

      # rv64 needs to use a non-default mcmodel so that variables can
      # live in a broader range of memory addresses
      if name.startswith('rv64')
	flags += [ '-mcmodel=medany' ]
      endif

      # Add any extra flags for this target from the cross file
      flags += meson.get_cross_property('c_args_' + name, [])

      value = [tmp[0], flags]
      set_variable('target_' + name, value)
    endif
  endforeach

  # Make sure all requested multilib configurations
  # are actually available
  if multilib_list != []
    foreach lib : multilib_list
      if lib not in used_libs
	error('Unavailable multilib: ' + lib)
      endif
    endforeach
  endif
else
  targets = ['']
  target_ = ['.', c_args]
endif

subdir('picolibc/posix')
subdir('support')
subdir('argp')
subdir('malloc')
subdir('picolibc/math')
subdir('picolibc/misc')
subdir('picolibc/ctype')
subdir('stdio-common')
