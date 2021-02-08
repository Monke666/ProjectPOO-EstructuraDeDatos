#ifndef INGRESARNOTAS_H
#define INGRESARNOTAS_H

#include <QWidget>
#include <QStandardItemModel>
#include "estudiante.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

namespace Ui {
class ingresarNotas;
}

class ingresarNotas : public QWidget
{
    Q_OBJECT

public:
    explicit ingresarNotas(QList <notas*> m_notas, QWidget *parent = nullptr);
    ~ingresarNotas();

private slots:

    void on_btn_Guardar_clicked();

    void on_btn_Cerrar_clicked();

    void on_btn_Anadir_clicked();

    void Promedio(const QModelIndex &index);


private:
    Ui::ingresarNotas *ui;
    QStandardItemModel *csvModel;
};

#endif // INGRESARNOTAS_H
