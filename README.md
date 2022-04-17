Notepad Application
===================
This Application has been developed with:
* C++/QT
* Cmake

Software description
--------------------
This application is a simple Notepad application that allows you to create or modify a text document

How it works
-
In [container.h](https://github.com/OmarAymanMahfouz/Notepad/blob/master/container.h)
* The windowController class handles the construction and destruction of the windows.
* The saveClass class handles saving mechanism.
* The openClass class handles opening mechanism.

In [mainwindow.h](https://github.com/OmarAymanMahfouz/Notepad/blob/master/mainwindow.h)
* The MainWindow handles all events that happens in the current activated window.
* The MainWindow initialize the important object like file name, file path and current zoom.

In [finddialog.h](https://github.com/OmarAymanMahfouz/Notepad/blob/master/finddialog.h)
* The findDialog handles the search mechanism.
