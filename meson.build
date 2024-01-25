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
'vrui_layout.c',
'vrui_layout.h',
'vrui_pal.h',

)

if build_machine.system() == 'linux'
vrui_files += files('vrui_pal_linux.c')

endif

if build_machine.system() == 'windows'
vrui_files += files('vrui_pal_win32.c')

endif

vrui = shared_library('svrui', vrui_files,
c_args : '-DVRUI_SHARED')

subdir('example')

cc = meson.get_compiler('c')
openvr_lib_path = meson.source_root() + '/example'
openvr = cc.find_library('openvr_api', dirs : [openvr_lib_path])

opengl = dependency('gl')

openvr_copy = fs.copyfile(meson.source_root() + '/example/openvr_api.dll')
openvrpdb_copy = fs.copyfile(meson.source_root() + '/example/openvr_api.pdb')
example = executable('svrui_example', example_files, link_with : vrui, dependencies : [openvr, opengl])
