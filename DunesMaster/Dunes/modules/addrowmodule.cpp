#include "addrowmodule.h"
#include "modulelistitem.h"

const QString AddRowModule::title = "AddRow";
const QString AddRowModule::description = "AddRow Description";

AddRowModule::AddRowModule()
{
    m_titleLabel->setText(title);
}

QString AddRowModule::getCode(){
    return "boilerplateselect()";
}
