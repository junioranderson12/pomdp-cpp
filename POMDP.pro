TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    belief-node.cpp \
    belief-tree.cpp \
    main.cpp \
    model-abstract/agent.cpp \
    model-abstract/model.cpp \
    model-abstract/observation.cpp \
    model-abstract/simulator.cpp \
    model-abstract/state.cpp \
    model-grid_world/grid-world-agent.cpp \
    model-grid_world/grid-world-model.cpp \
    model-grid_world/grid-world-observation.cpp \
    model-grid_world/grid-world-simulator.cpp \
    model-grid_world/grid-world-state.cpp
        

HEADERS += \
    belief-node.hpp \
    belief-tree.hpp \
    model-abstract/agent.hpp \
    model-abstract/model.hpp \
    model-abstract/observation.hpp \
    model-abstract/simulator.hpp \
    model-abstract/state.hpp \
    model-grid_world/grid-world-agent.hpp \
    model-grid_world/grid-world-model.hpp \
    model-grid_world/grid-world-observation.hpp \
    model-grid_world/grid-world-simulator.hpp \
    model-grid_world/grid-world-state.hpp
