project('libextend', 'cpp', version : '1.0', default_options : ['warning_level=3', 'cpp_std=c++23'])

use_asan = get_option('use_asan')

cpp_flags = []
ld_flags = []

if use_asan
    cpp_flags = ['-fsanitize=address', '-fsanitize-coverage=full', '-fno-omit-frame-pointer']
    ld_flags = ['-fsanitize=address']
endif

cc = meson.get_compiler('cpp')


source_files = [
  'src/cpu_stat.cpp',
]

include_directories = include_directories('include')

# Declare a shared library
libextend = library('extend', source_files,
  include_directories : include_directories,
  cpp_args : cpp_flags,
  link_args : ld_flags,
  soversion : '0', # ABI version
)


# Declare libextend dependency
libextend_dep = declare_dependency(
  include_directories : include_directories,
  link_with : libextend,
  dependencies : [],
)

# Declare boost dependency
# Find Boost.Test
boost_test_dep = dependency('boost', modules : ['unit_test_framework'])
gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.10.0')

test_cpu_stats = executable('test_cpu_stats', ['test/cpu_stats_test.cpp'],
  include_directories : include_directories,
  cpp_args : cpp_flags,
  link_args : ld_flags,
  dependencies : [libextend_dep, boost_test_dep],
)

test_vector_utils = executable('test_vector_utils', ['test/vector_utils_test.cpp'],
  include_directories : include_directories,
  cpp_args : cpp_flags,
  link_args : ld_flags,
  dependencies : [libextend_dep, boost_test_dep],
)

# Define a test to run the executable
test('vector_utils_test', test_vector_utils)

subdir('./src/linux/gui')