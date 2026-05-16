cmake_minimum_required(VERSION 3.19)
project(Gwint LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Gwint
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    karta.cpp
    karta.h
    kontener_kart.h kontener_kart.cpp
    plansza.h plansza.cpp
    plansza_linia.h plansza_linia.cpp

    card_loader.h card_loader.cpp
    deck_saver.h deck_saver.cpp
    deck_loader.h deck_loader.cpp
    keyword.h keyword.cpp
    graveyard.h graveyard.cpp
    player_hand.h player_hand.cpp
    textury.qrc
    deck.h deck.cpp
    card_button.h card_button.cpp

    player.h player.cpp
    gra.h gra.cpp
    efekty_pogodowe.h efekty_pogodowe.cpp
)

configure_file(cards_list.txt cards_list.txt COPYONLY)

target_link_libraries(Gwint
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Gwint
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Gwint
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
