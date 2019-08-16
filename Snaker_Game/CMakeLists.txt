cmake_minimum_required(VERSION 3.9)
project(Snaker_Game C)

set(CMAKE_C_STANDARD 11)

add_executable(Snaker_Game main.c Common/WinApiHelper.c Common/WinApiHelper.h View/Panel.c View/Panel.h View/ControlPanel.c View/ControlPanel.h View/KeyHandler.c View/KeyHandler.h View/SettingPanel.c View/SettingPanel.h View/GamePanel.c View/GamePanel.h Control/GameControl.c Control/GameControl.h Model/GameData.h View/UserHelpPanel.c View/UserHelpPanel.h View/ExitPanel.c View/ExitPanel.h)

add_definitions(-lwinmm)

target_link_libraries(Snaker_Game Winmm.lib)