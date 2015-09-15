TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    init/init.cpp \
    init/starter.cpp \
    gfx/gfx_class.cpp \
    event/event.cpp \
    gfx/sprite.cpp \
    gfx/window.cpp \
    gfx/spr_vec.cpp \
    game/player.cpp \
    game/game_instance_generic.cpp \
    game/instance_container.cpp \
    gfx/tile.cpp \
    init/level/tinyxml2.cpp \
    init/level/room.cpp \
    init/level/level_loader.cpp \
    game/hud.cpp \
    gfx/texture.cpp \
    audio/audioserver.cpp \
    game/wall/wall_overworld.cpp \
    audio/sample.cpp \
    audio/mus_background.cpp \
    game/wall/wall_brick.cpp \
    init/level/recognize_types.cpp \
    game/enemies/oval_classic.cpp \
    game/wall/wall_coin.cpp \
    game/enemies/supersayan.cpp \
    game/enemies/bad_cloud.cpp \
    game/enemies/torpedo.cpp \
    game/enemies/turtle.cpp \
    gfx/font.cpp \
    game/wall/block_special.cpp \
    game/items/mushroom.cpp \
    game/items/venom_mushroom.cpp

INCLUDEPATH += /usr/include/SDL2
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    init/init.h \
    init/starter.h \
    gfx/gfx_class.h \
    event/event.h \
    gfx/sprite.h \
    gfx/window.h \
    gfx/spr_vec.h \
    game/game_instance_generic.h \
    game/instance_container.h \
    game/player.h \
    game/wall.h \
    game/wall/wall.h \
    game/room.h \
    gfx/tile.h \
    init/level/tinyxml2.h \
    init/level/room.h \
    init/level/level_loader.h \
    game/hud.h \
    gfx/texture.h \
    audio/audioserver.h \
    game/wall/wall_overworld.h \
    audio/sample.h \
    audio/mus_background.h \
    game/wall/wall_brick.h \
    game/enemies/oval_classic.h \
    game/wall/wall_coin.h \
    game/enemies/supersayan.h \
    game/enemies/bad_cloud.h \
    game/enemies/torpedo.h \
    game/enemies/turtle.h \
    gfx/font.h \
    game/wall/block_special.h \
    init/level/recognize_types.h \
    game/items/mushroom.h \
    game/items/venom_mushroom.h \
    game/enemies/spikes.h \
    game/flag.h \
    game/items/tube.h
