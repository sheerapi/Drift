project('Drift', 'cpp', version: '0.0.1', meson_version: '1.6.0')

sources = [
    'src/core/Application.cpp',
    'src/core/ApplicationInfo.cpp',
    'src/utils/Demangle.cpp',
    'src/utils/StringUtils.cpp',
]

run_command('./skia.sh', host_machine.system(), 'x64', check: true)

dependencies = [
    dependency('skia'),
    dependency(
        'spdlog',
        default_options: {
            'external_fmt': 'enabled',
            'compile_library': true,
            'default_library': 'static',
        },
    ),
]

drift = shared_library(
    'drift',
    sources: sources,
    include_directories: include_directories('include'),
    dependencies: dependencies,
)

drift_dep = declare_dependency(
    link_with: drift,
    include_directories: include_directories('include'),
    dependencies: dependencies,
)

meson.override_dependency('drift', drift_dep)

executable('sandbox', sources: 'sandbox/main.cpp', dependencies: drift_dep)
executable(
    'dac',
    sources: 'tools/dac.cpp',
    dependencies: [dependency('libzstd'), dependency('rapidjson')],
)