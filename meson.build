project('Drift', 'cpp', version: '0.0.1')

sources = []

run_command('./skia.sh', host_machine.system(), 'x64', check: true)

dependencies = [dependency('skia')]

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