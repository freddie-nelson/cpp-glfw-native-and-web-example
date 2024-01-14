project('emscripten-test', 'cpp', 'c')

incdir = include_directories('externals/include')

glad_src = ['externals/src/glad/glad.c']
glad = static_library('glad', glad_src, include_directories : incdir)

# configure for cross-compilation
dependencies = []
link_with = []
link_args = []
name_suffix = 'exe'

cross_target = meson.get_external_property('cross_target', 'native')

if cross_target == 'native'
    dependencies += [dependency('glfw3')] 
    link_with += glad
endif

if cross_target == 'wasm'
    link_args += ['-sUSE_GLFW=3', '-sMIN_WEBGL_VERSION=2', '-sMAX_WEBGL_VERSION=2']
    name_suffix = 'html'
endif

src = ['main.cpp']
executable('main', src, include_directories : incdir, link_args : link_args, name_suffix : name_suffix, link_with : link_with, dependencies : dependencies)