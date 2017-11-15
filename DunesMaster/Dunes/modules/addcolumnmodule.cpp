#include "addcolumnmodule.h"
#include "modulelistitem.h"

const QString AddColumnModule::title = "AddColumn";
const QString AddColumnModule::description = "AddColumn Description";

AddColumnModule::AddColumnModule()
{
    m_titleLabel->setText(title);
}

QString AddColumnModule::getCode(){
    return "add_column(top())";
}
