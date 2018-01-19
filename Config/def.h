#ifndef DEF_H
#define DEF_H

#define MAINWINDOW_WIDTH 660
#define MAINWINDOW_HEIGHT 444

#define HOST_IP "31.131.27.154"
const QString defaultScrollBarStyle = "QScrollBar:vertical{"
                                      "background: white;"
                                      "border-top-right-radius: 4px;"
                                      "border-bottom-right-radius: 4px;"
                                      "width: 8px;"
                                      "margin: 0px;"
                                      "}"
                                      "QScrollBar:handle:vertical{"
                                      "background: gray;"
                                      "border-radius: 2px;"
                                      "min-height: 20px;"
                                      "margin: 0px 2px 0px 2px;"
                                      "}"
                                      "QScrollBar:add-line:vertical{"
                                      "background: transparent;"
                                      "height: 0px;"
                                      "subcontrol-position: right;"
                                      "subcontrol-origin: margin;"
                                      "}"
                                      "QScrollBar:sub-line:vertical{"
                                      "background: transparent;"
                                      "height: 0px;"
                                      "subcontrol-position: left;"
                                      "subcontrol-origin: margin;"
                                      "}";

#define MAX_GLOBAL_MESSAGE_SIZE 140

#endif // DEF_H
