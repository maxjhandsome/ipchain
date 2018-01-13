#include "ipctransfertransaction.h"
#include "ui_ipctransfertransaction.h"
#include "walletmodel.h"
#include "log/log.h"
IpcTransferTransaction::IpcTransferTransaction(QWidget *parent) :
    QWidget(parent),walletModel(NULL),
    ui(new Ui::IpcTransferTransaction)
{
    ui->setupUi(this);
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->line_2->hide();
    ui->line_3->hide();
    ui->label_error->setText("");
}

IpcTransferTransaction::~IpcTransferTransaction()
{
    delete ui;
}
void IpcTransferTransaction::SetNameDisplay(QString s1)
{
    ui->ipcnamelabel->setText(s1);
}
void IpcTransferTransaction::on_pushButton_back_pressed()
{
    Q_EMIT back();
}

void IpcTransferTransaction::on_pushButton_confirmtransaction_pressed()
{
    QString address = ui->lineEdit_address->text();
    if(address.isEmpty()){
        ui->label_error->setText(tr("InvalidAddress"));
        return;
    }
    LOG_WRITE(LOG_INFO,"IpcTransferTransaction",address.toStdString().c_str());
    QString msg;
    if(walletModel->transferIpc(address,msg))
    {
        ui->lineEdit_address->setText("");
        Q_EMIT gotoSuccessfultradePage(0);
    }
    else
    {
        if(msg == "AmountExceedsBalance")
            ui->label_error->setText(tr("AmountExceedsBalance"));
        else if(msg == "AmountWithFeeExceedsBalance")
            ui->label_error->setText(tr("AmountWithFeeExceedsBalance"));
        else if(msg == "InvalidAddress")
            ui->label_error->setText(tr("InvalidAddress"));
        else if(msg == "AmountExceedsBalance")
            ui->label_error->setText(tr("AmountExceedsBalance"));
        else if(msg == "Password error.")
            ui->label_error->setText(tr("Password error."));
        else if(msg == "IPC-owner-starttime-is-up-yet")
            ui->label_error->setText(tr("IPC-owner-starttime-is-up-yet")+ tr(" ")+m_strStringTime);
        else if(msg == "bad-txns-inputs-spent")
            ui->label_error->setText(tr("bad-txns-inputs-spent"));

        else
            ui->label_error->setText(tr("Other")+tr(" ")+msg);
    }
    LOG_WRITE(LOG_INFO,"IpcTransferTransaction msg",msg.toStdString().c_str());
}
void IpcTransferTransaction::showEvent(QShowEvent *event)
{
    ui->label_error->setText("");
    ui->lineEdit_address->setText("");
}
