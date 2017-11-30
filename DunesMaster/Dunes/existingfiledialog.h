#include <QLineEdit>

#ifndef EXISTINGFILEDIALOG_H
#define EXISTINGFILEDIALOG_H


class ExistingFileDialog : public QLineEdit
{
public:
    ExistingFileDialog();
protected:
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // EXISTINGFILEDIALOG_H
