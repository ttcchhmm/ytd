#include "main.h"

#include <QCoreApplication>
#include <QCommandLineParser>
#include "console/console.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    a.setApplicationName("ytd");
    a.setApplicationVersion("1.0.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("An audio daemon for youtube-dl");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("port", "The port to bind to the server");

	parser.process(a);

    if(parser.positionalArguments().length() != 1) {
        Console::err << "Invalid number of arguments." << Qt::endl;
        return 1;
    }

    Main::player = new Player;
    Main::server = new WebSocketServer(Main::player, parser.positionalArguments()[0].toInt()); // Start the websocket server

    return a.exec();
}
