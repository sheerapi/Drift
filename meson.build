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
    'src/graphics/RendererContext.cpp',
    'src/events/InputSystem.cpp',
    'src/utils/Time.cpp',
    'src/events/ShortcutManager.cpp',
    'src/utils/ConfigManager.cpp',
    'src/styles/Style.cpp',
    'src/components/FadeActivity.cpp',
    'src/utils/Scheduler.cpp',
    'src/styles/AnimationScheduler.cpp',
    'src/styles/TransitionFunction.cpp',
    'src/utils/CubicBezier.cpp'
]

cmake = import('cmake')

sys_os = host_machine.system()
glfw = not get_option('no_desktop')

glfw_backend = ''

if sys_os == 'linux'
    glfw_backend = 'wayland'
elif sys_os == 'windows'
    glfw_backend = 'win32'
elif sys_os == 'macos'
    glfw_backend = 'cocoa'
endif

add_project_arguments(
    ['-fvisibility=hidden'],
    language: ['c', 'cpp'],
)

if get_option('debug') or get_option('verbose')
    add_global_arguments(['-DDEBUG'], language: ['c', 'cpp'])
endif

if get_option('no_wayland')
    add_global_arguments(['-DDT_NO_WAYLAND'], language: ['c', 'cpp'])
endif

if get_option('no_desktop')
    add_global_arguments(['-DDT_NO_DESKTOP'], language: ['c', 'cpp'])
endif

message('Downloading Skia binaries...')

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
    dependency('magic_enum'),
    dependency('tomlplusplus'),
    dependency('utf8cpp'),
    dependency('libzstd'),
    dependency('fontconfig')
]

if not get_option('no_wayland') and sys_os == 'linux'
    dependencies += [
        dependency('wayland-client'),
        dependency('wayland-cursor'),
        dependency('wayland-egl'),
    ]
endif

if glfw
    dependencies += [
        dependency('glfw3', default_options: { 'display-api': glfw_backend })
    ]
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