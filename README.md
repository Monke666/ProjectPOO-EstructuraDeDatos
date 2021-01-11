//ProjectPOO-EstructuraDeDatos
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filascolumnas.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDataStream>
#include <QStandardItemModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    HojaCalculo = new QStandardItemModel(this);
    ui->tableView->setModel(HojaCalculo);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbrir_triggered()
{
    auto filename = QFileDialog::getOpenFileName(this, "A B R I R",
        QDir::rootPath(), "CSV File (*.csv)");
    if (filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream xin(&file);
    int ix = 0;
    while (!xin.atEnd()) {
        auto line = xin.readLine();
        auto elements = line.split(",");
        const int elementsSize = elements.size();
        HojaCalculo->setRowCount(ix + 1);
        HojaCalculo->setColumnCount(elementsSize);
        for (int jx = 0; jx < elementsSize; ++jx) {
            setValueAt(ix, jx, elements.at(jx));
        }
        ++ix;
    }
}

void MainWindow::on_actionGuardar_Como_triggered()
{
    QString nombreArchivo;
    QFile Archivo;

    nombreArchivo = QFileDialog::getSaveFileName(this, "G U A R D A R  C O M O",
        QDir::rootPath(), "CSV File (*.csv)");
    if (nombreArchivo.isEmpty()) {
        return;
    }
    Archivo.setFileName(nombreArchivo);
    if (!Archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream xout(&Archivo);
    const int rowCount = HojaCalculo->rowCount();
    const int colCount = HojaCalculo->columnCount();
    for (int i = 0; i < rowCount; ++i) {
        xout << getValueAt(i, 0);
        for (int j = 1; j < colCount; ++j) {
            xout << ", " << getValueAt(i, j);
        }
        xout << "\n";
    }
    Archivo.flush();
    Archivo.close();
}

void MainWindow::on_actionNuevo_triggered()
{
    FilasColumnas nuevo(this);
    if (nuevo.exec() == QDialog::Rejected) {
        return;
    }
    const int rowCount = nuevo.getNumeroDeFilas();
    const int colCount = nuevo.getNumeroDeColumnas();
    HojaCalculo->setRowCount(rowCount);
    HojaCalculo->setColumnCount(colCount);
}

QString MainWindow::getValueAt(int i, int j) const
{
    if (!HojaCalculo->item(i,j)) {
        return "";
    }
    return HojaCalculo->item(i,j)->text();
}

void MainWindow::setValueAt(int i, int j, const QString &value)
{
    if (!HojaCalculo->item(i,j)) {
        HojaCalculo->setItem(i,j, new QStandardItem(value));
    } else {
        HojaCalculo->item(i,j)->setText(value);
    }
}

void MainWindow::on_actionCerrar_triggered()
{
    close();
}
