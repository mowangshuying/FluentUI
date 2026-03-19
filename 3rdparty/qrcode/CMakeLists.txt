set (TGT qrcode)

if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
if(WIN32)
    set(CMAKE_DEBUG_POSTFIX "d")
endif()
endif()

add_library(${TGT} STATIC
    QrCode.cpp
    QrCode.hpp
)
target_include_directories(${TGT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})