#include "nextmodule.h"
#include "modulelistitem.h"

const QString NextModule::title = "Next";
const QString NextModule::description = "For an input stream with multiple HTML elements, discards the first element so that other blocks that operate on only the first element can now operate on the next one.";

NextModule::NextModule()
{
    m_titleLabel->setText(title);
}

QString NextModule::getCode(){
    return "next();\n";
}

QString NextModule::getConfig(QString col){
    return "type=" + QString::number(type) + ";" + "col=" + col + ";" + "\n";
}
