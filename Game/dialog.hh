#ifndef DIALOG_HH
#define DIALOG_HH

#include "mainwindow.hh"
#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>

/**
 * @file
 * @brief Defines the appearance and operations of the Dialog window class.
 */

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    /**
     * @brief on_pulsu1Button_clicked chooses character 1.
     * @pre Button is clicked.
     * @post Dialog image is set to version 1, pulsuType_ is set to 1,
     * twoPlayerMode is set to false.
     */
    void on_pulsu1Button_clicked();

    /**
     * @brief on_pulsu2Button_clicked chooses character 2.
     * @pre Button is clicked.
     * @post Dialog image is set to version 2, pulsuType_ is set to 2,
     * twoPlayerMode is set to false.
     */
    void on_pulsu2Button_clicked();

    /**
     * @brief accept closes dialog and sends pulsuType_ and twoPlayerMode_.
     * @pre One of the radio buttons is clicked.
     * @post sendPulsutype(pulsuType_), sendTwoPlayerMode(twoPlayerMode_)
     * and QDialog::accept() are called.
     */
    void accept() override;

    /**
     * @brief reject closes dialog.
     * @pre -
     * @post dontStart() is emitted and QDialog::reject() is called.
     */
    void reject() override;

    /**
     * @brief on_twoPlayerButton_clicked chooses two player mode.
     * @pre Button is clicked.
     * @post pulsuType_ is set to 1, twoPlayerMode_ is set to true.
     */
    void on_twoPlayerButton_clicked();

signals:
    void sendPulsuType(int type);
    void sendTwoPlayerMode(bool onko);
    void dontStart();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    int pulsuType_;
    bool twoPlayerMode_;
};

#endif // DIALOG_HH
