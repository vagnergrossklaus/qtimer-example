#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

private:
    int _countColorChanges = 0;

    Ui::MainWindow* ui;
    QTimer _clockTimer;
    QTimer _colorTimer;
    QTimer _colorTimerRemainingTime;
    QRandomGenerator _randomGenerator;

private slots:
    void onClockTimerTimeout();
    void onPbtSingleShotClicked();
    void onPbtColorStopClicked();
    void onColorTimerTimeout();
    void onColorTimerRemainingTimeTimeout();
    void onSingleShot();

};
#endif // MAINWINDOW_H
