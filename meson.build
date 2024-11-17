project('Drift', 'cpp', version: '0.0.1', meson_version: '1.6.0', default_options: ['cpp_std=c++20'])

sources = [
    'src/core/Application.cpp',
    'src/core/ApplicationInfo.cpp',
    'src/core/Element.cpp',
    'src/core/View.cpp',
    'src/core/Activity.cpp',
    'src/utils/Demangle.cpp',
    'src/utils/StringUtils.cpp',
    'src/utils/PerformanceTimer.cpp',
    'src/events/Observable.cpp',
    'src/events/EventManager.cpp',
    'src/events/DummyEventLoop.cpp',
    'src/events/EventLoop.cpp'
]

cmake = import('cmake')

if get_option('debug')
    add_global_arguments('-DDEBUG', language: ['c', 'cpp'])
endif

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
    cmake.subproject('yoga').dependency('yogacore'),
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