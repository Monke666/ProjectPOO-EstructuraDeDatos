#include "filascolumnas.h"
#include "ui_filascolumnas.h"


FilasColumnas::FilasColumnas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilasColumnas)
{
    ui->setupUi(this);
    SpinBox(ui->spinFila, 0, INT_MAX);
    SpinBox(ui->spinColum, 0, INT_MAX);
}

FilasColumnas::~FilasColumnas()
{
    delete ui;
}

int FilasColumnas::getNumeroDeFilas() const
{
    return ui->spinFila->value();
}

int FilasColumnas::getNumeroDeColumnas() const
{
    return ui->spinColum->value();
}

void FilasColumnas::on_btn_Crear_accepted()
{
    accept();
}

void FilasColumnas::on_btn_Crear_rejected()
{
    reject();
}

void FilasColumnas::SpinBox(QSpinBox *spinBox, int min, int max) const
{
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
}

