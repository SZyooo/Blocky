#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QMainWindow>

class EditWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditWindow(QWidget *parent = nullptr);
    ~EditWindow();
};
#endif // EDITWINDOW_H
