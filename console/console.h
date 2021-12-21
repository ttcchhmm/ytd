#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextStream>
#include <QString>

namespace Console {
    /**
     * The standard output.
     */
    inline QTextStream out = QTextStream(stdout);

    /**
     * The error output.
     */
    inline QTextStream err = QTextStream(stderr);
}

#endif // CONSOLE_H