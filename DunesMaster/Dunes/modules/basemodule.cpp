#include "basemodule.h"
#include "modulelistitem.h"
#include "modulelist.h"
#include <QPainter>
#include <QDebug>
#include <unordered_map>
BaseRegistry::map_type BaseRegistry::map;

const QString BaseModule::title = "Base";
const QString BaseModule::description = "Description";

BaseModule::BaseModule()
{
    m_layout = new QGridLayout(this);
    m_titleLabel = new QLabel();
    m_titleLabel->setText("ERROR");
    m_layout->addWidget(m_titleLabel);
    setObjectName("BaseModule");
    setStyleSheet("#BaseModule { background-color: white; border: 3px solid grey; border-radius:20px; }");
    m_optionsPanel = new QWidget();
    m_optionsPanel->setObjectName("optionsPanel");
    m_layout->setVerticalSpacing(0);
    m_layout->addWidget(m_optionsPanel, 1, 0, 1, 1);

    setFocusPolicy(Qt::ClickFocus);
}

BaseModule::~BaseModule() {
    //TODO maybe delete title label and other widgets?
}

void BaseModule::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragStartPosition = event->pos();
    }
}

void BaseModule::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
    {
        return;
    }
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
    {
        return;
    }
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    QGridLayout *blockArea = (QGridLayout *)parentWidget()->layout();
    std::unordered_map<int, int> rowToCol;
    for(int idx = 0; idx < blockArea->count(); idx++){
        int row, col, rowSpan, colSpan;
        blockArea->getItemPosition(idx, &row, &col, &rowSpan, &colSpan);

        rowToCol.insert({row, col});
    }

    for(const std::pair<int, int>& p : rowToCol)
    {
        if(blockArea->itemAtPosition(p.first, p.second)->widget() == this)
        {
            mimeData->setProperty("index", p.first);
        }
    }

    drag->setMimeData(mimeData);
    drag->exec(Qt::MoveAction);
}

// When you click on a module, change it's outline to blue
void BaseModule::focusInEvent(QFocusEvent*) {
    setStyleSheet("#BaseModule { background-color: white; border: 3px solid lightblue; border-radius:20px; }");
    setObjectName("BaseModuleSelected");
}

// When you click on something else, change it's outline back to grey
void BaseModule::focusOutEvent(QFocusEvent*) {
    setObjectName("BaseModule");
    setStyleSheet("#BaseModule { background-color: white; border: 3px solid grey; border-radius:20px; }");
}

// Redirect keypress events to our emmitter
void BaseModule::keyPressEvent(QKeyEvent *e)
{
    emit keyPressed(this, e);
}

// When strings the user entered get compiled into javascript strings, we need to escape \ and "
// Ex: user enters: google.com/asd"fdsf, the result would be something like download_page("google.com/asd"fdsf")
// We need to make that download_page("google.com/asd\"fdsf")
QString BaseModule::escapeString(QString s) {
    s.replace(QRegExp("\\"), "\\\\");
    s.replace(QRegExp("\""), "\\\"");
    return s;
}

// Creates an entry in the modulelist.
// Used in the setup() function but implemented here to prevent a circular header inclusion
void BaseModule::createModuleListItem(ModuleList* list, QString title, QString description, ModuleType type) {
    list->addItem(new ModuleListItem(title, description, type));
}

// This paint event needs to be implemented for our css to work
void BaseModule::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
