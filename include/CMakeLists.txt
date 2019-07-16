add_subdirectory(app)
set(APP_HEADERS ${APP_HEADERS} PARENT_SCOPE)

add_subdirectory(engine)
set(ENGINE_HEADERS ${ENGINE_HEADERS} PARENT_SCOPE)