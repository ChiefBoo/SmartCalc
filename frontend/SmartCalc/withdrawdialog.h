#ifndef WITHDRAWDIALOG_H
#define WITHDRAWDIALOG_H

#include <QDialog>

namespace Ui {
class withdrawdialog;
}

class withdrawdialog : public QDialog {
  Q_OBJECT

 public:
  explicit withdrawdialog(QWidget *parent = nullptr);
  ~withdrawdialog();

 private:
  Ui::withdrawdialog *ui;
};

#endif  // WITHDRAWDIALOG_H
