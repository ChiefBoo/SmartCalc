#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QErrorMessage>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_result_2->setFocus();
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

    connect(ui->button_left_bracket_2, SIGNAL(clicked()), this, SLOT(s21_operations()));
    connect(ui->button_right_bracket_2, SIGNAL(clicked()), this, SLOT(s21_operations()));
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
    connect(ui->button_equal_2, SIGNAL(clicked()), this, SLOT(s21_equal_clicked()));
    connect(ui->button_AC_2, SIGNAL(clicked()), this, SLOT(s21_clear()));
    connect(ui->button_point_2, SIGNAL(clicked()), this, SLOT(s21_point_clicked()));

    connect(ui->button_plot_2, SIGNAL(clicked()), this, SLOT(s21_plot()));
}

MainWindow::~MainWindow()
{   
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

void MainWindow::s21_clear() {
    ui->lineEdit_result_2->setText("");
}
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
    Node* stack = NULL;
    Node* rev_stack = NULL;
    double x_val = ui->lineEdit_x_2->text().toDouble(&status_x);
    double result = 0;

    if (status_x) {
        int status = check_validation(expression);
        if (status == OK) {
            parser(expression, &stack);
            reverse_stack(&stack, &rev_stack);
            free_stack(&stack);
            reverse_polish_notation(&rev_stack, &stack);
            free_stack(&rev_stack);
            reverse_stack(&stack, &rev_stack);
            status = calculate(&rev_stack, x_val, &result);
            if (status == OK) {
                ui->lineEdit_result_2->setText(QString::number(result));
            } else {
                //ui->lineEdit_result->setText("ERROR IN CALCULATION");
                (new QErrorMessage(this))->showMessage("ERROR IN CALCULATION");
            }
            free_stack(&stack);
            free_stack(&rev_stack);
        } else {
            //ui->lineEdit_result->setText("INVALID EXPRESSION");
            (new QErrorMessage(this))->showMessage("INVALID EXPRESSION");
            
        }
    } else {
        //ui->lineEdit_result->setText("INVALID X VALUE");
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

    Node* stack = NULL;
    Node* rev_stack = NULL;

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
            (x_min >= -1000000 && x_max <= 1000000) && (y_min >= -1000000 && y_max <= 1000000) && status_step) {
        ui->customPlot_2->clearGraphs();
        x.clear();
        y.clear();
        ui->customPlot_2->xAxis->setRange(x_min, x_max);
        ui->customPlot_2->yAxis->setRange(y_min, y_max);
     
        X = x_min;
        int status = check_validation(expression);
        if (status == OK) {
            for (X = x_min; X <= x_max && (status == OK); X = X + h) {
                parser(expression, &stack);
                reverse_stack(&stack, &rev_stack);
                free_stack(&stack);
                reverse_polish_notation(&rev_stack, &stack);
                free_stack(&rev_stack);
                reverse_stack(&stack, &rev_stack);
                status = calculate(&rev_stack, X, &Y);
                if (Y > 1000000 || Y < -1000000 || Y > y_max || Y < y_min) continue;
                else {
                    x.push_back(X);
                    y.push_back(Y);
                }
            }        
            if (status == OK) {
                ui->customPlot_2->addGraph();
                ui->customPlot_2->graph(0)->addData(x, y);
                ui->customPlot_2->replot();
                ui->customPlot_2->setInteraction(QCP::iRangeZoom, true);
                ui->customPlot_2->setInteraction(QCP::iRangeDrag, true);
            } else {
                //ui->lineEdit_result->setText("ERROR IN CALCULATION");
                (new QErrorMessage(this))->showMessage("ERROR IN CALCULATION");
            }
            free_stack(&stack);
            free_stack(&rev_stack);
        } else {
            //ui->lineEdit_result->setText("INVALID EXPRESSION");
            (new QErrorMessage(this))->showMessage("INVALID EXPRESSION");
            
        }
    } else {
        //ui->lineEdit_result->setText("INVALID X VALUE");
        (new QErrorMessage(this))->showMessage("INVALID BORDER X, Y OR INVALID STEP");
    }

}
