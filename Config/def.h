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

#define HANDSHAKE 0
#define REGISTRATION 1
#define REGISTRATION_CODE 2
#define RECOVERY 3
#define RECOVERY_CODE 4
#define RECOVERY_NEW_PASS 5
#define DOES_EXIST_NICKNAME 6
#define DOES_EXIST_EMAIL 7

#define ERROR_AUTH 8
#define NICKNAME_EXIST 9
#define NICKNAME_NOT_EXIST 10
#define EMAIL_EXIST 11
#define EMAIL_NOT_EXIST 12
#define RECOVERY_FOUND 13
#define RECOVERY_NOT_FOUND 14
#define RIGHT_CODE 15
#define INVALID_CODE 16
#define SUCCESS_RECOVERY 17
#define REGISTRATION_SUCCESSFUL 18

#define MAX_GLOBAL_MESSAGE_SIZE 140

#endif // DEF_H
