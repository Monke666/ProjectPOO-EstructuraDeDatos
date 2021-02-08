
#ifndef GRAFICARARBOL_H
#define GRAFICARARBOL_H

#include <QString>

struct nodo{
     int num;
     QString nombreAr;
     struct nodo *izq, *der;
 };

typedef struct nodo *ABB;


#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GraficarArbol; }


class GraficarArbol : public QWidget
{
    Q_OBJECT

public:
    GraficarArbol(QWidget *parent = nullptr);
    ~GraficarArbol();
    ABB crearNodo(int x, QString nombreArbol);
    void insertar(ABB &arbol, int x, QString nombreArbol);
    void preOrden(ABB arbol);
    void enOrden(ABB arbol);
    void postOrden(ABB arbol);
    void verArbol(ABB arbol, int n);
    void inicio(int alto, int ancho);
    void circulo(int radio, int x, int y,int incrementox, int incrementoy, QString texto,QColor colorfondo,QColor colorlinea);
    QString nombreAr;
    int n;
    int x;
    ABB arbol = NULL;
    int promedio();
private slots:

    void on_btn_Abrir_clicked();

    void on_btn_Cerrar_clicked();

    void on_btn_Guardar_clicked();

private:
    Ui::GraficarArbol *ui;
    QPixmap pixmap;
    int radio = 30;
    int x1 = 20;
    int y1 = 40;
    int incrementox = 0;
    int incrementoy = 0;
    int incrementox1 = 0;
    int incrementoy1 = 0;
};

#endif // GRAFICARARBOL_H
