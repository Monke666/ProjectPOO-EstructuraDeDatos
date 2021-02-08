#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graficodebarras.h"
#include "ui_graficodebarras.h"
#include <QPainter>
#include <QPen>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

GraficoDeBarras::GraficoDeBarras(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraficoDeBarras)
{
    ui->setupUi(this);
    setWindowTitle("GRAFICO DE BARRAS");
    ui->Imagen->resize(alto + 60, ancho + 40);
    pixmap = QPixmap(ui->Imagen->size());
    iniciar(ancho,20);
    ejes(iniciox, inicioy, 2,ancho,alto,Qt::black);
    ui->Imagen->setPixmap(pixmap);
}

GraficoDeBarras::~GraficoDeBarras()
{
    delete ui;
}
void GraficoDeBarras::iniciar(int ancho, int alto){
    pixmap.fill(Qt::white);
    painter.begin(&pixmap);
    pen.setColor(Qt::black);
    texto((ancho/3), alto+5, "PONDERACIÓN DE NOTAS", 12);
}

void GraficoDeBarras::texto(int x, int y, QString texto, int tamanio){
    painter.setPen(pen);
    QFont font = painter.font();
    font.setPixelSize(tamanio);
    painter.setFont(font);
    painter.drawText(x,y,texto);
}

void GraficoDeBarras::ejes(int iniciox,int inicioy, int grosor, int ancho, int alto, QColor color){
    pen.setWidth(grosor);
    pen.setColor(color);
    pen.setJoinStyle(Qt::MiterJoin);
    painter.setPen(pen);
    painter.drawLine(iniciox, inicioy-30 ,iniciox, alto);
    texto(iniciox-12, 20, "Y", 16);
    painter.drawLine(iniciox,alto,ancho,alto);
    texto(ancho, alto+20, "X", 16);
    painter.drawLine(iniciox-3,alto/2,12,alto/2);
    pen.setColor(Qt::black);
    texto(0, alto/2, "50", 9);

}

void GraficoDeBarras::barra(int desplazamiento, int iniciox, int inicioy, int alto, int nota, QString nombre)
{
    if (nota > 69){
        painter.setBrush(Qt::green);
    }else{
        painter.setBrush(Qt::red);
    }
    pen.setColor(Qt::black);
    painter.setPen(pen);
    if (nota==0)
       inicioy=alto;
    else
       if (nota == 40)
          inicioy=(alto/2);
       else
    inicioy= alto -((alto*nota)/100)+15;
    texto(iniciox+12+desplazamiento, inicioy-12, nombre, 12);
    texto(iniciox+12+desplazamiento, inicioy-22, QString::number(nota), 12);
    painter.drawRect(iniciox+20+desplazamiento, inicioy, 20,alto - inicioy);
}

void GraficoDeBarras::lineaPromedio(int iniciox, int alto, int notaPromedio)
{
    painter.setBrush(Qt::green);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    int valor;
    if (notaPromedio == 0)
       valor = 0;
    else
       if (notaPromedio == 70)
          valor = -(alto / 2);
       else
          valor= alto -((alto*notaPromedio)/100)+15;
    painter.drawRect(iniciox+10, valor ,ancho-20,1);
    texto(iniciox+10, valor+10 ,QString::number(notaPromedio), 10);
}

void GraficoDeBarras::on_btn_Imagen_clicked()
{
    QString nombreArchivo;
    QTextStream entrada;
    QFile file;

    QString Apellido, Nota;
    int i = 0;
    int vi1 = 0;
    int flag1 = 1;
    int flag2 = 4;
    int vnotaf;
    int acumulanota = 0;
    int cuenta = 0;

    //LEER ARCHIVO: CSV
    nombreArchivo = QFileDialog::getOpenFileName(this, "A B R I R", QDir::rootPath(), "CSV File (*.csv)");
    file.setFileName(nombreArchivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QMessageBox::information(this,"A V I S O","Archivo no Abierto");
            }else{
        }
    QTextStream in(&file);
    while (!in.atEnd()){
    QString line = in.readLine();
    QList<QStandardItem *> standardItemsList;

      for (QString item : line.split(";")) {
           standardItemsList.append(new QStandardItem(item));

           if (i==flag1){
               Apellido = item;
               flag1+=5;
           }
           if (i==flag2){
               QString notap = item;
               vnotaf=notap.toInt();
               acumulanota=acumulanota+vnotaf;
               cuenta=cuenta+1;
               barra(vi1,iniciox, inicioy,alto,vnotaf,Apellido);
               vi1=vi1+30;
               flag2+=5;
           }
           i=i+1;
      }

     }
    lineaPromedio(iniciox,alto,(acumulanota/cuenta));
    ui->Imagen->setPixmap(pixmap);
}



void GraficoDeBarras::on_btn_Guardar_clicked()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,"Guardar imagen",QString(),"Imagenes (*.png)");
        if (!nombreArchivo.isEmpty()){
             if (pixmap.save(nombreArchivo)){
                  QMessageBox::information(
                              this,"Guardar imagen","Archivo almacenado en: " + nombreArchivo);
             }else{
                 QMessageBox::warning(
                             this,"Guardar imagen","No se pudo guardar el archivo");
             }
        }
    }

void GraficoDeBarras::on_btn_Abrir_clicked()
{
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this, "Abrir", QString(), "Imagen(*.png)");
    if (!nombreArchivo.isEmpty()){
        QImage archivoImagen(nombreArchivo); //VERIFICA SI EL ARCHIVO ES VALIDO EN EL FORMATO
        if (archivoImagen.isNull()){
            QMessageBox::information(this,"ERROR","Imagen no Valida");
            return;
        }
        ui->Imagen->setPixmap(QPixmap::fromImage(archivoImagen));
        ui->Imagen->adjustSize();
    }
}

void GraficoDeBarras::on_btn_Cerrar_clicked()
{
    close();
}
