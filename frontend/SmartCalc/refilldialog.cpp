#include "refilldialog.h"

#include "ui_refilldialog.h"

refilldialog::refilldialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::refilldialog) {
  ui->setupUi(this);
}

refilldialog::~refilldialog() { delete ui; }
