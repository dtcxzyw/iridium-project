libiridium_support_dep = [fmt]
libiridium_support = library('iridium_support',
                     'OutputStream.cpp',
                     'Name.cpp',
                     include_directories: [libiridium_inc],
                     dependencies: libiridium_support_dep,
                     install: true
)

iridium_support = declare_dependency(link_with: libiridium_support,
                               dependencies: libiridium_support_dep
)
