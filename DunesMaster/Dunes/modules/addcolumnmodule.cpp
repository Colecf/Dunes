#include "addcolumnmodule.h"
#include "modulelistitem.h"

const QString AddColumnModule::title = "AddColumn";
const QString AddColumnModule::description = "Adds a cell to the output spreadsheet. This cell will have the contents of the current input stream, and will be added to a new column in the current row.";

AddColumnModule::AddColumnModule()
{
    m_titleLabel->setText(title);
}

QString AddColumnModule::getCode(){
    return "add_column(top());\n";
}

QString AddColumnModule::getConfig(QString col){
    return "type=" + QString::number(type) + ";" + "col=" + col + ";" + "\n";
}
