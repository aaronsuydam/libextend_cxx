project('libextend', 'cpp', version : '1.0', default_options : ['warning_level=3', 'cpp_std=c++23'])

use_asan = get_option('use_asan')

cpp_flags = []
ld_flags = []

if use_asan
    cpp_flags = ['-fsanitize=address', '-fsanitize-coverage=full', '-fno-omit-frame-pointer']
    ld_flags = ['-fsanitize=address']
endif

python_dep = dependency('python', modules : ['matplotlib'], required : true)
cc = meson.get_compiler('cpp')
libpython = cc.find_library('python3.12', required : true) 

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

test_cpu_stats = executable('test_cpu_stats', ['test/test_cpu_stats.cpp'],
  include_directories : include_directories,
  cpp_args : cpp_flags,
  link_args : ld_flags,
  dependencies : [libextend_dep, boost_test_dep, python_dep, libpython],
)
