#include "foreachmodule.h"
#include "modulelistitem.h"

const QString ForEachModule::title = "ForEach";
const QString ForEachModule::description = "Loops through contents of the input stream by HTML element and performs the nested operations";

ForEachModule::ForEachModule()
{
    m_titleLabel->setText(title);
}

QString ForEachModule::getCode(){
    QString code = "while(top().length > 0){";
    for(size_t i = 0; i < children.size(); i++){
        code += "  " + children.at(i)->getCode();
    }
    code += "  next();\n}";
    return code;
}

QString ForEachModule::getConfig(QString col){
    return "type=" + QString::number(type) + ";" + "col=" + col + ";" + "\n";
}
