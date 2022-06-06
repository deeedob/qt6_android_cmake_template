#include <filesystem>
#include <QGuiApplication>
#ifdef ANDROID_BUILD
    #include <QQmlApplicationEngine>
#else
    #include "enhanced_engine.hpp"
    #include <QQmlContext>
#endif
#include <iostream>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


#ifdef ANDROID_BUILD
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/MainWindow.qml"));
#else
    EnhancedEngine engine;
    engine.rootContext()->setContextProperty("$QmlEngine", &engine);

    auto path = std::filesystem::current_path();
    path.append("qml/main_hot_reload.qml");
    engine.load(path.c_str());
#endif


    return app.exec();
}
