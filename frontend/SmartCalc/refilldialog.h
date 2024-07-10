#ifndef REFILLDIALOG_H
#define REFILLDIALOG_H

#include <QDialog>

namespace Ui {
class refilldialog;
}

class refilldialog : public QDialog {
  Q_OBJECT

 public:
  explicit refilldialog(QWidget *parent = nullptr);
  ~refilldialog();

 private:
  Ui::refilldialog *ui;
};

#endif  // REFILLDIALOG_H
