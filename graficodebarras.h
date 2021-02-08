#ifndef GRAFICODEBARRAS_H
#define GRAFICODEBARRAS_H

#include <QDialog>
#include <QPen>
#include <QPainter>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QStandardItemModel>

namespace Ui {
class GraficoDeBarras;
}

class GraficoDeBarras : public QDialog
{
    Q_OBJECT

public:
    explicit GraficoDeBarras(QWidget *parent = nullptr);
    ~GraficoDeBarras();
    int ancho = 500;
    int alto = 500;
    int iniciox = 40;
    int inicioy = 60;

public slots:
        void iniciar(int ancho, int alto);
        void texto(int x, int y, QString texto, int tamanio);
        void ejes(int iniciox,int inicioy, int grosor, int ancho, int alto, QColor color);
        void barra(int desplazamiento,int iniciox, int inicioy, int alto, int nota, QString nombre);
        void lineaPromedio(int iniciox, int alto, int notaPromedio);


private slots:
    void on_btn_Imagen_clicked();

    void on_btn_Guardar_clicked();

    void on_btn_Abrir_clicked();

    void on_btn_Cerrar_clicked();

private:
    Ui::GraficoDeBarras *ui;
    QPixmap pixmap;
    QPen pen;
    QPainter painter;
    QStandardItemModel *csvModel;


};

#endif // GRAFICODEBARRAS_H


