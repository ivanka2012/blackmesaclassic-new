set(LICENSE_FILE ${CMAKE_INSTALL_PREFIX}/bmc/LICENSES.txt)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bmc)
file(REMOVE ${LICENSE_FILE})

message("${CMAKE_INSTALL_PREFIX}")

function(AddLicenseText)
    cmake_parse_arguments(
        PARSED_ARGS
        ""
        "LIBRARY"
        "SOURCES"
        ${ARGN}
    )
    file(APPEND ${LICENSE_FILE} "\n========= ${PARSED_ARGS_LIBRARY} license(s) =========\n")
    foreach(source ${PARSED_ARGS_SOURCES})
        get_filename_component(source_filename ${source} NAME)
        file(APPEND ${LICENSE_FILE} "* ${source_filename}:\n")
        file(READ ${source} contents)
        file(APPEND ${LICENSE_FILE} "${contents}")
    endforeach(source)
    file(APPEND ${LICENSE_FILE} "\n========= end ${PARSED_ARGS_LIBRARY} license(s) =====\n")
endfunction(AddLicenseText)

AddLicenseText(LIBRARY BlackMesaClassic SOURCES ${CMAKE_SOURCE_DIR}/../LICENSE.txt)
AddLicenseText(LIBRARY GoldSrcSDK SOURCES ${CMAKE_SOURCE_DIR}/../SDKLICENSE.txt)
AddLicenseText(LIBRARY fmt SOURCES ${CMAKE_CURRENT_BINARY_DIR}/fmt-source/src/fmt/LICENSE.rst)
