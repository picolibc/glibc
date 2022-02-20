srcs_support = [
  'support_record_failure.c',
  'support_test_compare_failure.c',
  'support_test_verify_impl.c',
  'write_message.c',
]

lib_support = static_library('support',
			  srcs_support,
			  pic: false,
			  include_directories: inc,
			  c_args: c_args)
