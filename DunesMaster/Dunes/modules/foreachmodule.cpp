#include "foreachmodule.h"
#include "modulelistitem.h"

const QString ForEachModule::title = "ForEach";
const QString ForEachModule::description = "ForEach Description";

ForEachModule::ForEachModule()
{
    m_titleLabel->setText(title);
}

QString ForEachModule::getCode(){
    return "boilerplateselect()";
}
