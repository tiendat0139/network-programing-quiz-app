QT += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    ../app/comunicate/client.cpp \
    animations.cpp \
    answerhandler.cpp \
    categoryhandler.cpp \
    clientmanager.cpp \
    component.cpp \
    createroomdialog.cpp \
    examwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    passworddialog.cpp \
    practicehandler.cpp \
    practiceitem.cpp \
    questionbutton.cpp \
    questionclient.cpp \
    questionhandler.cpp \
    resulthandler.cpp \
    roomhandler.cpp \
    roomitem.cpp \
    serverlistener.cpp \
    styles.cpp \
    userhandler.cpp \
    useritem.cpp \
    utils.cpp \
    addquestiondialog.cpp \
    adminwindow.cpp \
    categoryitem.cpp \
    createpracticedialog.cpp \
    questionbankitem.cpp \

HEADERS += \
    animations.h \
    answerhandler.h \
    categoryhandler.h \
    clientmanager.h \
    component.h \
    createroomdialog.h \
    examwindow.h \
    loginwindow.h \
    mainwindow.h \
    passworddialog.h \
    practicehandler.h \
    practiceitem.h \
    questionbutton.h \
    questionclient.h \
    questionhandler.h \
    resulthandler.h \
    roomhandler.h \
    roomitem.h \
    serverlistener.h \
    styles.h \
    userhandler.h \
    useritem.h \
    utils.h \
    addquestiondialog.h \
    adminwindow.h \
    categoryitem.h \
    createpracticedialog.h \
    questionbankitem.h \

FORMS += \
    createroomdialog.ui \
    examwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    passworddialog.ui \
    practiceitem.ui \
    roomitem.ui \
    addquestiondialog.ui \
    adminwindow.ui \
    categoryitem.ui \
    createpracticedialog.ui \
    questionbankitem.ui \
    useritem.ui \

RESOURCES += \
    resource.qrc
