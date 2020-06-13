set(SOURCE_LIST
    "${ASSIGNMENT_SOURCE_ROOT}/main.cpp"
    "${ASSIGNMENT_SOURCE_ROOT}/node.cpp"
    "${ASSIGNMENT_SOURCE_ROOT}/line.cpp"
    "${ASSIGNMENT_SOURCE_ROOT}/scene.cpp"

    )

set(SHADER_SOURCE "${ASSIGNMENT_SOURCE_ROOT}/AssignmentPaths.cpp")
configure_file("${ASSIGNMENT_SOURCE_ROOT}/AssignmentPaths.cpp.in"
    ${SHADER_SOURCE})

set(ASSIGNMENT_SOURCE_LIST
    ${SOURCE_LIST}
    ${SHADER_SOURCE}
    PARENT_SCOPE)
