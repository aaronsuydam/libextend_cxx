project('libextend', 'cpp', version : '1.0', default_options : ['warning_level=3', 'cpp_std=c++17'])

source_files = [
  'src/cpu_stat.cpp',
]

include_directories = include_directories('include')

# Declare a shared library
libextend = library('libextend', source_files,
  include_directories : include_directories,
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

test_cpu_stats = executable('test_cpu_stats', ['test/test_cpu_stats.cpp', 'src/cpu_stat.cpp'],
  include_directories : include_directories,
  dependencies : [libextend_dep, boost_test_dep]
)
