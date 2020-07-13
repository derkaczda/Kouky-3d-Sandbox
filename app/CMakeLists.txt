project(app)


set(SOURCE_FILES
    main.cpp
    Sandbox.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Kouky3d
)