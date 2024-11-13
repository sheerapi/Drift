project('Skia', ['c', 'cpp'], version: 'latest')

cc = meson.get_compiler('cpp')

skia_dep = declare_dependency(
    dependencies: [
        cc.find_library('bentleyottmann', dirs: meson.current_source_dir()),
        cc.find_library('skcms', dirs: meson.current_source_dir(), static: true),
        cc.find_library('skia', dirs: meson.current_source_dir(), required: true),
        cc.find_library('skottie', dirs: meson.current_source_dir()),
        cc.find_library('skresources', dirs: meson.current_source_dir(), required: true),
        cc.find_library('sksg', dirs: meson.current_source_dir()),
        cc.find_library('skshaper', dirs: meson.current_source_dir()),
    ],
    include_directories: include_directories('skia/include', 'skia'),
)

meson.override_dependency('skia', skia_dep)