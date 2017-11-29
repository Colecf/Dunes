#include <unordered_map>
#include <stack>
#include <QDebug>
#include <QSaveFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include "codegen.h"
#include "blockarea.h"

const QString CodeGen::INITIAL_CODE = "var cheerio=require('cheerio');var request=require('sync-request');var fs=require('fs');var stack=[];function top(){return stack[stack.length-1]}function pop(){if(stack.length<0){console.error(\"Popping with empty stack\")}return stack.pop()}function get_page(url){if(stack.length>0){pop()}stack.push(request('GET',url).getBody())}function children(query,css){var $=query;var html=\"\";$(css).contents().each(function(i,elem){html+=$.html(this)});return html}function select_by_css(html,css,get_children=!1){var $=cheerio.load(html);pop();if(get_children){stack.push(children($,css))}else{stack.push($.html(css))}}function get_text(){var $=cheerio.load(top());pop();var ret=$(\"*\").first().text();stack.push(ret)}function add_row(){var data=fs.readFileSync(output_script);fs.truncateSync(output_script,data.length-1);fs.appendFileSync(output_script,'\\n')}function add_column(data){fs.appendFileSync(output_script,'\"'+data.replace(/\"/g,'\"\"')+'\",')}function scope(){stack.push(top())}function constant(data){if(stack.length>0){pop()}stack.push(data)}function attribute(attribute){var $=cheerio.load(pop());stack.push($(\"*\").first().attr(attribute))}function next(){var $=cheerio.load(top());pop();var html=\"\";$(\"*\").first().nextAll().each(function(i,elem){html+=$.html(this)});stack.push(html)}";

CodeGen::CodeGen()
{
}

CodeGen::CodeGen(BlockArea *blockarea)
{
    m_blockarea = blockarea;
}

QString CodeGen::generateCode(){
    QString code = "";
    // Create mapping from row to column, do this instead of row to module because we can't get col from module
    std::unordered_map<int, int> *rowToCol = m_blockarea->createRowToCol();
    // Stack of every parent-block's row (while, if, scope, foreach). Get the block via casting a widget w/ itemAtPosition
    QGridLayout *m_layout = m_blockarea->getLayout();
    std::stack<int> *parentRowStack = new std::stack<int>;
    for(int row = 0; row < m_layout->count(); row++){
        int col, prevModuleCol;
        if((col = m_blockarea->getCol(rowToCol, row)) == -1){
            qErrnoWarning("Error: col must integer >= 0");
            return NULL;
        }
        QWidget* const item = m_layout->itemAtPosition(row, col)->widget();
        if(BaseModule *module = dynamic_cast<BaseModule*>(item)){
            int parentCol;
            // If we have parent blocks, get the parentCol and compare with current col
            if(!parentRowStack->empty() && (parentCol = m_blockarea->getCol(rowToCol, parentRowStack->top())) != -1){
                // If equal, we know we need to pop off all block rows that have a corresponding col >= than the current block's col
                while(parentCol >= col){
                    parentRowStack->pop();
                    if(!parentRowStack->empty()){
                        parentCol = m_blockarea->getCol(rowToCol, parentRowStack->top());
                    }
                    else{
                        // In the case that parentCol = col = 0, we don't want it to pop again.
                        // Set it to large random negative # to not trigger bottom if-statement
                        parentCol = std::numeric_limits<int>::min();
                    }
                }
                // If the parent is a parent to this module, add it to the parent's children
                if(parentCol+1 == col){
                    QWidget* const parent = m_layout->itemAtPosition(parentRowStack->top(), parentCol)->widget();
                    if(BaseModule *parentModule = dynamic_cast<BaseModule*>(parent)){
                        parentModule->children->push_back(module);
                    }
                }
            }
            // If it's a scope, push on the row of the block
            if(dynamic_cast<ScopeModule*>(module)){
                parentRowStack->push(row);
                module->children = new std::vector<BaseModule*>;
            }
            else if(dynamic_cast<IfModule*>(module) || dynamic_cast<WhileModule*>(module)){
                module->children = new std::vector<BaseModule*>;
            }
        }
        prevModuleCol = col;
    }
    for(int row = 0; row < m_layout->count(); row++){
        int col;
        if((col = m_blockarea->getCol(rowToCol, row)) == -1){
            qErrnoWarning("Error: col must integer >= 0");
            return NULL;
        }
        if(col == 0){
            QWidget* const item = m_layout->itemAtPosition(row, col)->widget();
            if(BaseModule *module = dynamic_cast<BaseModule*>(item)){
                code += module->getCode();
            }
        }
    }
    return code;
}

// writeCode for the generateButton
void CodeGen::writeCode(){
    QString code = INITIAL_CODE;
    QString pathToCode = QFileDialog::getSaveFileName(m_blockarea, tr("Save generated code to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),  tr("Javascript (*.js)"));
    writePackageJson(pathToCode);
    QString pathToCSV = QFileDialog::getSaveFileName(m_blockarea, tr("Save CSV to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("CSV (*.csv)"));
    code += "const output_script = '" + pathToCSV + "';if(fs.existsSync(output_script)){fs.truncateSync(output_script, 0);}\n" + generateCode();
    QSaveFile qSaveFile(pathToCode);
    if (qSaveFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&qSaveFile);
        stream << code;
        qSaveFile.commit();
        qInfo() << "saved to: " << pathToCode << endl;
    }
}

//runCode for the runButton
void CodeGen::runCode(){
    QString code = INITIAL_CODE;
    QString pathToCode = QDir::current().absolutePath() + "/output/" + "dunes_index.js";
    QString pathToCSV = QFileDialog::getSaveFileName(m_blockarea, tr("Save CSV to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("CSV (*.csv)"));
    code += "const output_script = '" + pathToCSV + "';if(fs.existsSync(output_script)){fs.truncateSync(output_script, 0);}\n" + generateCode();
    QSaveFile qSaveFile(pathToCode);
    if (qSaveFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&qSaveFile);
        stream << code;
        qSaveFile.commit();
        qInfo() << "saved to: " << pathToCode << endl;
        if(pathToCSV != ""){
            startProcess(pathToCode);
        }
    }
}

void CodeGen::writePackageJson(QString codePath){
    QDir* path = new QDir(codePath);
    if(path->cdUp()){
        QString packageJsonPath = path->absolutePath() + "/package.json";
        QString packageJson = "{\n\t\"main\": \"index.js\",\n\t\"dependencies\": {\n\t\t\"cheerio\": \"^0.22.0\",\n\t\t\"request\": \"^2.83.0\",\n\t\t\"sync-request\": \"^4.1.0\"\n\t},\n\t\"devDependencies\": {},\n\t\"author\": [\n\t\t\"Derek Kwong\",\n\t\t\"Cole Faust\"\n\t]\n}";
        QSaveFile qSaveFile(packageJsonPath);
        if(qSaveFile.open(QIODevice::WriteOnly)){
            QTextStream stream(&qSaveFile);
            stream << packageJson;
            qSaveFile.commit();
            qInfo() << "packageJson saved to: " << packageJsonPath << endl;
        }
    }

}

void CodeGen::startProcess(QString codePath){
    // Add loading symbol?
    QProcess *nodeProcess = new QProcess(this);
    nodeProcess->setStandardOutputFile(QDir::current().absolutePath() + "/output/" + "standardOutFile");
    nodeProcess->setStandardErrorFile(QDir::current().absolutePath() + "/output/" + "standardErrFile");
    nodeProcess->start("/usr/local/bin/node " + codePath);
    connect(nodeProcess, SIGNAL(finished(int)), this, SLOT(finishProcess(int)));
    connect(nodeProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(finishProcessError(QProcess::ProcessError)));
}

void CodeGen::finishProcessError(QProcess::ProcessError error){
    qInfo() << "errored out: " << error;
}

void CodeGen::finishProcess(int exitCode){
    // End loading symbol?
    qInfo() << "finished: " << exitCode;
}
