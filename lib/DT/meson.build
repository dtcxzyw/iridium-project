libiridium_dt_dep = [iridium_support, llvm]
libiridium_dt = library('iridium_dt',
                    'IntrusiveList.cpp',
                    'RefCount.cpp',
                    include_directories: [libiridium_inc],
                    dependencies: libiridium_dt_dep,
                    install: true
)

iridium_dt = declare_dependency(
    link_with: libiridium_dt,
    dependencies: libiridium_dt_dep)
