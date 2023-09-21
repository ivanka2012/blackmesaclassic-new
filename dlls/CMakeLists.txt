cmake_minimum_required(VERSION 3.15)
include(${CMAKE_SOURCE_DIR}/GetGitRevisionDescription.cmake)
get_git_head_revision(GIT_REFSPEC BMC_GIT_COMMIT)

cmake_policy(SET CMP0091 NEW)
project(hl VERSION ${BlackMesaClassic_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/hl.exp)
add_library(hl SHARED
    aflock.cpp
    agrunt.cpp
    airtank.cpp
    animating.cpp
    animation.cpp
    apache.cpp
    barnacle.cpp
    barney.cpp
    bigmomma.cpp
    bloater.cpp
    bmodels.cpp
    bullsquid.cpp
    buttons.cpp
    cbase.cpp
    client.cpp
    combat.cpp
    controller.cpp
    crossbow.cpp
    crowbar.cpp
    defaultai.cpp
    doors.cpp
    effects.cpp
    egon.cpp
    explode.cpp
    flyingmonster.cpp
    func_break.cpp
    func_tank.cpp
    game.cpp
    gamerules.cpp
    gargantua.cpp
    gauss.cpp
    genericmonster.cpp
    ggrenade.cpp
    globals.cpp
    gman.cpp
    handgrenade.cpp
    hassassin.cpp
    headcrab.cpp
    healthkit.cpp
    hgrunt.cpp
    hornet.cpp
    hornetgun.cpp
    houndeye.cpp
    h_ai.cpp
    h_battery.cpp
    h_cine.cpp
    h_cycler.cpp
    h_export.cpp
    ichthyosaur.cpp
    islave.cpp
    items.cpp
    leech.cpp
    lights.cpp
    maprules.cpp
    monstermaker.cpp
    monsters.cpp
    monsterstate.cpp
    mortar.cpp
    mp5.cpp
    multiplay_gamerules.cpp
    nihilanth.cpp
    nodes.cpp
    observer.cpp
    osprey.cpp
    pathcorner.cpp
    plane.cpp
    plats.cpp
    player.cpp
    python.cpp
    rat.cpp
    roach.cpp
    rpg.cpp
    satchel.cpp
    schedule.cpp
    scientist.cpp
    scripted.cpp
    shotgun.cpp
    singleplay_gamerules.cpp
    skill.cpp
    sound.cpp
    soundent.cpp
    spectator.cpp
    squadmonster.cpp
    squeakgrenade.cpp
    subs.cpp
    talkmonster.cpp
    teamplay_gamerules.cpp
    tempmonster.cpp
    tentacle.cpp
    triggers.cpp
    tripmine.cpp
    turret.cpp
    util.cpp
    weapons.cpp
    world.cpp
    wpn_shared/hl_wpn_glock.cpp
    xen.cpp
    zombie.cpp
    ../game_shared/voice_gamemgr.cpp
    ../pm_shared/pm_debug.c
    ../pm_shared/pm_math.c
    ../pm_shared/pm_shared.c
    model.cpp
    
)
configure_file(${CMAKE_SOURCE_DIR}/Config.h.in Config.h)

if(WIN32 AND MSVC AND (NOT MSVC_VERSION LESS 1600) AND (NOT CMAKE_VERSION VERSION_LESS "3.1"))
    target_sources(hl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hl.def)
else()
    target_sources(hl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hlmingw.def)  
    target_link_options(hl PUBLIC
        -Wl,--enable-stdcall-fixup
        -static
    )
endif()

set_property(TARGET hl PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set_target_properties(hl PROPERTIES PREFIX "")
add_definitions(-DWIN32 -DQUIVER -DNOMINMAX -DVOXEL -DQUAKE2 -DVALVE_DLL -DCLIENT_WEAPONS -DWINVER=0x0501 -D_WIN32_WINNT=0x0501)
if(WIN32)
    target_include_directories(hl PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../dlls
        ${CMAKE_CURRENT_SOURCE_DIR}/../engine
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
        ${CMAKE_CURRENT_SOURCE_DIR}/../pm_shared
        ${CMAKE_CURRENT_SOURCE_DIR}/../game_shared
        ${CMAKE_CURRENT_SOURCE_DIR}/../public
        ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()
if(MSVC)
    target_compile_options(hl PRIVATE "/MP")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
install(TARGETS hl RUNTIME DESTINATION bmc/dlls)
if(WIN32 AND MSVC AND (NOT MSVC_VERSION LESS 1600) AND (NOT CMAKE_VERSION VERSION_LESS "3.1"))
    install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION debug_symbols OPTIONAL)
endif()