Notepad Application
===================
This Application has been developed with:
* Qt/c++
* Cmake
Software description
--------------------
This application is clone of MS notepad with the same features and functionalities.
How it works
-
In [container.h](https://github.com/OmarAymanMahfouz/Notepad/blob/master/container.h)
* The genaricClass handles all the external behaviours like open, save and saveAs.
* The genaricClass also handles the construction and desturction of the opened Notepad files.

In [mainwindow.h](https://github.com/OmarAymanMahfouz/Notepad/blob/master/mainwindow.h)
* The MainWindow handles all events that happens in the current activated window.
* The MainWindow initialize the important object like file name, file path and current zoom.

In [finddialog.h](https://github.com/OmarAymanMahfouz/Notepad/blob/master/finddialog.h)
* The findDialog handles the search mechanism.
