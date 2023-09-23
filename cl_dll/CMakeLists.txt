cmake_minimum_required(VERSION 3.15)
include(${CMAKE_SOURCE_DIR}/GetGitRevisionDescription.cmake)
get_git_head_revision(GIT_REFSPEC BMC_GIT_COMMIT)

cmake_policy(SET CMP0091 NEW)
project(client VERSION ${BlackMesaClassic_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_library(client SHARED
    ammo.cpp
    ammohistory.cpp
    ammo_secondary.cpp
    battery.cpp
    cdll_int.cpp
    com_weapons.cpp
    death.cpp
    demo.cpp
    entity.cpp
    events.cpp
    ev_common.cpp
    ev_hldm.cpp
    flashlight.cpp
    GameStudioModelRenderer.cpp
    geiger.cpp
    health.cpp
    hl/hl_baseentity.cpp
    hl/hl_events.cpp
    hl/hl_objects.cpp
    hl/hl_weapons.cpp
    hud.cpp
    hud_bench.cpp
    hud_benchtrace.cpp
    hud_msg.cpp
    hud_redraw.cpp
    hud_servers.cpp
    hud_spectator.cpp
    hud_update.cpp
    input.cpp
    inputw32.cpp
    interpolation.cpp
    in_camera.cpp
    menu.cpp
    message.cpp
    saytext.cpp
    statusbar.cpp
    status_icons.cpp
    StudioModelRenderer.cpp
    studio_util.cpp
    text_message.cpp
    train.cpp
    tri.cpp
    util.cpp
    vgui_ClassMenu.cpp
    vgui_ControlConfigPanel.cpp
    vgui_CustomObjects.cpp
    vgui_int.cpp
    vgui_MOTDWindow.cpp
    vgui_SchemeManager.cpp
    vgui_ScorePanel.cpp
    vgui_ServerBrowser.cpp
    vgui_SpectatorPanel.cpp
    vgui_TeamFortressViewport.cpp
    vgui_teammenu.cpp
    view.cpp
    voice_status.cpp
    ../common/parsemsg.cpp
    ../dlls/crossbow.cpp
    ../dlls/crowbar.cpp
    ../dlls/egon.cpp
    ../dlls/gauss.cpp
    ../dlls/handgrenade.cpp
    ../dlls/hornetgun.cpp
    ../dlls/mp5.cpp
    ../dlls/python.cpp
    ../dlls/rpg.cpp
    ../dlls/satchel.cpp
    ../dlls/shotgun.cpp
    ../dlls/squeakgrenade.cpp
    ../dlls/tripmine.cpp
    ../dlls/wpn_shared/hl_wpn_glock.cpp
    ../game_shared/vgui_checkbutton2.cpp
    ../game_shared/vgui_grid.cpp
    ../game_shared/vgui_helpers.cpp
    ../game_shared/vgui_listbox.cpp
    ../game_shared/vgui_loadtga.cpp
    ../game_shared/vgui_scrollbar2.cpp
    ../game_shared/vgui_slider2.cpp
    ../game_shared/voice_banmgr.cpp
    ../pm_shared/pm_debug.c
    ../pm_shared/pm_math.c
    ../pm_shared/pm_shared.c
    ../public/interface.cpp
)
configure_file(${CMAKE_SOURCE_DIR}/Config.h.in Config.h)

set_property(TARGET client PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set_target_properties(client PROPERTIES PREFIX "")
add_definitions(-DCLIENT_DLL -DCLIENT_WEAPONS -DNOMINMAX -DHL_DLL -DWINVER=0x0501 -D_WIN32_WINNT=0x0501)
if(WIN32)
    add_definitions(-DWIN32)
    if(MSVC)
        target_link_libraries(client PUBLIC
            #${CMAKE_BINARY_DIR}/fmt-bin/lib/fmt$<$<CONFIG:Debug>:d>.lib
            ${CMAKE_CURRENT_SOURCE_DIR}/../utils/vgui/lib/win32_vc6/vgui.lib
            ${CMAKE_CURRENT_SOURCE_DIR}/../lib/public/SDL2.lib
        )
    else(NOT MSVC) #mingw
        target_link_libraries(client PUBLIC
            #${CMAKE_BINARY_DIR}/fmt-bin/lib/fmt$<$<CONFIG:Debug>:d>.lib
            ${CMAKE_CURRENT_SOURCE_DIR}/../utils/vgui/lib/win32_vc6/vgui.lib
            ${CMAKE_CURRENT_SOURCE_DIR}/../lib/public/SDL2.lib
        )
    endif()
    target_include_directories(client PUBLIC
        #${CMAKE_BINARY_DIR}/fmt-bin/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../dlls
        ${CMAKE_CURRENT_SOURCE_DIR}/../cl_dll
        ${CMAKE_CURRENT_SOURCE_DIR}/../public
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
        ${CMAKE_CURRENT_SOURCE_DIR}/../pm_shared
        ${CMAKE_CURRENT_SOURCE_DIR}/../engine
        ${CMAKE_CURRENT_SOURCE_DIR}/../utils/vgui/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../game_shared
        ${CMAKE_CURRENT_SOURCE_DIR}/../external
        ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()
if(MSVC)
    target_compile_options(client PRIVATE /MP /GL)
    target_link_options(client PRIVATE /LTCG /OPT:REF)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
install(TARGETS client RUNTIME DESTINATION bmc/cl_dlls)
if(WIN32 AND MSVC AND (NOT MSVC_VERSION LESS 1600) AND (NOT CMAKE_VERSION VERSION_LESS "3.1"))
	install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION debug_symbols OPTIONAL)
endif()