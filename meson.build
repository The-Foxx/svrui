#///////////////////////////////////////////////////////////////////////////
#/
#/  SVRUI Source File.
#/  Copyright (C) 2024 Clara Lille
#/ -------------------------------------------------------------------------
#/  File name:   meson.build
#/  Version:     v1.00
#/  Created:     23/01/24 by Clara.
#/  Description: 
#/ -------------------------------------------------------------------------
#/  This project is licensed under the MIT License
#/
#///////////////////////////////////////////////////////////////////////////

#if get_option('solver_present') != true
project('svrui', 'c')

#endif

fs = import('fs')

vrui_files = files(
'vrui.c',
'vrui.h',
'vrui_base.h',
'vrui_gfx.c',
'vrui_gfx.h',
'vrui_layout.c',
'vrui_layout.h',
'vrui_pal.h',
'vrui_window.c',
'vrui_window.h',

)

if build_machine.system() == 'linux'
vrui_files += files('vrui_pal_linux.c')

endif

if build_machine.system() == 'windows'
#vrui_files += files('vrui_pal_linux.c') # temp hack just to get mingw to build the library
vrui_files += files('vrui_pal_win32.c')

endif

vrui_cargs = []

vrui_shared = get_option('vrui_shared')
if vrui_shared == true
vrui_cargs += ['-DVRUI_SHARED']

endif

vrui = shared_library('svrui', vrui_files,
c_args : vrui_cargs)

vrui_static = static_library('svrui_static', vrui_files)

subdir('example')

iter = executable('svrui_test', iter_files, link_with : vrui)

cc = meson.get_compiler('c')

glfw = declare_dependency(
  dependencies : cc.find_library('glfw3', dirs : [meson.current_source_dir() + '/lib/glfw']),
  include_directories : include_directories('.'),
)

openGLDep = dependency('gl')

ogl = executable('svrui_ogl_test', ogl_files, link_with : vrui, dependencies : [glfw, openGLDep])

subdir('overlay_reference')
overlay_ref = executable('svrui_overlay', overlay_ref_files, link_with : vrui_static, dependencies : [glfw],
include_directories : ['overlay_reference/lib/vulkan_api/include'])
