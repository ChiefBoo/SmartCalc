#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <refilldialog.h>
#include <withdrawdialog.h>

#include <QMainWindow>
#include <QVector>

#include "../../backend/qcustomplot.h"

extern "C" {
#include "../../backend/smartcalc.h"
#include "../../backend/stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  refilldialog refill;
  withdrawdialog withdraw;

 private slots:
  void s21_digit_numbers();
  void s21_functions();
  void s21_operations();
  void s21_x_clicked();
  void s21_point_clicked();
  void s21_equal_clicked();
  void s21_clear();
  void s21_plot();
  void s21_credit_calc();
  void s21_debit_calc();

  void on_pushButton_3_clicked();
  void on_pushButton_5_clicked();
};
#endif  // MAINWINDOW_H
