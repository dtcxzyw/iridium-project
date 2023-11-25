libiridium_ir_dep = [iridium_support, iridium_dt]
libiridium_ir = library('iridium_ir',
                    'Block.cpp',
                    'ConstantValue.cpp',
                    'IntegerOperators.cpp',
                    'Operator.cpp',
                    'OperatorTraits.cpp',
                    'Region.cpp',
                    'Type.cpp',
                    'Value.cpp',
                    include_directories: [libiridium_inc],
                    dependencies: libiridium_ir_dep,
                    install: true
)

iridium_ir = declare_dependency(
    link_with: libiridium_ir,
    dependencies: libiridium_ir_dep)
