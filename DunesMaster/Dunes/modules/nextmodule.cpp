#include "nextmodule.h"
#include "modulelistitem.h"

const QString NextModule::title = "Next";
const QString NextModule::description = "Next Description";

NextModule::NextModule()
{
    m_titleLabel->setText(title);
}

QString NextModule::getCode(){
    return "boilerplateselect()";
}
