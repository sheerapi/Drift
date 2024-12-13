project(
    'Drift',
    'cpp',
    version: '0.0.1',
    default_options: ['cpp_std=c++20'],
)

sources = [
    'src/core/Application.cpp',
    'src/core/ApplicationInfo.cpp',
    'src/core/Element.cpp',
    'src/core/View.cpp',
    'src/core/Activity.cpp',
    'src/utils/Demangle.cpp',
    'src/utils/StringUtils.cpp',
    'src/utils/PerformanceTimer.cpp',
    'src/utils/LibraryManager.cpp',
    'src/events/Observable.cpp',
    'src/events/EventManager.cpp',
    'src/events/DummyEventLoop.cpp',
    'src/events/EventLoop.cpp',
    'src/events/DesktopEventLoop.cpp',
    'src/components/Window.cpp',
    'src/graphics/RendererContext.cpp'
]

cmake = import('cmake')

if get_option('debug') or get_option('verbose')
    add_global_arguments(['-DDEBUG', '-fvisibility=hidden'], language: ['c', 'cpp'])
endif

if get_option('no_glfw')
    add_global_arguments(['-DDT_NO_GLFW', '-fvisibility=hidden'], language: ['c', 'cpp'])
endif

run_command('./skia.sh', host_machine.system(), 'x64', check: true)

dependencies = [
    dependency('skia'),
    dependency('dl'),
    dependency(
        'spdlog',
        default_options: {
            'external_fmt': 'enabled',
            'compile_library': true,
            'default_library': 'static',
        },
    ),
    cmake.subproject('yoga').dependency('yogacore'),
    dependency('opengl')
]

if not get_option('no_glfw')
    dependencies += [dependency('glfw3', default_options: { 'display-api': 'wayland', })]
endif

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