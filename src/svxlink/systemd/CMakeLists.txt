#############################################################################
# SvxLink ROIP Repeater system Systemd setup
#############################################################################

set(SYSTEMD_CONFIGURATIONS_FILES_DIR "/lib/systemd/system" CACHE PATH
  "Path to systemd units")
set(SYSTEMD_DEFAULTS_FILES_DIR "${SYSCONF_INSTALL_DIR}/default" CACHE PATH
  "Path to systemd unit configuration files")

configure_file(svxlink_gpio_setup.service.in svxlink_gpio_setup.service @ONLY)
configure_file(svxlink.service.in svxlink.service @ONLY)
configure_file(remotetrx.service.in remotetrx.service @ONLY)
configure_file(svxreflector.service.in svxreflector.service @ONLY)
configure_file(svxlink.default.in svxlink @ONLY)
configure_file(remotetrx.default.in remotetrx @ONLY)
configure_file(svxreflector.default.in svxreflector @ONLY)
configure_file(svxlink_upnp.service.in svxlink_upnp.service @ONLY)
configure_file(svxlink_upnp.default.in svxlink_upnp @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/svxlink_gpio_setup.service
              ${CMAKE_CURRENT_BINARY_DIR}/svxlink.service
              ${CMAKE_CURRENT_BINARY_DIR}/remotetrx.service
              ${CMAKE_CURRENT_BINARY_DIR}/svxreflector.service
              ${CMAKE_CURRENT_BINARY_DIR}/svxlink_upnp.service
        DESTINATION ${SYSTEMD_CONFIGURATIONS_FILES_DIR})
message(STATUS "Systemd unit files will be installed to "
        "${SYSTEMD_CONFIGURATIONS_FILES_DIR} after make install")

install_if_not_exists(${CMAKE_CURRENT_BINARY_DIR}/svxlink
        ${SYSTEMD_DEFAULTS_FILES_DIR} )
install_if_not_exists(${CMAKE_CURRENT_BINARY_DIR}/remotetrx
        ${SYSTEMD_DEFAULTS_FILES_DIR} )
install_if_not_exists(${CMAKE_CURRENT_BINARY_DIR}/svxreflector
        ${SYSTEMD_DEFAULTS_FILES_DIR} )
install_if_not_exists(${CMAKE_CURRENT_BINARY_DIR}/svxlink_upnp
        ${SYSTEMD_DEFAULTS_FILES_DIR} )
message(STATUS "Systemd unit configuration files will be "
               "installed to ${SYSTEMD_DEFAULTS_FILES_DIR} "
               "after make install")
