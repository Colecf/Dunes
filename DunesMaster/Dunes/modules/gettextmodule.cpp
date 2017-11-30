#include "gettextmodule.h"
#include "modulelistitem.h"

const QString GetTextModule::title = "GetText";
const QString GetTextModule::description = "Gets the visible text contents of the first HTML element in the input stream.";

GetTextModule::GetTextModule()
{
    m_titleLabel->setText(title);
}

QString GetTextModule::getCode(){
    return "get_text();\n";
}

QString GetTextModule::getConfig(QString col){
    return title + col + "\n";
}
