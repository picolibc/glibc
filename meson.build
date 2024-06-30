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

cpu_family = host_machine.cpu_family()
cpu = host_machine.cpu()

enable_multilib = get_option('multilib')
multilib_list = get_option('multilib-list')

ldbl_eq_dbl = cc.sizeof('double') == cc.sizeof('long double')

inc_dirs = ['sysdeps/wordsize-32', 'support', '.', 'picolibc', 'sysdeps' / cpu_family, 'sysdeps/generic']

c_args = ['-include', '@0@/@1@'.format(meson.current_source_dir(), 'picolibc/hacks.h'), '-g']

c_args += get_option('extra-c-args')

c_args += cc.get_supported_arguments(['-frounding-math', '-fsignaling-nans', '-fno-builtin'])

picolibc_buildtype = get_option('picolibc-buildtype')

if picolibc_buildtype != ''
  c_args += '--picolibc-buildtype=' + picolibc_buildtype
endif

inc = include_directories(inc_dirs)

targets = []

if enable_multilib
  used_libs = []

  # Ask the compiler for the set of available multilib configurations,
  # set up the build system to compile for all desired ones
  foreach target : run_command(cc, '--print-multi-lib', check : true).stdout().strip().split('\n')
    _tmp = target.split(';')

    _arch_flags = []
    # Let the user specify a subset of the possible multilib
    # configurations to build for
    if multilib_list == [] or _tmp[0] in multilib_list
      used_libs += _tmp[0]
      if _tmp[0].contains('pacbti')
	continue
      endif
      if _tmp.length() > 1
	foreach flag : _tmp[1].strip('@').split('@')
	  if flag != ''
	    _arch_flags += '-' + flag
	  endif
	endforeach
	if _tmp[0] == '.'
	  name = ''
	else
	  name = _tmp[0].underscorify()
	endif
      else
	name = ''
      endif
      targets += name

      # rv64 needs to use a non-default mcmodel so that variables can
      # live in a broader range of memory addresses
      if name.startswith('rv64')
	_arch_flags += [ '-mcmodel=medany' ]
      endif

      _link_flags = _arch_flags + meson.get_cross_property('link_args_' + name, [])

      # Add any extra flags for this target from the cross file
      _c_flags = c_args + _arch_flags + meson.get_cross_property('c_args_' + name, [])

      set_variable('target_' + name, [_tmp[0], _c_flags, _link_flags])
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
  target_name = get_option('target-name')
  if target_name == ''
    multi_dir = run_command(cc, c_args + '--print-multi-directory', check : false)
    target_name = multi_dir.stdout().strip().split('\n')[0].underscorify()
    message('Target name computed as "' + target_name + '"')
  endif
  targets = [target_name]
  set_variable('target_' + target_name,
	       ['.', c_args])
endif

# support libraries
subdir('picolibc/posix')
subdir('support')
subdir('argp')

# directories with tests
subdir('benchtests')
subdir('gnulib')
subdir('malloc')
subdir('picolibc/ctype')
subdir('picolibc/iconv')
subdir('picolibc/libio')
subdir('picolibc/math')
subdir('picolibc/misc')
subdir('picolibc/setjmp')
subdir('picolibc/stdlib')
subdir('picolibc/string')
subdir('picolibc/wcsmbs')
subdir('stdio-common')
