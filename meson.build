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

project('svrui', 'c')
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
vrui_files += files('vrui_pal_win32.c')

endif

vrui_cargs = []

vrui_shared = get_option('vrui_shared')
if vrui_shared == true
vrui_cargs += ['-DVRUI_SHARED']

endif

vrui = shared_library('svrui', vrui_files,
c_args : vrui_cargs)

subdir('example')

cc = meson.get_compiler('c')
openvr_lib_path = meson.source_root() + '/example'
openvr = cc.find_library('openvr_api', dirs : [openvr_lib_path])

opengl = dependency('gl')

openvr_copy = fs.copyfile(meson.source_root() + '/example/openvr_api.dll')
openvrpdb_copy = fs.copyfile(meson.source_root() + '/example/openvr_api.pdb')
example = executable('svrui_example', example_files, link_with : vrui, dependencies : [openvr, opengl])

iter = executable('svrui_test', iter_files, link_with : vrui)
