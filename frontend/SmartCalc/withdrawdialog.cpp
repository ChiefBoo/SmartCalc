#include "withdrawdialog.h"

#include "ui_withdrawdialog.h"

withdrawdialog::withdrawdialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::withdrawdialog) {
  ui->setupUi(this);
}

withdrawdialog::~withdrawdialog() { delete ui; }
