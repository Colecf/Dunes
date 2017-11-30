#include "addrowmodule.h"
#include "modulelistitem.h"

const QString AddRowModule::title = "AddRow";
const QString AddRowModule::description = "Adds a row to the output spreadsheet. This module doesn't add any actual data to the spreadsheet, but instead moves down a row so that subsequent calls to AddColumn will add data on a new row.";

AddRowModule::AddRowModule()
{
    m_titleLabel->setText(title);
}

QString AddRowModule::getCode(){
    return "add_row();\n";
}

QString AddRowModule::getConfig(QString col){
    return title + col + "\n";
}
