add_definitions(-DMICROPYTHON)

# dolp configuration
add_definitions(-DENTITIES_PER_WORLD=60 -DBODY_COMPONENTS_PER_WORLD=60 -DCOLLISION_COMPONENTS_PER_WORLD=60 -DMOVEMENT_COMPONENTS_PER_WORLD=60
-DRENDER_COMPONENTS_PER_WORLD=60 -DSTATE_COMPONENTS_PER_WORLD=60 -DUPDATE_COMPONENTS_PER_WORLD=60 -DNUM_TIMEOUTS=60)

add_library(usermod_dolp INTERFACE)

target_sources(usermod_dolp INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/dolp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dolpmodule.c
    ${CMAKE_CURRENT_LIST_DIR}/pentity.cpp

    ${CMAKE_CURRENT_LIST_DIR}/../src/dolp.cpp

    ${CMAKE_CURRENT_LIST_DIR}/../src/drivers/Display.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/drivers/DriverLayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/drivers/Joystick.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/drivers/NotePlayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/drivers/Timer.cpp

    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/Engine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/Entity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/PEntity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/World.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/components/BodyComponent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/components/CollisionComponent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/components/MovementComponent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/components/RenderComponent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/components/UpdateComponent.cpp

    ${CMAKE_CURRENT_LIST_DIR}/../src/target/micropython/rp2040/HwDisplay-Oled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/target/micropython/rp2040/HwDisplaySPI-Oled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/target/micropython/rp2040/HwDisplayI2C-Oled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/target/micropython/rp2040/HwJoystick.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/target/micropython/rp2040/HwNotePlayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/target/micropython/rp2040/HwRefresh.cpp
)

target_include_directories(usermod_dolp INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../src/
    ${CMAKE_CURRENT_LIST_DIR}/../src/drivers
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine
    ${CMAKE_CURRENT_LIST_DIR}/../src/engine/components
    ${CMAKE_CURRENT_LIST_DIR}/../src/hardware
)

target_link_libraries(usermod INTERFACE usermod_dolp)
