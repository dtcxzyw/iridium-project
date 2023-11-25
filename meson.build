project('iridium-project',
        ['cpp'],
        default_options : ['cpp_std=c++20'],
        version: 'nightly'
)

libiridium_inc = include_directories('include')

gtest = dependency('gtest')
gtest_main = dependency('gtest_main')
fmt = dependency('fmt')
llvm = dependency('llvm')
z3 = dependency('z3', required: false)
pkgconfig = import('pkgconfig')
lit = find_program('lit', required: false)

subdir('lib')
subdir('test')

install_subdir('include', install_dir : 'include/iridium')

subdir('tools')
