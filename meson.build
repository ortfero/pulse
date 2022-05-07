project('pulse', 'cpp',
    license: 'MIT',
    default_options: [
        'cpp_std=c++17',
        'warning_level=3'])

headers = [
    'include/pulse/pulse.hpp'
]

incdirs = include_directories('./include')

pulse = declare_dependency(
    include_directories: incdirs,
    sources: headers
)

subdir('benchmark')
subdir('test')

install_headers(headers, subdir: 'pulse')

pkg = import('pkgconfig')
pkg.generate(
    name: 'pulse',
    filebase: 'pulse',
    subdirs: ['pulse'],
    description: 'C++ 17 single-header library for signals and slots'
)
