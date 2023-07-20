SET(SOURCES screens/ui_Screen1.c
    ui.c
    ui_helpers.c
    fonts/ui_font_sourcehan20.c
    fonts/ui_font_sourcehan36.c)

add_library(ui ${SOURCES})
