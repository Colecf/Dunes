#include <unordered_map>
#include <stack>
#include <QDebug>
#include <QSaveFile>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDialog>
#include <QDialogButtonBox>
#include "codegen.h"
#include "blockarea.h"

QString loadInitialCode() {
    QFile f(":/resources/basecode.js");
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        qInfo() << "Couldn't open file!";
        return "";
    }
    QTextStream in(&f);
    return in.readAll();
}

QString CodeGen::INITIAL_CODE = "";

CodeGen::CodeGen()
{
}

CodeGen::CodeGen(BlockArea *blockarea, OptionsMenu *optionsm)
{
    m_blockarea = blockarea;
    options = optionsm;
    nodeProcess = new QProcess(this);
    npmProcess = new QProcess(this);
    alert = new QMessageBox();
    alert->setText("Please set your node and npm paths!");
    connect(npmProcess, SIGNAL(finished(int)), this, SLOT(finishedNpmProcess(int)));
    connect(npmProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(finishNpmProcessError(QProcess::ProcessError)));
    connect(nodeProcess, SIGNAL(finished(int)), this, SLOT(finishedNodeProcess(int)));
    connect(nodeProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(finishNodeProcessError(QProcess::ProcessError)));
}

QString CodeGen::generateCode(){
    QString code = "";
    // Create mapping from row to column, do this instead of row to module because we can't get col from module
    auto rowToCol = m_blockarea->createRowToCol();
    // Stack of every parent-block's row (while, if, scope, foreach). Get the block via casting a widget w/ itemAtPosition
    QGridLayout *m_layout = m_blockarea->getLayout();
    std::stack<int> *parentRowStack = new std::stack<int>;
    for(int row = 0; row < m_layout->count(); row++){
        int col;
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
    if(INITIAL_CODE.size() == 0) {
        INITIAL_CODE = loadInitialCode();
    }
    QString code = INITIAL_CODE;
    QString pathToCode = QFileDialog::getSaveFileName(m_blockarea, tr("Save generated code to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),  tr("Javascript (*.js)"));
    QDir *codeDir = new QDir(pathToCode);
    if(codeDir->cdUp()){
        writePackageJson(codeDir->absolutePath());
    }
    else{
        qInfo() << "cdUp on codeDir failed!";
    }
    QString pathToCSV = QFileDialog::getSaveFileName(m_blockarea, tr("Save CSV to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("CSV (*.csv)"));
    code += "const output_script = '" + pathToCSV + "';if(fs.existsSync(output_script)){fs.truncateSync(output_script, 0);}\n" + generateCode();
    QSaveFile qSaveFile(pathToCode);
    if (qSaveFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&qSaveFile);
        stream << code;
        qSaveFile.commit();
    }
}

bool CodeGen::checkNodeAndNpmPaths(){
    return (options->getNodePath().length() != 0 || options->getNpmPath().length() != 0);
}

//runCode for the runButton
void CodeGen::runCode(){
    if(!checkNodeAndNpmPaths()){
        alert->setText("Please set your node and npm paths!");
        alert->exec();
        return;
    }
    if(INITIAL_CODE.size() == 0) {
        INITIAL_CODE = loadInitialCode();
    }
    QString code = INITIAL_CODE;
    QDir curDir = QDir::current();
    QString pathToCode = curDir.absolutePath() + "/output/" + "dunes_index.js";
    QString packagePath = writePackageJson(curDir.absolutePath() + "/output/");
    QString pathToCSV = QFileDialog::getSaveFileName(m_blockarea, tr("Save CSV to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("CSV (*.csv)"));
    code += "const output_script = '" + pathToCSV + "';if(fs.existsSync(output_script)){fs.truncateSync(output_script, 0);}\n" + generateCode();
    QSaveFile qSaveFile(pathToCode);
    if(curDir.mkpath(curDir.absolutePath() + "/output")){
        if (qSaveFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&qSaveFile);
            stream << code;
            qSaveFile.commit();
            if(pathToCSV != "" && packagePath.size() != 0){
                startProcess(pathToCode, packagePath);
            }
        }
    }
}

QString CodeGen::writePackageJson(QString codePath){
    QString packageJsonPath = codePath + "package.json";
    QString packageJson = "{\n\t\"main\": \"index.js\",\n\t\"dependencies\": {\n\t\t\"cheerio\": \"^0.22.0\",\n\t\t\"request\": \"^2.83.0\",\n\t\t\"sync-request\": \"^4.1.0\"\n\t},\n\t\"devDependencies\": {},\n\t\"author\": [\n\t\t\"Derek Kwong\",\n\t\t\"Cole Faust\"\n\t]\n}";
    QSaveFile qSaveFile(packageJsonPath);
    QDir *dir = new QDir();
    if(dir->mkpath(codePath)){
        if(qSaveFile.open(QIODevice::WriteOnly)){
            QTextStream stream(&qSaveFile);
            stream << packageJson;
            qSaveFile.commit();
            return packageJsonPath;
        }
    }
    return "";
}

void CodeGen::startProcess(QString codePath, QString packageJsonPath){
    // Add loading symbol?
    QString npmFolderPath = QDir::current().absolutePath() + "/npm/";
    QString nodeFolderPath = QDir::current().absolutePath() + "/node";
    QDir curDir = QDir::current();
    if(curDir.mkpath(npmFolderPath)){
        npmProcess->setStandardOutputFile(npmFolderPath + "standardOutFile");
        npmProcess->setStandardErrorFile(npmFolderPath + "standardErrFile");
    }
    QString npmPath = options->getNpmPath();
    QDir *packageJsonDir = new QDir(packageJsonPath);
    packageJsonDir->cdUp();
    npmProcess->setWorkingDirectory(packageJsonDir->absolutePath());
    QProcessEnvironment sysenv = QProcessEnvironment::systemEnvironment();
    QDir npmDir = QDir(npmPath);
    npmDir.cdUp();
    QString nodePath = options->getNodePath();
    QDir nodeDir = QDir(nodePath);
    nodeDir.cdUp();
    QString path = sysenv.value("PATH");
    if(path != "")
        path += ":";
    path += npmDir.absolutePath() + ":" + nodeDir.absolutePath();
    qInfo() << "path is " << path;
    sysenv.remove("PATH");
    sysenv.insert("PATH", path);
    npmProcess->setProcessEnvironment(sysenv);
    npmProcess->start(npmPath, QStringList() <<"install");
    qInfo() << "program is " << npmProcess->program();
    if(curDir.mkpath(nodeFolderPath)){
        nodeProcess->setStandardOutputFile(nodeFolderPath + "standardOutFile");
        nodeProcess->setStandardErrorFile(nodeFolderPath + "standardErrFile");
    }
    nodeProcess->setProgram(nodePath + " " + codePath);
}

void CodeGen::finishNodeProcessError(QProcess::ProcessError error){
    alert->setText("Error Node: " + QString::number(error));
    alert->exec();
    qInfo() << "errored out: " << error;
}

void CodeGen::finishNpmProcessError(QProcess::ProcessError error){
    alert->setText("Error Npm: " + QString::number(error ));
    alert->exec();
    qInfo() << "errored out: " << error;
}

void CodeGen::finishedNpmProcess(int status){
    if(status == 0){
        qInfo() << "NPM installed correctly";
        qInfo() << "Node process: " << nodeProcess->program();
        nodeProcess->start();
    }
    else{
        alert->setText("NPM failed to finish");
        alert->exec();
    }
    qInfo() << "NPM finished with status: " << status;
}

void CodeGen::finishedNodeProcess(int status){
    alert->setText("Script ran!");
    alert->exec();
    qInfo() << "Node finished with status: " << status;
}
