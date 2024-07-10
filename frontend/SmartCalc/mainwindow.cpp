#include "mainwindow.h"

#include <QErrorMessage>
#include <QLabel>
#include <QPixmap>
#include <QString>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->lineEdit_result_2->setFocus();
  QDate date = QDate::currentDate();
  ui->dateEdit->setDate(date);

  connect(ui->button_10, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_11, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_12, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_13, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_14, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_15, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_16, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_17, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_18, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));
  connect(ui->button_19, SIGNAL(clicked()), this, SLOT(s21_digit_numbers()));

  connect(ui->button_left_bracket_2, SIGNAL(clicked()), this,
          SLOT(s21_operations()));
  connect(ui->button_right_bracket_2, SIGNAL(clicked()), this,
          SLOT(s21_operations()));
  connect(ui->button_dif_2, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->button_sum_2, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->button_mul_2, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->button_div_2, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->button_mod_2, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->button_degree_2, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->button_sin_2, SIGNAL(clicked()), this, SLOT(s21_functions()));
  connect(ui->button_asin_2, SIGNAL(clicked()), this, SLOT(s21_functions()));
  connect(ui->button_cos_2, SIGNAL(clicked()), this, SLOT(s21_functions()));
  connect(ui->button_acos_2, SIGNAL(clicked()), this, SLOT(s21_functions()));
  connect(ui->button_tan_2, SIGNAL(clicked()), this, SLOT(s21_functions()));
  connect(ui->button_atan_2, SIGNAL(clicked()), this, SLOT(s21_functions()));
  connect(ui->button_ln_2, SIGNAL(clicked()), this, SLOT(s21_functions()));
  connect(ui->button_sqrt_2, SIGNAL(clicked()), this, SLOT(s21_functions()));
  connect(ui->button_log_2, SIGNAL(clicked()), this, SLOT(s21_functions()));

  connect(ui->button_x_2, SIGNAL(clicked()), this, SLOT(s21_x_clicked()));
  connect(ui->button_equal_2, SIGNAL(clicked()), this,
          SLOT(s21_equal_clicked()));
  connect(ui->button_AC_2, SIGNAL(clicked()), this, SLOT(s21_clear()));
  connect(ui->button_point_2, SIGNAL(clicked()), this,
          SLOT(s21_point_clicked()));

  connect(ui->button_plot_2, SIGNAL(clicked()), this, SLOT(s21_plot()));
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(s21_credit_calc()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(s21_debit_calc()));
}

MainWindow::~MainWindow() {
  delete ui->customPlot_2;
  delete ui;
}

void MainWindow::s21_digit_numbers() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label = ui->lineEdit_result_2->text() + button->text();

  ui->lineEdit_result_2->setText(new_label);
}

void MainWindow::s21_operations() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label;

  new_label = ui->lineEdit_result_2->text();

  if (button->text() == "/" && !(ui->lineEdit_result_2->text().endsWith("÷")) &&
      !(ui->lineEdit_result_2->text().endsWith("/"))) {
    new_label += "/";
  } else if (button->text() == "*" &&
             !(ui->lineEdit_result_2->text().endsWith("*"))) {
    new_label += "*";
  } else if (button->text() == "+" &&
             !(ui->lineEdit_result_2->text().endsWith("+"))) {
    new_label += "+";
  } else if (button->text() == "-" &&
             !(ui->lineEdit_result_2->text().endsWith("-"))) {
    new_label += "-";
  } else if (button->text() == "^" &&
             !(ui->lineEdit_result_2->text().endsWith("^"))) {
    new_label += "^";
  } else if (button->text() == "mod" &&
             !(ui->lineEdit_result_2->text().endsWith("mod"))) {
    new_label += "mod";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    new_label += ")";
  }

  ui->lineEdit_result_2->setText(new_label);
}
void MainWindow::s21_functions() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label;

  new_label = ui->lineEdit_result_2->text() + button->text() + "(";

  ui->lineEdit_result_2->setText(new_label);
}

void MainWindow::s21_clear() { ui->lineEdit_result_2->setText(""); }
void MainWindow::s21_x_clicked() {
  QString new_label;

  if (!(ui->lineEdit_result_2->text().endsWith("x")))
    new_label = ui->lineEdit_result_2->text() + "x";

  ui->lineEdit_result_2->setText(new_label);
}
void MainWindow::s21_point_clicked() {
  if (!(ui->lineEdit_result_2->text().endsWith('.')))
    ui->lineEdit_result_2->setText(ui->lineEdit_result_2->text() + ".");
}

void MainWindow::s21_equal_clicked() {
  QString input = ui->lineEdit_result_2->text();
  QByteArray byteArray = input.toLocal8Bit();
  char *expression = byteArray.data();

  bool status_x = 1;
  Node *stack = NULL;
  Node *rev_stack = NULL;
  double x_val = ui->lineEdit_x_2->text().toDouble(&status_x);
  double result = 0;

  if (status_x) {
    int status = check_validation(expression);
    if (status == OK) {
      status = parser(expression, &stack);
      if (status == OK) {
        reverse_stack(&stack, &rev_stack);
        free_stack(&stack);
        reverse_polish_notation(&rev_stack, &stack);
        free_stack(&rev_stack);
        reverse_stack(&stack, &rev_stack);
        status = calculate(&rev_stack, x_val, &result);
        if (status == OK) {
          ui->lineEdit_result_2->setText(QString::number(result));
        } else {
          // ui->lineEdit_result->setText("ERROR IN CALCULATION");
          (new QErrorMessage(this))->showMessage("ERROR IN CALCULATION");
        }
      } else {
        (new QErrorMessage(this))->showMessage("INVALID EXPRESSION");
      }
      free_stack(&stack);
      free_stack(&rev_stack);
    } else {
      // ui->lineEdit_result->setText("INVALID EXPRESSION");
      (new QErrorMessage(this))->showMessage("INVALID EXPRESSION");
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    // ui->lineEdit_result->setText("INVALID X VALUE");
    (new QErrorMessage(this))->showMessage("INVALID X VALUE");
  }
}

void MainWindow::s21_plot() {
  QString input = ui->lineEdit_result_2->text();
  QByteArray byteArray = input.toLocal8Bit();
  char *expression = byteArray.data();

  bool status_x_min = 1;
  bool status_y_min = 1;
  bool status_x_max = 1;
  bool status_y_max = 1;
  bool status_step = 1;

  Node *stack = NULL;
  Node *rev_stack = NULL;

  QVector<double> x, y;

  double x_max = ui->lineEdit_11->text().toDouble(&status_x_max);
  double x_min = ui->lineEdit_8->text().toDouble(&status_x_min);
  double y_max = ui->lineEdit_12->text().toDouble(&status_y_max);
  double y_min = ui->lineEdit_9->text().toDouble(&status_y_min);
  double h = ui->lineEdit_10->text().toDouble(&status_step);

  double X = 0;
  double Y = 0;
  int N = 0;
  double result = 0;

  if (status_x_max && status_x_min && status_y_max && status_y_min &&
      (x_min >= -1000000 && x_max <= 1000000) &&
      (y_min >= -1000000 && y_max <= 1000000) && status_step) {
    ui->customPlot_2->clearGraphs();
    x.clear();
    y.clear();
    ui->customPlot_2->xAxis->setRange(x_min, x_max);
    ui->customPlot_2->yAxis->setRange(y_min, y_max);

    X = x_min;
    int status = check_validation(expression);
    if (status == OK) {
      for (X = x_min; X <= x_max && (status == OK); X = X + h) {
        status = parser(expression, &stack);
        if (status == OK) {
          reverse_stack(&stack, &rev_stack);
          free_stack(&stack);
          reverse_polish_notation(&rev_stack, &stack);
          free_stack(&rev_stack);
          reverse_stack(&stack, &rev_stack);
          status = calculate(&rev_stack, X, &Y);
          if (Y > 1000000 || Y < -1000000 || Y > y_max || Y < y_min)
            continue;
          else {
            x.push_back(X);
            y.push_back(Y);
          }
        } else {
          break;
        }
      }
      if (status == OK) {
        ui->customPlot_2->addGraph();
        ui->customPlot_2->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot_2->graph(0)->setScatterStyle(
            QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
        ui->customPlot_2->graph(0)->addData(x, y);
        ui->customPlot_2->setInteraction(QCP::iRangeZoom, true);
        ui->customPlot_2->setInteraction(QCP::iRangeDrag, true);
        ui->customPlot_2->replot();
      } else {
        // ui->lineEdit_result->setText("ERROR IN CALCULATION");
        (new QErrorMessage(this))->showMessage("ERROR IN CALCULATION");
      }
      free_stack(&stack);
      free_stack(&rev_stack);
    } else {
      // ui->lineEdit_result->setText("INVALID EXPRESSION");
      (new QErrorMessage(this))->showMessage("INVALID EXPRESSION");
    }
    free_stack(&stack);
    free_stack(&rev_stack);
  } else {
    // ui->lineEdit_result->setText("INVALID X VALUE");
    (new QErrorMessage(this))
        ->showMessage("INVALID BORDER X, Y OR INVALID STEP");
  }
}

void MainWindow::s21_credit_calc() {
  bool status_total_amount = 1;
  bool status_term = 1;
  bool status_rate = 1;

  double total_amount = ui->lineEdit->text().toDouble(&status_total_amount);
  double term = ui->lineEdit_2->text().toDouble(&status_term);
  double rate = ui->lineEdit_13->text().toDouble(&status_rate);

  long double monthly_rate = 0;
  double monthly_term = 0;

  long double part = 0;
  long double percent = 0;

  long double min_pay = 0;
  long double max_pay = 0;

  long double monthly_payment = 0;
  long double overpayment = 0;
  long double total_payment = 0;

  if (status_total_amount && status_term && status_rate && total_amount > 0 &&
      term > 0 && rate > 0) {
    monthly_term = term;
    if (ui->comboBox->currentIndex() == 1) {
      monthly_term = term * 12;
    }
    monthly_rate = rate / (long double)(100. * 12);
    if (ui->radioButton->isChecked()) {
      monthly_payment =
          (long double)total_amount * monthly_rate /
          (long double)(1. - powl(1. + monthly_rate, -1. * monthly_term));
      total_payment = monthly_payment * (long double)monthly_term;
      overpayment = total_payment - (long double)total_amount;
      ui->label_19->setText(QString::number(monthly_payment, 'g', 10));
      ui->label_19->setText(ui->label_19->text() += " руб.");
    } else {
      part = total_amount / (long double)monthly_term;
      max_pay = part + (long double)total_amount * monthly_rate;
      min_pay = 0;
      for (int i = 0; i < monthly_term; i++) {
        min_pay = part + (total_amount - part * i) * monthly_rate;
        total_payment += min_pay;
      }
      ui->label_19->setText(QString::number(max_pay, 'g', 10));
      ui->label_19->setText(ui->label_19->text() += "...");
      ui->label_19->setText(ui->label_19->text() +=
                            QString::number(min_pay, 'g', 10));
      ui->label_19->setText(ui->label_19->text() += " руб.");
      overpayment = total_payment - (long double)total_amount;
    }
    ui->label_21->setText(QString::number(overpayment, 'g', 10));
    ui->label_21->setText(ui->label_21->text() += " руб.");
    ui->label_23->setText(QString::number(total_payment, 'g', 10));
    ui->label_23->setText(ui->label_23->text() += " руб.");

  } else {
    (new QErrorMessage(this))->showMessage("INVALID DATA");
  }
}

void MainWindow::s21_debit_calc() {
  bool status_total_amount = 1;
  bool status_term = 1;
  bool status_rate = 1;
  bool status_rate_cb = 1;

  double total_amount = ui->lineEdit_3->text().toDouble(&status_total_amount);
  double term = ui->lineEdit_4->text().toDouble(&status_term);
  double rate = ui->lineEdit_5->text().toDouble(&status_rate);
  double rate_cb = ui->lineEdit_6->text().toDouble(&status_rate_cb);

  double total_percent = 0;
  double tax_amount = 0;
  double deposit_amount = 0;

  long double monthly_rate = 0;
  double monthly_term = 0;
  QDate open_date = ui->dateEdit->date();

  if (status_total_amount && status_term && status_rate && status_rate &&
      total_amount > 0 && term > 0 && rate > 0 && rate_cb > 0) {
    monthly_term = term;
    if (ui->comboBox_2->currentIndex() == 1) {
      monthly_term = term * 12;
    }
    QDate end_date = open_date.addMonths(int(monthly_term));
    int count_of_days = open_date.daysTo(end_date);

    // monthly_rate = rate / (long double)(100. * 12);

    if (ui->checkBox->isChecked()) {
      total_percent = count_of_days;
    } else {
      total_percent = total_amount * rate * count_of_days / 365 / 100;
      deposit_amount = total_amount;
      QDate pre_month = open_date;
      QDate cur_month = open_date.addMonths(1);
      double deposit = 0.0;
      if (ui->comboBox_3->currentIndex() == 0) {
        double year_dep = 0.0;
        for (int i = open_date.month(); i < open_date.month() + monthly_term;
             i++) {
          int count_day_to_month = pre_month.daysTo(cur_month);
          deposit += total_amount * rate * count_day_to_month / 365 / 100;
          year_dep += total_amount * rate * count_day_to_month / 365 / 100;
          if (i % 11 == 0 || i == (open_date.month() + monthly_term - 1)) {
            if (year_dep > rate_cb * 10000) {
              tax_amount = tax_amount + (year_dep - (rate_cb * 10000)) * 0.13;
            }
            year_dep = 0.0;
          }
          pre_month = cur_month;
          QDate tmp = cur_month.addMonths(1);
          cur_month = tmp;
        }
      } else {
        total_percent = 0;
        double year_dep = 0.0;
        int count_day_to_year = 0;
        for (int i = open_date.month(); i < open_date.month() + monthly_term;
             i++) {
          int count_day_to_month = pre_month.daysTo(cur_month);
          count_day_to_year += count_day_to_month;
          if (count_day_to_year > 364) {
            deposit += total_amount * rate / 100;
            year_dep = total_amount * rate / 100;
            count_day_to_year = 0;
          }
          if (i == (open_date.month() + monthly_term - 1)) {
            deposit += total_amount * rate * count_day_to_year / 365 / 100;
            year_dep += total_amount * rate * count_day_to_year / 365 / 100;
          }
          if (i % 11 == 0 || i == (open_date.month() + monthly_term - 1)) {
            if (year_dep > rate_cb * 10000) {
              tax_amount = tax_amount + (year_dep - (rate_cb * 10000)) * 0.13;
            }
            year_dep = 0.0;
          }
          pre_month = cur_month;
          QDate tmp = cur_month.addMonths(1);
          cur_month = tmp;
        }
        total_percent = deposit;
      }
    }
    ui->label_34->setText(QString::number(total_percent, 'g', 10));
    ui->label_34->setText(ui->label_34->text() += " руб.");
    ui->label_35->setText(QString::number(tax_amount, 'g', 10));
    ui->label_35->setText(ui->label_35->text() += " руб.");
    ui->label_37->setText(QString::number(deposit_amount, 'g', 10));
    ui->label_37->setText(ui->label_37->text() += " руб.");
  } else {
    (new QErrorMessage(this))->showMessage("INVALID DATA");
  }
}

void MainWindow::on_pushButton_3_clicked() { refill.show(); }

void MainWindow::on_pushButton_5_clicked() { withdraw.show(); }
