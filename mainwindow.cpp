#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <limits>
#include <math.h>

#include <QDebug>
#include <QDateTime>
#include <QThread>

MainWindow::MainWindow( QWidget* parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ) {
    ui->setupUi( this );

    QObject::connect( ui->pbtSingleShot, &QPushButton::clicked, this, &MainWindow::onPbtSingleShotClicked );
    QObject::connect( ui->pbtColorStop, &QPushButton::clicked, this, &MainWindow::onPbtColorStopClicked );

    QObject::connect( &_clockTimer, &QTimer::timeout, this, &MainWindow::onClockTimerTimeout );
    _clockTimer.start( 500 );

    QObject::connect( &_colorTimer, &QTimer::timeout, this, &MainWindow::onColorTimerTimeout );
//    _colorTimer.setSingleShot( true );
//    _colorTimer.setInterval( 1000 );
//    _colorTimer.start();

    QObject::connect( &_colorTimerRemainingTime, &QTimer::timeout, this, &MainWindow::onColorTimerRemainingTimeTimeout );
    _colorTimerRemainingTime.setInterval( 10 );
    _colorTimerRemainingTime.start();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onClockTimerTimeout() {
    qDebug() << "onClockTimerTimeout";
    ui->lblClock->setText( QDateTime::currentDateTime().toString( "dd-MM-yyyy hh:mm:ss" ) );
}

void MainWindow::onPbtSingleShotClicked() {
    QTimer::singleShot( 0, this, &MainWindow::onSingleShot );
    QTimer::singleShot( ui->ledSingleShot->text().toInt(), [this]() {
        qDebug() << "onPbtSingleShotClicked";
        ui->lblSingleShotCustomTime->setText( QString( "Disparado após %1 miliseconds" ).arg( ui->ledSingleShot->text().toInt() ) );
    } );
}

void MainWindow::onPbtColorStopClicked() {
    qDebug() << "onPbtColorStopClicked";
    _colorTimer.stop();
}

void MainWindow::onColorTimerTimeout() {
    qDebug() << "onColorTimerTimeout";
    ui->lblColor->setStyleSheet( QString( "border: 1px solid; border-color: #000000; background-color: #%1" ).arg( QString::number( QRandomGenerator::global()->bounded( 0, 999999 ) ).leftJustified( 6, '0' ) ) );
//    _colorTimer.start( QRandomGenerator::global()->bounded( 1000, 5000 ) );
//    _colorTimer.setInterval( QRandomGenerator::global()->bounded( 1000, 5000 ) );
    ui->lblColorChangesCount->setText( QString( "A cor foi trocada %1 vezes" ).arg( ++_countColorChanges ) );
//    QEventLoop eventLoop;
//    eventLoop.exec();
}

void MainWindow::onColorTimerRemainingTimeTimeout() {
    qDebug() << "onColorTimerRemainingTimeTimeout";
    if ( _colorTimer.isActive() ) {
        ui->lblRemainingTime->setText( QString ( "A cor irá mudar em %1 milisegundos" ).arg( _colorTimer.remainingTime() ) );
    } else{
        _colorTimerRemainingTime.stop();
        ui->lblRemainingTime->setText( "Essa foi a ultima cor :(" );
    }
}

void MainWindow::onSingleShot() {
    ui->lblSingleShotCustomTime->setText( QString( "Disparando em %1 miliseconds ..." ).arg( ui->ledSingleShot->text().toInt() ) );
}
