project('libextend', 'cpp', version : '1.0', default_options : ['warning_level=3', 'cpp_std=c++17'])

# Define the library name and sources
lib_name = 'libextend'
include_dir = meson.source_root() / 'include'
src_dir = meson.current_source_dir() / 'src'
source_files = run_command('find', src_dir, '-type', 'f', '-name', '*.cpp').stdout().strip().split()
source_files = run_command('find', include_dir, '-type', 'f', '-name', '*.hpp').stdout().strip().split()



# Define include directories
include_directories = include_directories('include')

# Declare a shared library
library(lib_name, lib_sources,
  include_directories : include_directories,
  soversion : '0', # ABI version
)

# Specify headers and their installation
install_headers(lib_headers, subdir : 'libexample')

# Tests
# If you have tests, you can set them up here
test_dir = include_directories('test')
test_sources = files('test/random_engines_testing.cpp', 'test/test.cpp') # Add all test source files here
test_executable = executable('test_runner', test_sources,
                             include_directories : test_dir,
                             dependencies : [library(lib_name)])
test('test_runner', test_executable)

# Installation directories
install_dir_lib = get_option('libdir')
install_dir_include = get_option('includedir') / 'libexample'

# Install the library
install_target(library(lib_name), dir : install_dir_lib)

# Install the headers
foreach h : lib_headers
  install_header(h, subdir : 'libexample')
endforeach
