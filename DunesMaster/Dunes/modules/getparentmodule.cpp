#include "getparentmodule.h"
#include "modulelistitem.h"

const QString GetParentModule::title = "GetParent";
const QString GetParentModule::description = "GetParent Description";

GetParentModule::GetParentModule()
{
    m_titleLabel->setText(title);
}

QString GetParentModule::getCode(){
    return "boilerplateselect()";
}
