include_guard(DIRECTORY)

function(qm_get_windows_proxy _out)
    if(NOT WIN32)
        return()
    endif()

    execute_process(
        COMMAND reg query "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings" /v ProxyEnable
        OUTPUT_VARIABLE _proxy_enable_output
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

    if(NOT _proxy_enable_output MATCHES "ProxyEnable[ \t\r\n]+REG_DWORD[ \t\r\n]+0x1")
        return()
    endif()

    execute_process(
        COMMAND reg query "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings" /v ProxyServer
        OUTPUT_VARIABLE _proxy_server_output
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

    if(NOT _proxy_server_output MATCHES "ProxyServer[ \t\r\n]+REG_SZ[ \t\r\n]+(.*)")
        return()
    endif()

    set(${_out} ${CMAKE_MATCH_1} PARENT_SCOPE)
endfunction()

macro(qm_set_proxy_env _proxy)
    set(ENV{HTTP_PROXY} "http://${_proxy}")
    set(ENV{HTTPS_PROXY} "http://${_proxy}")
    set(ENV{ALL_PROXY} "http://${_proxy}")
endmacro()
