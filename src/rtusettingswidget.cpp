#include "serialsettingswidget.h"
#include "rtusettingswidget.h"
#include "ui_serialsettingswidget.h"
#include "modbus.h"

#include <QMessageBox>


RtuSettingsWidget::RtuSettingsWidget(QWidget *parent) :
    SerialSettingsWidget(parent)
{
}

RtuSettingsWidget::~RtuSettingsWidget()
{
}

void RtuSettingsWidget::changeModbusInterface(const QString& port, char parity)
{
    releaseSerialModbus();

    m_serialModbus = modbus_new_rtu( port.toAscii().constData(),
            ui->baud->currentText().toInt(),
            parity,
            ui->dataBits->currentText().toInt(),
            ui->stopBits->currentText().toInt() );

    if( modbus_connect( m_serialModbus ) == -1 )
    {
        QMessageBox::critical( this, tr( "Connection failed" ),
            tr( "Could not connect serial port!" ) );
	releaseSerialModbus();
    }
}
