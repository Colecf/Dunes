#include <unordered_map>
#include <stack>
#include <QDebug>
#include <QSaveFile>
#include <QTextStream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDialog>
#include <QDialogButtonBox>
#include "codegen.h"
#include "blockarea.h"

/* Opens a file, reads all it's contents and returns as string */
QString readFile(QString filename) {
    QFile f(filename);
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

/* Set blockarea, options. Create nodeProcess, npmProcess, and an alert box.
 Connects the processes to their respective functions on finishing, or an error occurring */
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


/*
    Runs after the Run Code or Generate buttons are pressed. Traverses blocks in block area
    and calls each block's getCode() to form a QString with all the code
*/
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
                        parentModule->children.push_back(module);
                    }
                }
            }
            // If it's a module that can be a parent, push on the row of the block
            if(dynamic_cast<ScopeModule*>(module) || dynamic_cast<IfModule*>(module) || dynamic_cast<WhileModule*>(module) || dynamic_cast<ForEachModule*>(module)) {
                parentRowStack->push(row);
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
    delete parentRowStack;
    return code;
}

/*
    Asks user for where to save generated code and the CSV created. Puts the packageJson in the same directory
    as the generated code. Writes the generated code.
*/
void CodeGen::writeCode(){
    if(INITIAL_CODE.size() == 0) {
        INITIAL_CODE = readFile(":/resources/basecode.js");
    }
    QString code = INITIAL_CODE;
    QString pathToCode = QFileDialog::getSaveFileName(m_blockarea, tr("Save generated code to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),  tr("Javascript (*.js)"));
    if(pathToCode.length() == 0){
        return;
    }
    QDir *codeDir = new QDir(pathToCode);
    if(codeDir->cdUp()){
        writePackageJson(codeDir->absolutePath());
    }
    else{
        qInfo() << "cdUp on codeDir failed!";
    }
    delete codeDir;
    QString pathToCSV = QFileDialog::getSaveFileName(m_blockarea, tr("Save CSV to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("CSV (*.csv)"));
    code += "const output_script = '" + pathToCSV + "';if(fs.existsSync(output_script)){fs.truncateSync(output_script, 0);}\n" + generateCode();
    QSaveFile qSaveFile(pathToCode);
    if (qSaveFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&qSaveFile);
        stream << code;
        qSaveFile.commit();
    }
}

/*
    Returns true only if both nodePath and npmPath are set.
*/
bool CodeGen::checkNodeAndNpmPaths(){
    return (options->getNodePath().length() != 0 && options->getNpmPath().length() != 0);
}

/*
    Runs after the Run Code button is pressed.
    Asks for where to save CSV, writes package.json and generated code to hidden folder.
    Then, starts startProcess()
*/
void CodeGen::runCode(){
    if(!checkNodeAndNpmPaths()){
        alert->setText("Please set your node and npm paths!");
        alert->exec();
        return;
    }
    if(INITIAL_CODE.size() == 0) {
        INITIAL_CODE = readFile(":/resources/basecode.js");
    }
    QString code = INITIAL_CODE;
    QDir curDir = QDir::current();
    QString pathToCode = curDir.absolutePath() + "/output/" + "dunes_index.js";
    QString packagePath = writePackageJson(curDir.absolutePath() + "/output/");
    QString pathToCSV = QFileDialog::getSaveFileName(m_blockarea, tr("Save CSV to"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("CSV (*.csv)"));
    if(pathToCSV.length() == 0){
        return;
    }
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

/*
    Called whenever we save our generated code. Writes a package.json for the user to manually run
    'npm install' or for us to run 'npm install'
*/
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
            delete dir;
            return packageJsonPath;
        }
    }
    delete dir;
    return "";
}

/*
    Makes the path to the folder, if one isn't set. Then sets where the processes standardErrFile
    and standardOutFiles go.
*/
void CodeGen::setOutFiles(QDir curDir, QString folderPath, bool isNode){
    if(curDir.mkpath(folderPath)){
        if(isNode){
            nodeProcess->setStandardErrorFile(folderPath + "standardErrFile");
            nodeProcess->setStandardOutputFile(folderPath + "standardOutFile");
        }
        else{
            npmProcess->setStandardErrorFile(folderPath + "standardErrFile");
            npmProcess->setStandardOutputFile(folderPath + "standardOutFile");
        }
    }
}

/*
    Called in startProcess() to set up environment variables, ensuring we have the correct
    working directory and the correct PATH.
*/
void CodeGen::setUpProcess(QString packageJsonPath, QString npmPath, QString nodePath){
    QDir packageJsonDir =  QDir(packageJsonPath);
    packageJsonDir.cdUp();
    npmProcess->setWorkingDirectory(packageJsonDir.absolutePath());
    QProcessEnvironment sysenv = QProcessEnvironment::systemEnvironment();
    QDir npmDir = QDir(npmPath);
    npmDir.cdUp();
    QDir nodeDir = QDir(nodePath);
    nodeDir.cdUp();
    QString path = sysenv.value("PATH");
    if(path != "")
        path += ":";
    path += npmDir.absolutePath() + ":" + nodeDir.absolutePath();
    sysenv.remove("PATH");
    sysenv.insert("PATH", path);
    npmProcess->setProcessEnvironment(sysenv);
}

/*
    Calls all necessary set up functions before starting the 'npm install' process.
    Sets the nodeProcess's program.
*/
void CodeGen::startProcess(QString codePath, QString packageJsonPath){
    QString npmFolderPath = QDir::current().absolutePath() + "/npm/";
    QString nodeFolderPath = QDir::current().absolutePath() + "/node/";
    QDir curDir = QDir::current();
    setOutFiles(curDir, npmFolderPath, false);
    setOutFiles(curDir, nodeFolderPath, true);
    QString npmPath = options->getNpmPath();
    QString nodePath = options->getNodePath();
    setUpProcess(packageJsonPath, npmPath, nodePath);
    npmProcess->start(npmPath, QStringList() <<"install");
    nodeProcess->setProgram(nodePath);
    nodeProcess->setArguments(QStringList() << codePath);
}

/*
    Sends an alert message to the user if there's an error with the node process
*/
void CodeGen::finishNodeProcessError(QProcess::ProcessError error){
    alert->setText("Error Node: " + QString::number(error));
    alert->exec();
    qInfo() << "errored out: " << error;
}

/*
    Sends an alert message to the user if there's an error with the npm process
*/
void CodeGen::finishNpmProcessError(QProcess::ProcessError error){
    alert->setText("Error Npm: " + QString::number(error ));
    alert->exec();
    qInfo() << "errored out: " << error;
}

/*
    On finishing the npm process, we start the node process. Otherwise, we
    alert the user that it failed.
*/
void CodeGen::finishedNpmProcess(int status){
    qInfo() << "NPM finished with status: " << status;
    if(status == 0){
        nodeProcess->start();
    }
    else{
        alert->setText("NPM failed to finish");
        alert->exec();
    }
}

/*
    On finishing the node process with status 0, we alert the user that it finished successfully.
    Otherwise, we alert the user with the error message that node left in it's standardErrFile.
*/
void CodeGen::finishedNodeProcess(int status){
    if(status == 0){
        alert->setText("Script ran!");
        alert->exec();
    }
    else{
        alert->setText(readFile(QDir::current().absolutePath() + "/node/standardErrFile"));
        alert->exec();
    }
    qInfo() << "Node finished with status: " << status;
}
