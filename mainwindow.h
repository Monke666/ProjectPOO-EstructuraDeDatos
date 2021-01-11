#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbrir_triggered();

    void on_actionGuardar_Como_triggered();

    void on_actionCerrar_triggered();

    void on_actionNuevo_triggered();

private:
    QString getValueAt(int i, int j) const;
    void setValueAt(int i, int j, const QString &value);

    Ui::MainWindow *ui;
    QStandardItemModel *HojaCalculo;
};
#endif // MAINWINDOW_H
