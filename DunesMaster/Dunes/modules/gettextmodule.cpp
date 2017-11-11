#include "gettextmodule.h"
#include "modulelistitem.h"

const QString GetTextModule::title = "GetText";
const QString GetTextModule::description = "GetText Description";

GetTextModule::GetTextModule()
{
    m_titleLabel->setText(title);
}

QString GetTextModule::getCode(){
    return "boilerplateselect()";
}
