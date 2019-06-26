#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::training_Auto_confirm()
{
    qDebug() << "auto confirmed";

    while(model_mentors->canFetchMore())
    {
        model_mentors->fetchMore();
    }
    int row = model_mentors->rowCount();

    for(int i=0; i<row; i++)
    {
        QString train_1 = model_mentors->index(i,10).data().toString();
        QString train_2 = model_mentors->index(i,11).data().toString();
        QString train_3 = model_mentors->index(i,12).data().toString();
        QString WWVP = model_mentors->index(i,13).data().toString();

        if(train_1 != "y")
        {
            model_mentors->setData(model_mentors->index(i,10),"n");
        }

        if(train_2 != "y")
        {
            model_mentors->setData(model_mentors->index(i,11),"n");
        }

        if(train_3 != "y")
        {
            model_mentors->setData(model_mentors->index(i,12),"n");
        }

        if(train_1 == "y" && train_2 == "y" && train_3 == "y" && !WWVP.isEmpty())
        {
            model_mentors->setData(model_mentors->index(i,14),"y");
        }
        else
        {
            model_mentors->setData(model_mentors->index(i,14),"n");
        }
    }
    //model_mentors->submitAll();
}

void MainWindow::init_mentors_model()
{
    // init mentors' table model
    model_mentors = new QSqlTableModel(this,db);    // model_mentors is a private pointer defined in header file
    model_mentors->setTable("mentor");
    model_mentors->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_mentors->select();

    model_mentors->setHeaderData(0, Qt::Horizontal, "Uni ID");
    model_mentors->setHeaderData(1, Qt::Horizontal, "First Name");
    model_mentors->setHeaderData(2, Qt::Horizontal, "Last Name");
    model_mentors->setHeaderData(3, Qt::Horizontal, "Gender");
    model_mentors->setHeaderData(4, Qt::Horizontal, "Email");
    model_mentors->setHeaderData(5, Qt::Horizontal, "Mobile");
    model_mentors->setHeaderData(6, Qt::Horizontal, "Addtional information");
    model_mentors->setHeaderData(7, Qt::Horizontal, "Academic Level");
    model_mentors->setHeaderData(8, Qt::Horizontal, "College");
    model_mentors->setHeaderData(9, Qt::Horizontal, "Language");
    model_mentors->setHeaderData(10, Qt::Horizontal, "Training 1");
    model_mentors->setHeaderData(11, Qt::Horizontal, "Training 2");
    model_mentors->setHeaderData(12, Qt::Horizontal, "Training 3");
    model_mentors->setHeaderData(13, Qt::Horizontal, "WWVP Card Num");
    model_mentors->setHeaderData(14, Qt::Horizontal, "Confirm");
    model_mentors->setHeaderData(15, Qt::Horizontal, "Role");
}

void MainWindow::init_mentors_view()
{
    // set table view
    ui->tableView_mentors->setModel(model_mentors);

    delegare_model_mentor_training_1 = new Delegate_Training(this);
    delegare_model_mentor_training_2 = new Delegate_Training(this);
    delegare_model_mentor_training_3 = new Delegate_Training(this);
    delegare_model_mentor_training_confirm = new Delegate_Training(this);

    ui->tableView_mentors->setItemDelegateForColumn(10,delegare_model_mentor_training_1);
    ui->tableView_mentors->setItemDelegateForColumn(11,delegare_model_mentor_training_2);
    ui->tableView_mentors->setItemDelegateForColumn(12,delegare_model_mentor_training_3);
    ui->tableView_mentors->setItemDelegateForColumn(14,delegare_model_mentor_training_confirm);

    ui->tableView_mentors->hideColumn(15);
    ui->tableView_mentors->resizeColumnsToContents();
}

// ----------------------------------

// mentors

void MainWindow::init_mentors_page()
{
    init_mentors_model();
    init_mentors_view();
}

void MainWindow::on_lineEdit_mentors_search_editingFinished()
{
    QString str = ui->lineEdit_mentors_search->text().trimmed();    // Returns a string that has whitespace removed from the start and the end
    if(str.isEmpty()) {
        model_mentors->setFilter("");
        return;
    }
    QStringList list = str.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);   // get string list
    int num = list.size();
    QString tmp = list.at(0);
    QString argument = "uid LIKE '%" + tmp + "%'";
    for (int i=0; i < num ; i++)
    {
        tmp = list.at(i);
        argument = argument
                + " OR " + "uid LIKE '%" + tmp + "%'"               // Uni ID
                + " OR " + "first_name LIKE '%" + tmp + "%'"        // First Name
                + " OR " + "last_name LIKE '%" + tmp + "%'";        // Last Name
    }
    qDebug() << argument;
    model_mentors->setFilter(argument);
}

void MainWindow::on_pushButton_mentors_add_clicked()
{
    QSqlTableModel *tm = model_mentors;
    if (tm == nullptr)
        return;

    QModelIndex insertIndex = ui->tableView_mentors->currentIndex();
    int row = insertIndex.row() == -1 ? 0 : insertIndex.row();
    tm->insertRow(row);
    insertIndex = tm->index(row, 0);
    ui->tableView_mentors->setCurrentIndex(insertIndex);
    ui->tableView_mentors->edit(insertIndex);

    qDebug() << "Insert Row";
}

void MainWindow::on_pushButton_mentors_delete_clicked()
{
    QSqlTableModel *tm = model_mentors;
    if (!tm)
        return;

    QModelIndexList currentSelection = ui->tableView_mentors->selectionModel()->selectedIndexes();
    for (int i = 0; i < currentSelection.count(); ++i) {
        tm->removeRow(currentSelection.at(i).row());
    }

    if (tm){
        if(!tm->submitAll()){
            qDebug()<<"Unable to delete"<<endl;
            QSqlError err = tm->lastError();
            QMessageBox::warning(this, tr("Unable to delete"), tr("An error occurred while "
                                       "deleting the connection: ") + err.text());
        }
    }

    qDebug() << "Delete Row";
}

void MainWindow::on_pushButton_mentors_revert_clicked()
{
    QSqlTableModel * tm = model_mentors;
    if (tm)
        tm->revertAll();

    qDebug() << "Revert";
}

void MainWindow::on_pushButton_mentors_submit_clicked()
{
    QSqlTableModel * tm = model_mentors;
    if (tm){
        if(!tm->submitAll()){
            qDebug()<<"Unable to submit"<<endl;
            QSqlError err = tm->lastError();
            QMessageBox::warning(this, tr("Unable to submit"), tr("An error occurred while "
                                       "submitting the connection: ") + err.text());
        }
    }

    qDebug() << "Submit All";
}

