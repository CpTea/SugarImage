set(TARGET_NAME ${PROJECT_NAME})

find_package(OpenCV REQUIRED HINTS $ENV{OpenCV_DIR})

if(OpenCV_FOUND)
  file(GLOB_RECURSE INC_FILES "${PROJECT_SOURCE_DIR}/include/**")
  file(GLOB_RECURSE SC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp"
       "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/**/*.cpp"
       "${PROJECT_SOURCE_DIR}/src/**/*.h")

  add_library(${TARGET_NAME} SHARED ${INC_FILES} ${SC_FILES})

  target_include_directories(
    ${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:include>
    PRIVATE ${PROJECT_SOURCE_DIR}/src
    PRIVATE ${OpenCV_INCLUDE_DIRS})

  target_compile_definitions(
    ${TARGET_NAME}
    PRIVATE LIBRARY_EXPORT
    PRIVATE _UNICODE
    PRIVATE UNICODE)

  target_link_directories(${TARGET_NAME} PRIVATE ${PROJECT_BINARY_DIR} PRIVATE
                          ${OpenCV_LINK_DIRS})

  target_link_libraries(${TARGET_NAME} PRIVATE ${OpenCV_LIBS})

  configure_file(${PROJECT_SOURCE_DIR}/config/${TARGET_NAME}Config.cmake.in
                 ${PROJECT_SOURCE_DIR}/cmake/${TARGET_NAME}Config.cmake)

  install(
    TARGETS ${TARGET_NAME}
    EXPORT ${TARGET_NAME}Tagets
    RUNTIME DESTINATION bin/$<CONFIGURATION>
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
  install(FILES ${INC_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
  install(FILES ${PROJECT_SOURCE_DIR}/cmake/${TARGET_NAME}Config.cmake
          DESTINATION ${CMAKE_INSTALL_PREFIX})

else()
  message("Unable to find OpenCV from path: ${OpenCV_DIR}.")
endif()
